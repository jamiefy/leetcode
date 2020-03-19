//
// Created by anranzhai on 2020/3/19.
//
#include <iostream>
#include <map>
#include <deque>
#include <algorithm>
#include <vector>

class LRUCache {
public:
    LRUCache(int capacity) {
        cap=capacity;
    }

    int get(int key) {
        if(LRUMap.find(key)!=LRUMap.end()){
            recentUsed.erase(std::find(recentUsed.begin(),recentUsed.end(),key));
            recentUsed.push_back(key);
            return LRUMap[key];
        }
        return -1;
    }

    void put(int key, int value) {
        if(LRUMap.find(key)!=LRUMap.end()){
            LRUMap[key]=value;
            recentUsed.erase(std::find(recentUsed.begin(),recentUsed.end(),key));
            recentUsed.push_back(key);
            return;
        }
        if(LRUMap.size()>=cap){
            if(recentUsed.empty())
                return;
            else{
                LRUMap.erase(recentUsed.front());
                recentUsed.erase(recentUsed.begin());
            }
        }
        LRUMap[key]=value;
        recentUsed.push_back(key);
    }
private:
    std::map<int,int> LRUMap;
    std::vector<int> recentUsed;
    std::size_t cap;
};

int main(){
    LRUCache lruCache(2);
    std::cout<<lruCache.get(2)<<std::endl;
    lruCache.put(2,6);
    std::cout<<lruCache.get(1)<<std::endl;
    lruCache.put(1,5);
    lruCache.put(1,2);
    std::cout<<lruCache.get(1)<<std::endl;
    std::cout<<lruCache.get(2)<<std::endl;
}