//
// Created by 18455 on 2026/10/10.
//
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class TrieTree
{
public:
    TrieTree()
    {
        root_ = new trieNode('\0', 0);
    };

    ~TrieTree()
    {
        queue<trieNode*> nodeQueue;
        nodeQueue.push(root_);
        while (!nodeQueue.empty())
        {
            trieNode* cur = nodeQueue.front();
            nodeQueue.pop();
            for (auto it : cur->nodeMap)
            {
                nodeQueue.push(it.second);
            }
            delete cur;
        }
    }

    struct trieNode
    {
        trieNode(char data, int fre) : data_(data), frequency_(fre)
        {
        };
        char data_;
        int frequency_;
        map<char, trieNode*> nodeMap;
    };

    void add(const string& word);
    int query(const string& word);
    void preOrder();
    vector<string> queryPrefix(string prefix);
    void remove(const string& word);

private:
    trieNode* root_;
    void preOrder(trieNode* cur, string word, vector<string>& wordLists);
};

void TrieTree::preOrder()
{
    vector<string> wordList;
    string word;
    preOrder(root_, word, wordList);
    for (auto it : wordList)
    {
        cout << it << endl;
    }
}

vector<string> TrieTree::queryPrefix(string prefix)
{
    trieNode* cur = root_;
    for (int i = 0; i < prefix.size(); ++i)
    {
        auto it = cur->nodeMap.find(prefix[i]);
        if (it == cur->nodeMap.end())
        {
            return {};
        }
        cur = it->second;
    }
    vector<string> wordLists;
    preOrder(cur, prefix.substr(0, prefix.size() - 1), wordLists);
    return wordLists;
}


void TrieTree::preOrder(trieNode* cur, string word, vector<string>& wordLists)
{
    if (cur != root_)
    {
        word += cur->data_;
    }
    if (cur->frequency_ != 0)
    {
        wordLists.emplace_back(word);
    }
    for (auto it : cur->nodeMap)
    {
        preOrder(it.second, word, wordLists);
    }
}

void TrieTree::add(const string& word)
{
    trieNode* cur = root_;
    for (int i = 0; i < word.size(); ++i)
    {
        auto it = cur->nodeMap.find(word[i]);
        if (it == cur->nodeMap.end())
        {
            auto newNode = new trieNode(word[i], 0);
            cur->nodeMap.emplace(word[i], newNode);
            cur = newNode;
        }
        else
        {
            cur = it->second;
        }
    }
    cur->frequency_++;
    return;
}

int TrieTree::query(const string& word)
{
    trieNode* cur = root_;
    for (int i = 0; i < word.size(); ++i)
    {
        auto it = cur->nodeMap.find(word[i]);
        if (it == cur->nodeMap.end())
        {
            return 0;
        }
        else
        {
            cur = it->second;
        }
    }
    return cur->frequency_;
}

void TrieTree::remove(const string& word)
{
    trieNode* cur = root_;
    trieNode* del = root_;
    char delch = word[0];
    for (int i = 0; i < word.size(); ++i)
    {
        auto it = cur->nodeMap.find(word[i]);
        if (it == cur->nodeMap.end())
        {
            return;
        }

        if (cur->nodeMap.size() > 1 || cur->frequency_ > 0)
        {
            del = cur;
            delch = word[i];
        }
        cur = it->second;
    }
    if (cur->nodeMap.empty())
    {
        trieNode* child = del->nodeMap[delch];
        del->nodeMap.erase(delch);
        queue<trieNode*> nodeQueue;
        nodeQueue.push(child);
        while (!nodeQueue.empty())
        {
            trieNode* front = nodeQueue.front();
            nodeQueue.pop();
            for (auto& it : front->nodeMap)
            {
                nodeQueue.push(it.second);
            }

            delete front;
        }
    }
    else
    {
        cur->frequency_ = 0;
    }
}


int main(void)
{
    TrieTree tree;
    tree.add("nice");
    tree.add("nicee");
    tree.add("npp");
    tree.add("nppp");
    tree.add("npp");
    tree.add("npp");
    tree.add("npp");
    tree.add("npp");
    tree.add("nip");
    tree.add("apple");
    cout << tree.query("nicee") << endl;
    tree.preOrder();
    tree.remove("npp");
    for (auto it : tree.queryPrefix("n"))
    {
        cout << it << " ";
    }
    for (auto it : tree.queryPrefix("a"))
    {
        cout << it << " ";
    }
    return 0;
}
