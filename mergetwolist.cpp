//
// Created by anranzhai on 10/4/19.
//
#include <iostream>
#include <memory>

// Definition for singly-linked list.
 struct ListNode {
    int val;
    ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    std::shared_ptr<ListNode> dummy=std::make_shared<ListNode>(0);

    ListNode* p=dummy.get();//原生指针=智能指针指向对象.get()
    while(l1!= nullptr&&l2!=nullptr){
        if(l1->val<=l2->val){
            p->next=l1;
            l1=l1->next;
        }
        else if(l1->val>l2->val){
            p->next=l2;
            l2=l2->next;
        }
        p=p->next;
    }
    p->next=l1== nullptr?l2:l1;
    return dummy->next;
}

//递归调用，空间消耗为O（n+m）
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