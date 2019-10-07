//
// Created by anranzhai on 10/6/19.
//

//Definition for singly-linked list.
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//对前k位的翻转
ListNode* reverseK(ListNode* head, int k) {
    ListNode* dummy=new ListNode(0);
    dummy->next=head;

    ListNode* pre=head;
    ListNode* cur=head->next;

    for(int i=1;i<k;i++){
        dummy->next=cur;
        pre->next=cur->next;
        cur->next=head;

        cur=pre->next;
        head=dummy->next;
    }

    return dummy->next;
}

//对k位的翻转
ListNode* reverse(ListNode* head,int k) {
    ListNode* pre;//或ListNode* pre=nullptr;
    ListNode* curr = head;
    while (curr&&k--) {
        ListNode* next = curr->next;
        curr->next = nullptr;//或cur->next=pre;
        pre = curr;
        curr = next;
    }
    return pre;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    int count=0;
    ListNode* dummy=new ListNode(0);
    dummy->next=head;
    ListNode* pre=dummy;
    for(ListNode* p=head;p!= nullptr;p=p->next){
        if(++count%k==0){
            p=pre->next;//记住最开始的结点，就是reverseK后的第k个结点
            pre->next=reverse(pre->next,k);
            pre=p;
        }
    }
    return dummy->next;
}

int main(){
    ListNode a(1),b(2),c(3),d(4);
    a.next=&b;//指针需要赋值地址而不是a.next=c;
    b.next=&c;
    c.next=&d;
    ListNode *p=reverseKGroup(&a,2);
    while(p){
        std::cout<<p->val;
        p=p->next;
    }

}