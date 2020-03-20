//
// Created by anranzhai on 2020/3/19.
//
#include <iostream>
#include <map>
#include <deque>
#include <algorithm>
#include <vector>
#include <unordered_map>
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

//哈希表unordered_map（红黑树）和双链表
struct DLinkedNode {
    int key;
    int value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(int k,int v):key(k),value(v){prev=NULL;next=NULL;};
};
class LRUCacheImp {
public:
    LRUCacheImp(int capacity) {
        this->capacity = capacity;

        head = new DLinkedNode(-1,-1);
        head->prev = NULL;

        tail = new DLinkedNode(-1,-1);
        tail->next = NULL;

        head->next = tail;
        tail->prev = head;
    }
    void addNodeAfterHead(DLinkedNode* node) {
        /**
         * Always add the new node right after head.
         */
        node->prev = head;
        node->next = head->next;

        head->next->prev = node;
        head->next = node;
    }
    void removeNode(DLinkedNode* node) {
        /**
         * Remove an existing node from the linked list.
         */
        DLinkedNode* prev = node->prev;
        DLinkedNode* next = node->next;

        prev->next = next;
        next->prev = prev;
    }
    void moveToHead(DLinkedNode* node) {
        /**
         * Move certain node in between to the head.
         */
        removeNode(node);
        addNodeAfterHead(node);
    }
    DLinkedNode* popTail() {
        /**
         * Pop the current tail.
         */
        DLinkedNode* res = tail->prev;
        removeNode(res);
        return res;
    }
    int get(int key) {
        if(cache.find(key)==cache.end()){
            return -1;
        } else{
            DLinkedNode* node=cache.find(key)->second;
            moveToHead(node);
            cache[key]=node;
            return node->value;
        }
    }

    void put(int key, int value) {
        if(cache.find(key)==cache.end()){
            if(cache.size()<capacity) {
                DLinkedNode *node = new DLinkedNode(key, value);
                addNodeAfterHead(node);
                cache[key] = node;
            } else {
                cache.erase(popTail()->key);//pop的node也要从cache中删除
                DLinkedNode* node=new DLinkedNode(key,value);
                addNodeAfterHead(node);
                cache[key]=node;
            }
        } else {
            DLinkedNode* node=cache.find(key)->second;
            node->value=value;
            moveToHead(node);
            cache[key]=node;
        }
    }
private:
    std::unordered_map <int, DLinkedNode*> cache;
    int size;
    int capacity;
    DLinkedNode* head, *tail;
};

int main(){
    LRUCacheImp lruCache(2);
    std::cout<<lruCache.get(2)<<std::endl;
    lruCache.put(1,1);
    lruCache.put(2,2);
    std::cout<<lruCache.get(1)<<std::endl;
    lruCache.put(3,3);
    std::cout<<lruCache.get(2)<<std::endl;
    std::cout<<lruCache.get(3)<<std::endl;
}