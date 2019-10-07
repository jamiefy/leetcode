//
// Created by anranzhai on 10/4/19.
//
#include <iostream>
#include <memory>

//Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(head==NULL)
        return NULL;
    ListNode* dummy=new ListNode(8);
    dummy->next=head;
    ListNode* cur=head;
    int count=0;
    while(cur!= nullptr){
        count++;
        cur=cur->next;
    }
    ListNode* pre=dummy;
    for(int i=0;i<count-n;i++){
        pre=pre->next;
    }

   /* ListNode* tmp=pre->next;
    pre->next=tmp->next;
    delete tmp;
    //这里不能返回head，因为当head指向的节点被删除时，head->value=0
    return dummy->next;*/

    //没有delete真则该节点未被删除还在head指向的链表上但是不在dummy指向的链表上
    pre->next=pre->next->next;

    //这里不能返回head,因为当head指向的节点被跳过，当返回值为head->next时仍为原链表的第二个节点
    return dummy->next;
}

ListNode* removeNthFromEndImp(ListNode* head, int n) {
    if (head == NULL)
        return NULL;
    ListNode* dummy=new ListNode(0);
    dummy->next=head;
    ListNode* pre=dummy;
    ListNode* cur=head;
    while(n--){
        cur=cur->next;
    }
    while(cur!= nullptr){
        cur=cur->next;
        pre=pre->next;
    }
    pre->next=pre->next->next;
    return dummy->next;
}

int main(){
    ListNode* head=new ListNode(0);
    ListNode* p=head;
    for(int i=1;i<3;i++){
        ListNode* x=new ListNode(i);
        p->next=x;
        p=p->next;
    }
    head=removeNthFromEndImp(head->next,2);
    while(head!=NULL){
        std::cout<<head->val<<std::endl;
        head=head->next;
    }

}