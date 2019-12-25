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

int main(){
    ListNode l1(1);
    ListNode l2(2);
    ListNode l3(3);
    ListNode l4(4);
    l1.next=&l2;
    l2.next=&l3;
    l3.next=&l4;
    ListNode* p=rotateRight(&l1,2);
    while(p!=NULL){
        std::cout<<p->val<<"->";
        p=p->next;
    }
}