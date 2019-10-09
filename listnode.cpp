#include <iostream>

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

class Solution {
public:
    ListNode* addTwoNums(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead=new ListNode(0);
        ListNode* curr=dummyHead;
        int carry=0;
        while(l1 != nullptr || l2 != nullptr){
            int sum=(l1? l1->val:0)+(l2? l2->val:0)+carry;
            carry=sum/10;//carry是0或1，因为9+9+1=19最大不超过20
            curr->next=new ListNode(sum%10);
            curr=curr->next;
            l1?l1=l1->next: nullptr;
            l2?l2=l2->next: nullptr;
        }
        if(carry>0){
            curr->next=new ListNode(carry);
        }
        return dummyHead->next;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        bool isHead=true;
        ListNode* head;
        ListNode* currentListNode;
        int forward=0,current=0;//记录进位
        while(l1!= nullptr || l2!= nullptr){
            ListNode *listNode=new ListNode(0);//每次必须新建个节点，不然每次下一个会覆盖之前的节点
                if(isHead){
                    if(l1!= nullptr && l2!= nullptr){
                        head=new ListNode([&](int a,int b)->int{
                            if(a+b>=10){
                                forward=(a+b)/10;
                                return (a+b)%10;
                            } else
                                return a+b;
                        }(l1->val,l2->val));
                        l1=l1->next;
                        l2=l2->next;
                    }

                    else if(l1 == nullptr){
                        head=new ListNode(l2->val);
                        l2=l2->next;
                    }

                    else if(l2 == nullptr){
                        head=new ListNode(l1->val);
                        l1=l1->next;
                    }
                    currentListNode=head;
                    isHead= false;
                } else{
                    if(l1!= nullptr && l2!= nullptr){
                        listNode->val = [&](int a,int b)->int{
                            if(a+b+forward>=10){
                                current=(a+b+forward)%10;
                                forward=(a+b+forward)/10;
                                return current;
                            } else
                            {
                                current=a+b+forward;
                                forward=0;
                                return current;
                            }
                        }(l1->val,l2->val);
                        l1=l1->next;
                        l2=l2->next;
                    }
                    else if(l1 == nullptr){
                        listNode->val =[&](int b)->int{
                            if(b+forward>=10){
                                current=(b+forward)%10;
                                forward=(b+forward)/10;
                                return current;
                            } else{
                                current=b+forward;
                                forward=0;
                                return current;
                            }
                        }(l2->val);
                        l2=l2->next;
                    }
                    else if(l2 == nullptr){
                        listNode->val = [&](int b)->int{
                            if(b+forward>=10){
                                current=(b+forward)%10;
                                forward=(b+forward)/10;
                                return current;
                            } else
                            {
                                current=b+forward;
                                forward=0;
                                return current;
                            }

                        }(l1->val);
                        l1=l1->next;
                    }
                    currentListNode->next=listNode;
                    currentListNode=listNode;
                }
            }
            if(forward!=0){
                ListNode *listNode=new ListNode(forward);
                currentListNode->next=listNode;
                currentListNode=listNode;
            }
            currentListNode->next= nullptr;
            return head;
        }
};

int main() {
    int n,m,numOne,numTwo;
    while(std::cin>>n>>m){
        ListNode* headOneListNode,* headTwoListNode,*currentListNodeOne,*currentListNodeTwo;
        for(int i=0;i<n;i++){
            std::cin>>numOne;
            ListNode* listNodeOne=new ListNode(numOne);
            if(!i)
            {
                headOneListNode=listNodeOne;
                currentListNodeOne=headOneListNode;
            }
            else
            {
                if(headOneListNode && headTwoListNode){

                    currentListNodeOne->next=listNodeOne;
                    currentListNodeOne=listNodeOne;
                }
            }
        }
        for(int i=0;i<m;i++){
            std::cin>>numTwo;
            ListNode* listNodeTwo=new ListNode(numTwo);
            if(!i)
            {
                headTwoListNode=listNodeTwo;
                currentListNodeTwo=headTwoListNode;
            }
            else
            {
                if(headOneListNode && headTwoListNode){
                    currentListNodeTwo->next=listNodeTwo;
                    currentListNodeTwo=listNodeTwo;
                }
            }
        }
        currentListNodeOne=headOneListNode;
        currentListNodeTwo=headTwoListNode;
        while(currentListNodeOne!= NULL){
            std::cout<<currentListNodeOne->val;
            currentListNodeOne=currentListNodeOne->next;
        }
        std::cout<<std::endl;
        while(currentListNodeTwo!= NULL){
            std::cout<<currentListNodeTwo->val;
            currentListNodeTwo=currentListNodeTwo->next;
        }
        std::cout<<std::endl;
        Solution solution;
        ListNode* addListNode=solution.addTwoNums(headOneListNode,headTwoListNode);
        while(addListNode!= NULL){
            std::cout<<addListNode->val;
            addListNode=addListNode->next;
        }
    }
    return 0;
}