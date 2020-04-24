//
// Created by anranzhai on 2020/4/20.
//
#include <iostream>
#include <cstring>

char* strcat(char* dest, const char* src) {
    char* d = dest;
    d+=strlen(dest);
    dest[2]='3';
    while(*src!='\0') {
        *d++=*src++;
    }
    *d='\0';
    return dest;
}

int main(){
    char dest[20]="hello";//dest字符串数组不能是字符串指针，不然内存会溢出
    char* src="world";
    std::cout<<strcat(dest,src);
}

//#include <stdio.h>
//
//char* strcat(char *str1,char *str2)
//{
//    char* tempt = str1;
//
//    while(*str1!='\0')
//    {
//        str1++;
//    }
//
//    while(*str2!='\0')
//    {
//        *str1 = *str2;
//        str1++;
//        str2++;
//    }
//
//    *str1 = '\0';
//    return tempt;
//}
//
//int main()
//{
//    char a[20] = "hello";
//    char b[20] = ",world!";
//    printf("%s\n",strcat(a,b));
//    return 0;
//}