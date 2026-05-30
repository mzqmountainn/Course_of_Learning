//
// Created by 18455 on 2026/5/30.
//
//本次注意的点：需要重载operation<，不然红黑树插入时无法比较
#include "md5.h"
#include <vector>
#include <stdlib.h>
#include <string>
#include <list>
#include <set>
#include <map>
#include <iostream>

using namespace std;

class physicalServer;

//虚拟节点
class virtualServer {
private:
    string ip_;
    unsigned int md5_;
    physicalServer *physicalServerptr_;
public:
    virtualServer(string &&ip, physicalServer *p) : ip_(ip), physicalServerptr_(p) { md5_ = getMD5(ip.c_str()); };
    //重载<，供红黑树插入时使用
    bool operator<(const virtualServer &b) const {
        return md5_ < b.md5_;
    }
    const unsigned int getMD5V(void) const {
        return md5_;
    }
    const physicalServer *getphysicalServer(void) const {
        return physicalServerptr_;
    }
};

//实际节点
class physicalServer {
private:
    list<virtualServer> virtualServerList;
    string ip_;
    int virtualSize;
public:
    physicalServer(string &&ip, int size = 200) : ip_(ip), virtualSize(size) {
        for (int i = 0; i < virtualSize; ++i) {
            virtualServerList.emplace_back(ip + "#" + ::to_string(i), this);
        }
    }
    const list<virtualServer> &getvirtualServerList(void) const {
        return virtualServerList;
    }
    const string getIP(void) const {
        return ip_;
    }
};

//一致哈希（基于红黑树）
class consistentHash {
public:
    void add(physicalServer &ps) {
        // 使用 const auto& 避免不必要的对象拷贝
        for (const auto &it: ps.getvirtualServerList()) {
            virtualServerSet.insert(it);
        }
    }
    void del(physicalServer &ps) {
        for (const auto &it: ps.getvirtualServerList()) {
            auto itInconcistentHash = virtualServerSet.find(it);
            if (itInconcistentHash != virtualServerSet.end())
                virtualServerSet.erase(itInconcistentHash);
        }
    }
    string getRealIp(string &guestIP) const {
        const unsigned int md5 = getMD5(guestIP.c_str());
        for (auto vhost: virtualServerSet) {
            if (vhost.getMD5V() > md5) {
                return vhost.getphysicalServer()->getIP();
            }
        }
        //一致性哈希是一个首尾相接的环，超出了最大节点，就应该回到第一个节点。
        return virtualServerSet.begin()->getphysicalServer()->getIP();
    }
private:
    set<virtualServer> virtualServerSet;
};

void ShowConsistentHash(consistentHash &chash);
int main(void) {
    physicalServer test1("192.168.0.0", 10000);
    physicalServer test2("192.168.1.0", 10000);
    physicalServer test3("192.168.2.0", 10000);

    consistentHash chash;
    chash.add(test1);
    chash.add(test2);
    chash.add(test3);

    ShowConsistentHash(chash);
//    chash.del(test1);
//    ShowConsistentHash(chash);
    return 0;
}
void ShowConsistentHash(consistentHash &chash) {
    list<string> iplists{
            "192.168.1.123",
            "192.168.1.12",
            "192.168.1.13",
            "192.168.1.23",
            "192.168.1.54",
            "192.168.1.89",
            "192.168.1.21",
            "192.168.1.27",
            "192.168.1.49",
            "192.168.1.145",
            "192.168.2.34",
            "192.168.6.78",
            "192.168.2.90",
            "192.168.4.5"
    };

    map<string, list<string>> logMap;

    for (auto clientip: iplists) {
        string host = chash.getRealIp(clientip);
        logMap[host].emplace_back(clientip);
    }

    for (auto pair: logMap) {
        cout << "物理主机:" << pair.first << endl;
        cout << "客户端映射的数量:" << pair.second.size() << endl;

        for (auto ip: pair.second) {
            cout << ip << endl;
        }

        cout << "----------------------------" << endl;
    }
    cout << endl;
}
