//
// Created by Administator on 2019/12/25.
//
#include <iostream>
#include <memory>
#include <vector>
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

//时间复杂度：O(n)
//空间复杂度：O(n)
//运行时间贼慢，空间中上
ListNode* rotateRight(ListNode* head, int k) {
    //如果传入为空直接返回，一定要有该判断，只有在非空的情况下才能进行下面的步骤
    if(head==NULL)
        return head;
    ListNode* ptr=head;
    int count=1;
    while(ptr->next!=NULL){
        count++;
        ptr=ptr->next;
    }
    k=k%count;
    if(k==0 || count==1)
        return head;
    else{
        std::vector<int> tmp;
        for(ptr=head;ptr!=NULL;ptr=ptr->next)
            tmp.push_back(ptr->val);
        ListNode* behind=head;
        for(int i=0;i<k;i++){
            behind=behind->next;
        }
        for(int pre=0;pre<count;pre++,behind=behind->next){
            if(behind==NULL){
                behind=head;
            }
            behind->val=tmp[pre];
        }
    }
    return head;
}

//链表中的点已经相连，一次旋转操作意味着：先将链表闭合成环,找到相应的位置断开这个环，确定新的链表头和链表尾
//新的链表头在位置 n-k 处，其中 n 是链表中点的个数，新的链表尾就在头的前面，位于位置 n-k-1
//时间复杂度：O(N)，其中 NN 是链表中的元素个数
//空间复杂度：O(1)，因为只需要常数的空间
//执行用时是上面方法的1/5，消耗空间一样
ListNode* rotateRightNewHeadTail(ListNode* head, int k) {
    //如果传入为空直接返回，一定要有该判断，只有在非空的情况下才能进行下面的步骤
    if(head==NULL)
        return head;
    ListNode* ptr=head;
    int count=1;
    while(ptr->next!=NULL){
        count++;
        ptr=ptr->next;
    }
    k=k%count;
    if(k==0 || count==1)
        return head;
    else {
        ListNode *p=head;
        ListNode *newTail = head;
        ListNode *newHead = NULL;
        for (int i = 0; i < k; i++) {
            p = p->next;
        }
        while(p->next!=NULL){
            p=p->next;
            newTail=newTail->next;
        }
        p->next=head;
        newHead=newTail->next;
        newTail->next=NULL;
        return newHead;
    }
}
int main(){
    ListNode l1(1);
    ListNode l2(2);
    ListNode l3(3);
    ListNode l4(4);
    l1.next=&l2;
    l2.next=&l3;
    l3.next=&l4;
    ListNode* p=rotateRightNewHeadTail(&l1,2);
    while(p!=NULL){
        std::cout<<p->val<<"->";
        p=p->next;
    }
}