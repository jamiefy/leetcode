//
// Created by anranzhai on 10/3/19.
//
#include <iostream>
#include <map>

std::string intToRoman(int num) {
    if(num==0)return "";
    else if(num>=1&&num<4){
        std::string str(num,'I');
        return str;
    }
    else if(num==4)
        return "IV";
    else if(num<9){
        return "V"+intToRoman(num%5);
    }
    else if(num==9)
        return "IX";
    else if(num<40){
        std::string str(num/10,'X');
        return str+intToRoman(num%10);
    }
    else if(num<=49)
        return "XL"+intToRoman(num%10);
    else if(num<90)
        return "L"+intToRoman(num%50);
    else if(num<100)
        return "XC"+intToRoman(num%90);
    else if(num<400){
        std::string str(num/100,'C');
        return str+intToRoman(num%100);
    }
    else if(num>=400&&num<500){
        return "CD"+intToRoman(num%400);
    }
    else if(num<900)
        return "D"+intToRoman(num%500);
    else if(num<1000)
        return "CM"+intToRoman(num%900);
    else if(num<=3999){
        std::string str(num/1000,'M');
        return str+intToRoman(num%1000);
    } else
        return "";

}

std::string intToRomanImp(int num) {
    std::map<int,std::string> mapRom{{1,"I"},{4,"IV"},{5,"V"},{9,"IX"},{10,"X"},
                                     {40,"XL"},{50,"L"}, {90,"XC"},{100,"C"},
                                     {400,"CD"},{500,"D"},{900,"CM"},{1000,"M"}};
    std::map<int,std::string>::reverse_iterator reverseIterator=mapRom.rbegin();
    std::string ret;

    while(reverseIterator!=mapRom.rend()){
        if(num>=reverseIterator->first){
            ret+=reverseIterator->second;
            num-=reverseIterator->first;
        } else
            reverseIterator++;
    }
    return ret;
}

int romanToInt(std::string s) {
    std::map<std::string,int> mapRom{{"I",1},{"IV",4},{"V",5},{"IX",9},{"X",10},
                                     {"XL",40},{"L",50}, {"XC",90},{"C",100},
                                     {"CD",400},{"D",500},{"CM",900},{"M",1000}};
    int num=0,cur=0;
    while(cur<s.size()){
        auto before=mapRom.find(s.substr(cur,1));
        std::map<std::string,int>::iterator behind;
        if(cur+1<s.size()){
            behind=mapRom.find(s.substr(cur+1,1));
            if(before->second<behind->second){
                num+=mapRom.find(s.substr(cur,2))->second;
                cur+=2;
                continue;
            }
        }
        num+=before->second;
        cur++;
    }
    return num;
}

int romanToIntImp(std::string s) {
    std::map<std::string,int> mapRom{{"I",1},{"IV",3},{"V",5},{"IX",8},{"X",10},
                                     {"XL",30},{"L",50}, {"XC",80},{"C",100},
                                     {"CD",300},{"D",500},{"CM",800},{"M",1000}};
//    if(s=="")return 0;
    int num=mapRom.find(s.substr(0,1))->second,cur=1;
    while(cur<s.size()) {
        auto now = mapRom.find(s.substr(cur, 1));
        auto doub = mapRom.find(s.substr(cur - 1, 2));
        if (doub != mapRom.end())num += doub->second;
        else num += now->second;
        cur++;
    }
    return num;
}

int main(){
    std::cout<<romanToIntImp("III")<<std::endl;
}