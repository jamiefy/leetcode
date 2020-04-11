//
// Created by anranzhai on 2020/4/11.
//
#include <iostream>
#include<vector>
using namespace std;
//vector自定义类必须有默认构造函数
class myInt
{
public:
    myInt(int a ,int b):m_li(a),m_ri(b)
    {}
    void print()
    {
        std::cout<<"m_li = "<<this->m_li<<std::endl;
        std::cout<<"m_ri = "<<this->m_ri<<std::endl;
    }

    void set(int li, int ri)
    {
        this->m_li = li;
        this->m_ri = ri;
    }
private:
    int m_li;
    int m_ri;
};

int main() {

    std::vector<myInt> v1(30);
    for (std::vector<myInt>::iterator iter = v1.begin(); iter != v1.end(); iter++) {
        iter->print();
    }

    return 0;
}