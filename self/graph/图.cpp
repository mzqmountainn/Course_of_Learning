//
// Created by mzq on 2026/10/30.
//
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

//有向图
class Digraph
{
public:
    struct Vertic
    {
        list<int> adjList_;
        string data_;

        Vertic(string data) : data_(data)
        {
        };
    };

public:
    void readFile(const string& path)
    {
        FILE* file = fopen(path.c_str(), "r");
        if (file == nullptr)
        {
            throw path + "not exists!";
        }
        //填充第零号元素
        vertics.emplace_back("");
        while (!feof(file))
        {
            char line[1024];
            fgets(line, 1024, file);
            string lineStr(line);
            vertics.emplace_back(lineStr.substr(0, lineStr.size() - 1));
            fgets(line, 1024, file);
            //string lineStr2(line);
            std::stringstream linestream(line);
            string number;
            while (getline(linestream, number, ','))
            {
                vertics.back().adjList_.emplace_back(stoi(number));
            }
        }
        fclose(file);
    }

    void show() const
    {
        for (int i = 1; i < vertics.size(); i++)
        {
            cout << vertics[i].data_ << " : ";
            for (auto no : vertics[i].adjList_)
            {
                cout << no << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

private:
    vector<Vertic> vertics;
};

int main(void)
{
    Digraph graph;
    graph.readFile("/Users/mzq/workplace/Course_of_Learning/self/graph/info");
    graph.show();
    return 0;
}
