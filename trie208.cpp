//
// Created by anranzhai on 2020/3/23.
//
#include <iostream>
#include <cstring>
struct TrieNode{
    bool isStr;
    TrieNode* next[26];
    TrieNode():isStr(false){
        std::memset(next, 0, sizeof(next));  //memset这个函数的作用是将数字以单个字节逐个拷贝的方式放到指定的内存中去
        //这里是将next初始化，每个字节上都放0，这里next为数组名即指针类型，不需要加&
    };
};
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root=new TrieNode;
    }


    /** Inserts a word into the trie. */
    void insert(std::string word) {
        if(word.size()==0)
            return;
        TrieNode* cur=root;
        for(auto w:word){
            if(cur->next[w-'a']==NULL){
                cur->next[w-'a']=new TrieNode;
            }
            cur=cur->next[w-'a'];
        }
        cur->isStr=true;
    }

    TrieNode* hasPrefix(std::string prefix){
        TrieNode* cur=root;
        int index=0;
        while(prefix[index]!='\0'){
            if(cur->next[prefix[index]-'a']==NULL)
                return NULL;
            else
                cur=cur->next[prefix[index++]-'a'];
        }
        return cur;
    }

    /** Returns if the word is in the trie. */
    bool search(std::string word) {
        if(word.size()==0)
            return true;
        TrieNode* node=hasPrefix(word);
        return node!=NULL&&node->isStr;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix) {
        if(prefix.size()==0)return true;
        TrieNode* node=hasPrefix(prefix);
        return node!=NULL;
    }

private:
    TrieNode* root;
};

int main(){
    Trie* trie = new Trie();

    trie->insert("apple");
    std::cout<<trie->search("apple")<<std::endl;   // 返回 true
    std::cout<<trie->search("app")<<std::endl;    // 返回 false
    std::cout<<trie->startsWith("app")<<std::endl; // 返回 true
    trie->insert("app");
    std::cout<<trie->search("app")<<std::endl;
}