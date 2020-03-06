//
// Created by anranzhai on 2020/3/6.
//
#include <iostream>
#include <list>
#include <algorithm>
#include <set>
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
//哈希表
//时间复杂度 : O(m+n)。
//空间复杂度 : O(m+n)。或检查B中每个节点是否在A哈希表中O(m)
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if(headA==NULL || headB==NULL)
        return NULL;
    if(headA==headB)
        return headA;
    std::list<ListNode*> listA,listB;
    while(headA!=NULL){
        listA.push_back(headA);
        headA=headA->next;
    }
    while(headB!=NULL){
        listB.push_back(headB);
        headB=headB->next;
    }
    auto it=std::find_first_of(listA.begin(),listA.end(),listB.begin(),listB.end());
    return it==listA.end()?NULL:*it;
}

//双指针妙啊
ListNode* getIntersectionNodeDoublePointer(ListNode* headA, ListNode* headB) {
    if (headA == NULL || headB == NULL) return NULL;
    ListNode* pA = headA, *pB = headB;
    while (pA != pB) {
        pA = pA == NULL ? headB : pA->next;
        pB = pB == NULL ? headA : pB->next;
    }
    return pA;
}