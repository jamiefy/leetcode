//
// Created by anranzhai on 2020/3/2.
//
#include <iostream>
 struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

//回溯,必须定义reverseHead为全局变量，局部变量传到函数里不能改变
ListNode* reverseHead=new ListNode(0);
ListNode* reverse(ListNode* curr){
    if(curr->next==NULL)
        reverseHead=curr;
    else{
        ListNode* pre=reverse(curr->next);
        curr->next=NULL;//加上此句可以减少执行时间
        pre->next=curr;
    }
    return curr;
}
ListNode* reverseList(ListNode* head) {
    if(head==NULL||head->next==NULL)
        return head;
    ListNode *pre = reverse(head->next);
    head->next = NULL;
    pre->next = head;
    return reverseHead;
}


ListNode* rever(ListNode* curr){
    if(curr==NULL||curr->next==NULL)
        reverseHead=curr;
    else{
        ListNode* pre=rever(curr->next);
        curr->next=NULL;//加上此句可以减少执行时间
        pre->next=curr;
    }
    return curr;
}
ListNode* reverseListImprove(ListNode* head) {
    rever(head);
    return reverseHead;
}

ListNode* reverseListImp(ListNode* head) {
    if(head==NULL||head->next==NULL)
        return head;
    ListNode *rhead = reverseListImp(head->next);
    head->next->next=head;
    head->next=NULL;
    return rhead;
}

//迭代
ListNode* reverseListRecur(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    while (curr != NULL) {
        ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}


int  main(){
    ListNode* one=new ListNode(1);
    ListNode* two=new ListNode(2);
    ListNode* three=new ListNode(3);
    one->next=two;
    two->next=three;
    ListNode* head=reverseListImprove(one);
    while(head!=NULL){
        std::cout<<head->val<<" ";
        head=head->next;
    }
}