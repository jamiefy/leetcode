//
// Created by anranzhai on 2020/3/26.
//
#include <bits/stdc++.h>
class B1
{
public:
    B1(){std::cout<<"B1::B1()!<"<<std::endl;}
    void f() {std::cout<<"i'm here!"<<std::endl;}
};

class V1: public B1
{
public:
    V1(){std::cout<<"V1::V1()!<"<<std::endl;}
};

class D1: virtual public V1
{
public:
    D1(){std::cout<<"D1::D1()!<"<<std::endl;}
};

class B2
{
public:
    B2(){std::cout<<"B2::B2()!<"<<std::endl;}
};

class B3
{
public:
    B3(){std::cout<<"B3::B3()!<"<<std::endl;}
};

class V2:public B1, public B2
{
public:
    V2(){std::cout<<"V2::V2()!<"<<std::endl;}
};

class D2:virtual public V2, public B3
{
public:
    D2(){std::cout<<"D2::D2()!<"<<std::endl;}
};

class M1
{
public:
    M1(){std::cout<<"M1::M1()!<"<<std::endl;}
};

class M2
{
public:
    M2(){std::cout<<"M2::M2()!<"<<std::endl;}
};

class X:public D1, public D2
{
    M1 m1;
    M2 m2;
};
int main(int argc, const char * argv[]) {
    X x;
}
