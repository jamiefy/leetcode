//
// Created by anranzhai on 10/5/19.
//
#include <iostream>
#include <memory>
#include <vector>

//Definition for singly-linked list.
 struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

ListNode* swapPairs(ListNode* head) {
    if(head== nullptr||head->next== nullptr)
        return head;
    ListNode* pre=head;
    ListNode* cur=head->next;
    ListNode* dummy=new ListNode(0);//必须new申请内存空间
    head=cur;
    while (cur){
       dummy->next=cur;
       pre->next=cur->next;
       cur->next=pre;
       dummy=pre;
       pre=pre->next;
       cur=pre?pre->next: nullptr;
    }
    return head;
}

//递归
ListNode* swapPair(ListNode* head) {
    if(head== nullptr||head->next== nullptr)
        return head;
    ListNode* next=head->next;
    head->next=swapPair(next->next);
    next->next=head;
    return next;
}


int main(){
    ListNode a(1),b(2),c(3),d(4);
    a.next=&b;//指针需要赋值地址而不是a.next=c;
    b.next=&c;
    c.next=&d;
    ListNode *p=swapPairs(&d);
    while(p){
        std::cout<<p->val;
        p=p->next;
    }

}