// 37_倒排索引.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#undef UNICODE
#include <Windows.h>

// 倒排项
struct InvertTerm
{
	InvertTerm(string docid, int freqs, int location)
		: docid_(docid)
		, freqs_(freqs)
	{
		locations_.emplace_back(location);
	}
	bool operator==(const InvertTerm& term) const
	{
		return docid_ == term.docid_;
	}
	bool operator<(const InvertTerm& term) const
	{
		return docid_ < term.docid_;
	}
	string docid_;        // 单词所在的文档
	int freqs_;           // 单词出现的次数
	list<int> locations_; // 单词出现的位置
};

// 倒排列表
class InvertList
{
public:
	// 添加倒排项
	void addTerm(string docid, int location)
	{
		for (auto& term : termList_)
		{
			if (term.docid_ == docid) // docid已经创建了
			{
				term.freqs_++;
				term.locations_.emplace_back(location);
				return;
			}
		}

		// 第一次创建docid文档的倒排项
		termList_.emplace_back(docid, 1, location);
	}

	// 获取倒排列表内容
	const list<InvertTerm>& getInvertList() const
	{
		return termList_;
	}
private:
	list<InvertTerm> termList_;  // 存储当前倒排列表所有的倒排项
};

// 倒排索引
class InvertIndex
{
public:
	// 设置文档搜索的根路径
	void setSearchPath(string path)
	{
		cout << "搜索文件...";
		getAllFile(path.c_str());
		cout << "完成!" << endl;

		cout << "开始创建倒排索引";
		createInvertIndex();
		cout << "完成!" << endl;
	}

	// 查询接口
	void query(string phrase)
	{
		// 先进行句子分词操作
		vector<string> wordList;
		char* word = strtok(const_cast<char*>(phrase.c_str()), " ");
		while (word != nullptr)
		{
			word = trim(word);
			if (strlen(word) > 0)
			{
				wordList.emplace_back(word);
			}
			word = strtok(nullptr, " ");
		}

		if (wordList.empty())
			return;

		if (wordList.size() == 1)
		{
			auto it = invertMap_.find(wordList[0]);
			if (it == invertMap_.end())
			{
				cout << "未搜索到任何匹配的内容!" << endl;
				return;
			}

			for (auto& term : it->second.getInvertList())
			{
				cout << term.docid_ << " freqs:" << term.freqs_ << endl;
			}
		}
		else
		{
			// 多个单词的搜索结果进行合并处理
			vector<InvertList> invertList;
			for (int i = 0; i < wordList.size(); i++)
			{
				// invertList.emplace_back(invertMap_[wordList[i]]);
				auto it = invertMap_.find(wordList[i]);
				if (it != invertMap_.end())
				{
					invertList.emplace_back(it->second);
				}
			}

			// 开始遍历所有的倒排列表，求里面倒排项的交集
			vector<InvertTerm> termShared;
			vector<InvertTerm> v1(invertList[0].getInvertList().begin(),
				invertList[0].getInvertList().end());
			for (int i = 1; i < invertList.size(); i++)
			{
				vector<InvertTerm> v2(invertList[i].getInvertList().begin(),
					invertList[i].getInvertList().end());

				sort(v1.begin(), v1.end());
				sort(v2.begin(), v2.end());

				// 求两个倒排列表里面倒排项的交集
				// set_intersection求集合交集时，必须保证v1和v2是有序的
				set_intersection(v1.begin(), v1.end(),
					v2.begin(), v2.end(),
					back_inserter(termShared));

				v1.swap(termShared);
				termShared.clear();
			}

			// 得分排名比较高的倒排项
			for (auto& term : v1)
			{
				cout << term.docid_ << " freqs:" << term.freqs_ << endl;
				cout << "locations:";
				/*for (int pos : term.locations_)
				{
					cout << pos << " ";
				}
				cout << endl;*/
			}

			// 把出现部分单词的倒排项内容打印出来

		}
	}

	// 设置文档搜索的后缀名过滤
	void setSuffix(string suffix)
	{
		suffix_ = suffix;
	}
private:
	// 创建倒排索引结构
	void createInvertIndex()
	{
		for (string& filePath : fileList_)
		{
			cout << ".";
			FILE* pf = fopen(filePath.c_str(), "r");
			if (pf == nullptr)
			{
				cerr << filePath << " ......打开失败！" << endl;
				continue;
			}

			// 按行读取文件里面的内容，按照" "空格进行分词
			vector<string> wordList;
			int location = 0;
			const int LINE_SIZE = 2048;
			char line[LINE_SIZE] = { 0 };

			while (!feof(pf))
			{
				// 读一行文件内容
				fgets(line, LINE_SIZE, pf);

				// 按照" "空格进行分词 split   strtok
				char* word = strtok(line, " ");
				while (word != nullptr)
				{
					// 过滤一下word前后的多余的空格  \t  \n
					word = trim(word);
					if (strlen(word) > 0)
					{
						wordList.emplace_back(word);
					}
					word = strtok(nullptr, " ");
				}

				// 开始给wordList里面的单词创建或者修改倒排列表
				for (string& w : wordList)
				{
					location++;
					auto it = invertMap_.find(w);
					if (it == invertMap_.end())
					{
						// 新建w单词的倒排列表
						InvertList list;
						list.addTerm(filePath, location);
						invertMap_.emplace(w, list);
					}
					else
					{
						it->second.addTerm(filePath, location);
					}
				}
			}

			fclose(pf);
		}
	}

	// 去掉分词后  单词前后多余的字符 \t\t\tsdfads\t\n
	char* trim(char* word)
	{
		int i = 0;
		while (word[i] != '\0')
		{
			if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
			{
				i++;
			}
			else
			{
				break;
			}
		}

		int j = i;
		while (word[j] != '\0')
		{
			if (word[j] == ' ' || word[j] == '\t' || word[j] == '\n')
			{
				break;
			}
			j++;
		}
		word[j] = '\0';

		return word + i;
	}

	// 递归扫描路径下面所有的文件
	int getAllFile(const char* Path)
	{
		char szFind[MAX_PATH];
		WIN32_FIND_DATA FindFileData;
		strcpy(szFind, Path);
		strcat(szFind, "\\*.*");
		HANDLE hFind = FindFirstFile(szFind, &FindFileData);
		if (INVALID_HANDLE_VALUE == hFind)
			return -1;

		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
				{
					//发现子目录，递归之
					char szFile[MAX_PATH] = { 0 };
					strcpy(szFile, Path);
					strcat(szFile, "\\");
					strcat(szFile, FindFileData.cFileName);
					getAllFile(szFile);
				}
			}
			else
			{
				//找到文件，处理之
				string fileName(FindFileData.cFileName);
				int pos = fileName.find(suffix_);  // abcd.cpp   pos:4 +4 
				if (pos != string::npos && pos + suffix_.size() == fileName.size())
				{
					// std::cout << Path << "\\" << FindFileData.cFileName << std::endl;
					string filePath(Path);
					filePath.append("\\");
					filePath.append(fileName);
					fileList_.emplace_back(filePath);
				}
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);

		return 0;
	}
private:
	string suffix_;  // 过滤文档后缀   .cpp .cc .cxx .c
	list<string> fileList_;  // 存储所有需要建立倒排的文件
	unordered_map<string, InvertList> invertMap_; // 词典+倒排列表 
};

int main()
{
	InvertIndex index;
	index.setSuffix(".cpp");
	index.setSearchPath("D:\\cpp code\\C++全套数据结构算法代码");

	for (;;)
	{
		char buf[128] = { 0 };
		cout << "搜索内容:";
		cin.getline(buf, 128);   
		
		index.query(buf);  // grep
	}
	cout << endl;
}