//
// Created by anranzhai on 2020/7/31.
//
#include <iostream>
#include <queue>
using namespace std;
//class MedianFinder {
//public:
//    /** initialize your data structure here. */
//    MedianFinder() {
//        cnt=0;
//    }
//
//    void addNum(int num) {
//        cnt++;
//        //big是空或者big的最大值大于num先压入big
//        if(big.empty()||big.top()>num){
//            big.push(num);
//            //偶数时保证big等于small，奇数时保证big最多比small多一个
//            if(big.size()>small.size()+cnt%2){
//                small.push(big.top());
//                big.pop();
//            }
//        }else{
//            small.push(num);
//            if(small.size()>big.size()+cnt%2){
//                big.push(small.top());
//                small.pop();
//            }
//        }
//    }
//
//
//    double findMedian() {
//        if(cnt%2==0)
//            return (big.top()+small.top())/2.0;
//        else
//            return big.size()>small.size()?big.top():small.top();
//    }
//private:
//    priority_queue<double> big;
//    priority_queue<double,vector<double>,greater<>> small;
//    int cnt;
//};

//奇数个时多的在小顶堆，偶数个时大小顶堆大小相等
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        cnt=0;
    }

    void addNum(int num) {
        //偶数个时，首先向小顶堆压下一个
        if((cnt&1)==0){
            //比big最大值小的，要取big最大值压入小顶堆
            if(!big.empty()&&big.top()>num){
                big.push(num);
                num=big.top();
                big.pop();
            }
            small.push(num);
        }else{
            //奇数个时，向大顶堆压入下一个
            if(!small.empty()&&small.top()<num){
                small.push(num);
                num=small.top();
                small.pop();
            }
            big.push(num);
        }
        cnt++;
    }


    double findMedian() {
        if(cnt%2==0)
            return (big.top()+small.top())/2.0;
        else
            return small.top();
    }
private:
    priority_queue<double> big;
    priority_queue<double,vector<double>,greater<>> small;
    int cnt;
};


int main(){
    MedianFinder* obj = new MedianFinder();
    obj->addNum(1);
//    double param_0=obj->findMedian();
    obj->addNum(2);
    double param_1=obj->findMedian();
    obj->addNum(3);
    double param_2 = obj->findMedian();
    obj->addNum(-4);
    double param_3=obj->findMedian();
    obj->addNum(-5);
    double param_4=obj->findMedian();
    cout<<1;
}


