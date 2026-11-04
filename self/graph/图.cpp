//
// Created by mzq on 2026/10/30.
//
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

//有向图
class Digraph {
public:
    struct Vertic {
        list<int> adjList_;
        string data_;

        Vertic(string data) : data_(data) {
        };
    };

public:
    void readFile(const string &path) {
        FILE *file = fopen(path.c_str(), "r");
        if (file == nullptr) {
            throw path + "not exists!";
        }
        //填充第零号元素
        vertics.emplace_back("");
        while (!feof(file)) {
            char line[1024];
            fgets(line, 1024, file);
            string lineStr(line);
            vertics.emplace_back(lineStr.substr(0, lineStr.size() - 1));
            fgets(line, 1024, file);
            //string lineStr2(line);
            std::stringstream linestream(line);
            string number;
            while (getline(linestream, number, ',')) {
                int vex = stoi(number);
                if (vex > 0) {
                    vertics.back().adjList_.emplace_back(stoi(number));
                }
            }
        }
        fclose(file);
    }

    void show() const {
        for (int i = 1; i < vertics.size(); i++) {
            cout << vertics[i].data_ << " : ";
            for (auto no: vertics[i].adjList_) {
                cout << no << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    void dfs(void) {
        vector<bool> nodeHistory(vertics.size(), false);
        dfs(1, nodeHistory);
    }
    void bfs(void) {
        vector<bool> nodeHistory(vertics.size(), false);
        queue<int> nodeQueue;
        nodeQueue.push(1);
        nodeHistory[1] = true;
        while (!nodeQueue.empty()) {
            int cur = nodeQueue.front();
            nodeQueue.pop();
            cout << vertics[cur].data_ << " ";
            for (auto it: vertics[cur].adjList_) {
                if (!nodeHistory[it]) {
                    nodeQueue.push(it);
                    nodeHistory[it] = true;
                }
            }
        }
        return;
    }

private:
    void dfs(int no, vector<bool> &list) {
        if (list[no] == true) {
            return;
        }
        cout << vertics[no].data_ << " ";
        list[no] = true;
        for (auto it: vertics[no].adjList_) {
            dfs(it, list);
        }
    }

private:
    vector<Vertic> vertics;
};

int main(void) {
    Digraph graph;
#ifdef _WIN32
    // Windows
    graph.readFile("D:/workplace/Course_of_Learning/self/graph/info");
#elif defined(__APPLE__)
    // macOS
    graph.readFile("/Users/mzq/workplace/Course_of_Learning/self/graph/info");
#else
    // Linux
    graph.readFile("/home/mzq/workplace/Course_of_Learning/self/graph/info");
#endif
    //graph.readFile("/Users/mzq/workplace/Course_of_Learning/self/graph/info");
    graph.show();
    graph.dfs();
    cout << endl;
    graph.bfs();
    return 0;
}
