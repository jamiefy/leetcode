//
// Created by anranzhai on 10/5/19.
//
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

//Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };


ListNode* mergeTwoListsRecursive(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
        return l2;
    }
    else if (l2 == nullptr) {
        return l1;
    }
    else if (l1->val <= l2->val) {
        l1->next=mergeTwoListsRecursive(l1->next,l2);
        return l1;
    } else{
        l2->next=mergeTwoListsRecursive(l1,l2->next);
        return l2;
    }
}

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    if(lists.size()==0)
        return nullptr;
    else if(lists.size()==1) return lists[0];
    else{
        lists[1]=mergeTwoListsRecursive(lists[0],lists[1]);
        lists.erase(lists.begin());
        mergeKLists(lists);
        return lists[0];
    }
}

ListNode* mergeTwoLists(ListNode *l1,ListNode *l2){
    std::shared_ptr<ListNode> dummy=std::make_shared<ListNode>(0);
    ListNode* p=dummy.get();
    while(l1&&l2){
        if(l1->val<=l2->val){
            p->next=l1;
            l1=l1->next;
        } else{
            p->next=l2;
            l2=l2->next;
        }
        p=p->next;
    }
    p->next=l1?l1:l2;
    //p不能delete，p删了那块内存也就删了，会出现指针悬挂
    return dummy->next;
}

ListNode* mergeKListsImp(std::vector<ListNode*>& lists) {
    int len=lists.size();
    if(len==0)
        return nullptr;
    else if(len==1) return lists[0];
    else{
        for(int cur=0;cur+1<len;cur++){
            lists[cur+1]=mergeTwoLists(lists[cur],lists[cur+1]);
        }
        return lists[len-1];
    }
}

ListNode* mergeLists(std::vector<ListNode*>& lists) {
    int size=lists.size();
    if(size==0)return NULL;
    while(size>1)
    {
        for(int i=0;i<size;++i)
        {
            if(i%2==1)
            {
                lists[i/2]=mergeTwoLists(lists[i],lists[i-1]);
            }
        }
        if(size%2==1)
        {
            lists[size/2]=lists[size-1];
        }
        for(int i=0;i<size/2;++i)
        {
            //高效移除vector最后一个元素
            lists.pop_back();
        }
        size=lists.size();
    }
    return lists[0];
}



ListNode* mergeKList(std::vector<ListNode*>& lists) {
    if(lists.size()==0)return nullptr;
    std::vector<ListNode* > node_vec;
    for(int i=0;i<lists.size();i++)
    {
        ListNode* head=lists[i];
        while(head)
        {
            node_vec.push_back(head);
            head=head->next;
        }
    }
    std::sort(node_vec.begin(),node_vec.end(),[](ListNode* l1,ListNode* l2)-> bool{
        return l1->val<=l2->val;
    });
    for(int i=1;i<node_vec.size();i++)
    {
        node_vec[i-1]->next = node_vec[i];
    }
    node_vec[node_vec.size()-1]->next = NULL;
    return node_vec[0];
}

int main(){
    ListNode a(1),b(2),c(3),d(4);
    a.next=&c;//指针需要赋值地址而不是a.next=c;
    std::vector<ListNode*> lists({});
    ListNode *p=mergeKList(lists);
    while(p){
        std::cout<<p->val;
        p=p->next;
    }

}