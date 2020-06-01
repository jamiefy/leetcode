//
// Created by anranzhai on 2020/6/1.
//
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <stack>
#include <unordered_map>
using namespace std;
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

//bfs map<原节点，克隆节点>
Node* cloneGraphBFSStack(Node* node) {
    if(node==nullptr)
        return nullptr;
    unordered_set<Node*> visited;
    unordered_map<Node*,Node*> nmap;
    nmap[node]=new Node(node->val);
    deque<Node*> st;
    st.emplace_back(node);
    while(!st.empty()){
        Node* cur=st.front();
        st.pop_front();

        if(visited.count(cur)==0){
            for(auto& child:cur->neighbors){
                if(nmap.count(child)){
                    nmap[cur]->neighbors.push_back(nmap[child]);
                } else{
                    Node* copy=new Node(child->val);
                    nmap[cur]->neighbors.push_back(copy);
                    nmap[child]=copy;
                }
                st.push_back(child);
            }
            visited.emplace(cur);
        }
    }
    return nmap[node];
}

Node* cloneGraphDFSStack(Node* node) {
    if(node==nullptr)
        return nullptr;
    unordered_map<Node*,Node*> nmap;
    nmap[node]=new Node(node->val);
    stack<Node*> st;
    st.emplace(node);
    while(!st.empty()){
        Node* cur=st.top();
        st.pop();

        for(auto& child:cur->neighbors){
            //已经加进去nmap，就不再加入nmap
            if(!nmap.count(child)){
                nmap[child]=new Node(child->val);
                //只有当结点没有遍历过的时候才把其加入st
                st.emplace(child);
            }
            nmap[cur]->neighbors.push_back(nmap[child]);
        }
    }
    return nmap[node];
}

unordered_map<Node*, Node*> search;
Node* cloneGraphDFSRecursive(Node* node) {
    if (node == NULL)return nullptr;
    //当我发现这个节点已经遍历了,就直接返回当前节点，加入到当前节点的边
    if (search.count(node))return search[node];
    Node* r = new Node(node->val);//发现没有遍历以后visit=1
    search[node] = r;//new出来的是一个指针，但是不用打星号
    //否则没有遍历到的话,创建这个节点，并返回该节点，继续dfs原node
    for (auto n : node->neighbors) {
        r->neighbors.push_back(cloneGraphDFSRecursive(n));
    }
    return r;
}


int main(){
    Node* n1=new Node(1);
    Node* n2=new Node(2);
    Node* n4=new Node(4);
    Node* n3=new Node(3);
    n1->neighbors.push_back(n2);
    n1->neighbors.push_back(n4);

    n2->neighbors.push_back(n1);
    n2->neighbors.push_back(n3);

    n3->neighbors.push_back(n2);
    n3->neighbors.push_back(n4);

    n4->neighbors.push_back(n1);
    n4->neighbors.push_back(n3);

    Node* copy=cloneGraph(n1);
    cout<<1;
}