//
// Created by anranzhai on 2020/3/5.
//
#include <iostream>
#include <algorithm>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//迭代
//时间复杂度: O(N)。考虑包含 NN 个结点的链表。对每个节点最多会处理（第 nn 个结点之后的结点不处理）。
//空间复杂度: O(1)。我们仅仅在原有链表的基础上调整了一些指针，只使用了 O(1)O(1) 的额外存储空间来获得结果
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(head==NULL||head->next==NULL||m==n)
        return head;
    ListNode* beforeHead=new ListNode(0);
    beforeHead->next=head;
    ListNode* beforeStart=beforeHead,*curr=head;
    while(m>1){
        m--;
        n--;
        beforeStart=curr;
        curr=curr->next;
    }
    ListNode *start=curr,*pre=NULL;
    while(curr!=NULL&&n!=0){
        n--;
        ListNode *next=curr->next;
        curr->next=pre;
        pre=curr;
        curr=next;
    }
    beforeStart->next=pre;
    start->next=curr;
    return beforeHead->next;
    //不用构造虚拟头结点
//    if (beforeStart != null) {
//        beforeStart.next = prev;
//    } else {
//        head = prev;
//    }
//    return head;
}

bool stop= false;//交换至中心时停止交换数值
ListNode* reverseList(ListNode*head,ListNode* tail,int m,int n){
    if(m>1){
        reverseList(head->next,tail->next,m-1,n-1);
        return NULL;
    }else{
        if(n==1){
            std::swap(head->val,tail->val);
            return head->next;
        } else{
            ListNode* p=reverseList(head,tail->next,m,n-1);
            //奇数个和偶数个
            if(p==tail || p==tail->next)
                stop=true;
            if(!stop)
                std::swap(p->val,tail->val);
            return p->next;
        }
    }

}
//递归
ListNode* reverseBetweenRecursive(ListNode* head, int m, int n) {
    if(head==NULL||head->next==NULL||m==n)
        return head;
    reverseList(head,head,m,n);
    return head;
}

int  main(){
    ListNode* one=new ListNode(1);
    ListNode* two=new ListNode(2);
    ListNode* three=new ListNode(3);
    ListNode* four=new ListNode(4);
    ListNode* five=new ListNode(5);
    one->next=two;
    two->next=three;
    three->next=four;
    four->next=five;
    ListNode* head=reverseBetweenRecursive(three,1,1);
    while(head!=NULL){
        std::cout<<head->val<<" ";
        head=head->next;
    }
}