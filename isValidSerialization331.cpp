//
// Created by anranzhai on 2020/5/4.
//
#include <iostream>
#include <cstring>
using namespace std;
bool isValidSerialization(string preorder) {
    int slot=1;
    char *p= strtok(const_cast<char*>(preorder.c_str()),",");
    while(slot>0&&p){
        slot--;
        if(*p!='#')
            slot+=2;
        p=strtok(NULL,",");
    }
    return p==NULL&&slot==0;
}

int main(){
    cout<<isValidSerialization("9,#,92,#,#");
}