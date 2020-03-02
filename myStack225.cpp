//
// Created by anranzhai on 2020/3/2.
//
#include <deque>
class MyStack {
public:
/** Initialize your data structure here. */
    MyStack() {

    }

/** Push element x onto stack. */
    void push(int x) {
        deq.push_back(x);
    }

/** Removes the element on top of the stack and returns that element. */
    int pop() {
        if(!deq.empty()){
            int back=deq.back();
            deq.erase(deq.begin()+deq.size()-1);
            return back;
        }
        return -1;
    }

/** Get the top element. */
    int top() {
        if(!deq.empty())
            return deq.back();
        return -1;
    }

/** Returns whether the stack is empty. */
    bool empty() {
        return deq.empty();
    }

private:
std::deque<int> deq;
};

int main(){
    int x=1;
    MyStack* obj = new MyStack();
    obj->push(x);
    int param_2 = obj->pop();
    int param_3 = obj->top();
    bool param_4 = obj->empty();
}