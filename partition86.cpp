//
// Created by I538989 on 6/15/2020.
//
#include<iostream>
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

//双指针
//时间复杂度: O(N)，其中N是原链表的长度，我们对该链表进行了遍历。
//空间复杂度: O(1)，我们没有申请任何新空间。值得注意的是，我们只移动了原有的结点，因此没有使用任何额外空间。
ListNode* partition(ListNode* head, int x) {
    if(head== nullptr)
        return nullptr;
    auto dummylow=new ListNode(0);
    auto lowptr=dummylow;
    auto dummyhigh=new ListNode(0);
    auto highptr=dummyhigh;
    while(head!=nullptr){
        if(head->val<x){
            lowptr->next=head;
            lowptr=lowptr->next;
        }else{
            highptr->next=head;
            highptr=highptr->next;
        }
        head=head->next;
    }
    highptr->next= nullptr;
    lowptr->next=dummyhigh->next;
    return dummylow->next;
}