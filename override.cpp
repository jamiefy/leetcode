//
// Created by anranzhai on 2020/3/26.
//
#include <iostream>
using namespace std;
class Base
{
private:
    virtual void display() { cout<<"Base display()"<<endl; }
    void show(){ cout<<"Base show()"<<endl; }
public:
    void exec(){ display(); show(); }
    void fun(string s) { cout<<"Base fun(string)"<<endl; }
    void fun(int a) { cout<<"Base fun(int)"<<endl; }//overload:两个fun函数在Base类的内部被重载
    virtual int function(){}
};
class ClassA:public Base
{
public:
    void display() { cout<<"ClassA display()"<<endl; }//override:基类中display为虚函数，且参数列表一直，故此处为重写
    void fun(int a,int b) { cout<<"ClassA fun(int,int)"<<endl; }//redefining:fun函数在Base类中不为虚函数，故此处为重定义
    void show() { cout<<"ClassA show()"<<endl; }//redefining:理由同上
    int function(int a){}//overload:注意这是重载而不是重写，因为参数列表不同，在编译时ClassA中其实还有个编译器自己偷偷加上的从Base继承来的int function(){};
};
int main(){
    ClassA a;
    Base *base=&a;
    base->exec();//display()是ClassA的，因为覆盖了，show()是Base自己的
    a.exec();//结果同上
    a.show();//show()是ClassA重定义的
    base->fun(1);//fun()是Base自己的，因为直接从对象base调用
    a.fun(1, 1);//fun()是ClassA重定义的
    return 0;
}
