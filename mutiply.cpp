//
// Created by 54293 on 2019/10/28.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

//乘法不是对应位相乘，每位都应与对方每位相乘
std::string multiplyW(std::string num1, std::string num2) {
    std::vector<int> multiplyVec;
    int len1=num1.size();
    int len2=num2.size();
    int  carry=0,index1=len1-1,index2=len2-1;
    int n1=0,n2=0;
    while(index1>=0&&index2>=0){
        n1=num1[index1]-'0';
        n2=num2[index2]-'0';
        multiplyVec.emplace_back((n1*n2+carry)%10);
        carry=(n1*n2+carry)/10;
        index1--;
        index2--;
    }
    if(index1<0){
        while(index2>=0){
            n2=num2[index2]-'0';
            multiplyVec.emplace_back((n2+carry)%10);
            carry=(n1+carry)/10;
            index2--;
        }
    } else{
        while(index1>=0){
            n1=num1[index1]-'0';
            multiplyVec.emplace_back((n1+carry)%10);
            carry=(n1+carry)/10;
            index1--;
        }
    }
    if(carry!=0)
        multiplyVec.emplace_back(carry);
    std::string multiplyStr;
    for(auto c:multiplyVec){
        multiplyStr+=(char)(c+'0');
    }
    return multiplyStr;
}

//普通竖式运算思想，将每一位num2与num1相乘结果进一步累加
//时间复杂度：O(MN)。M,N 分别为 num1 和 num2 的长度。
//空间复杂度：O(M+N)。用于存储计算结果。
std::string multiply(std::string num1,std::string num2){
    //有一个数为0时直接返回0避免返回多个0的字符串
    if(num1=="0"||num2=="0")
        return "0";
    int len1=num1.size();
    int len2=num2.size();
    //保证len1>len2，否则如6*501会出错
    if(len1<len2){
        return multiply(num2,num1);
    }
    std::vector<std::vector<int>> multiplyVec(len2);
    for(int i=len2-1;i>=0;i--){
        int  carry=0,num=0;
        for(int j=len1-1;j>=0;j--){
            num=(num2[i]-'0')*(num1[j]-'0')+carry;
            multiplyVec[len2-1-i].emplace_back(num%10);
            carry=num/10;
        }
        if(carry)multiplyVec[len2-1-i].emplace_back(carry);
    }
    std::string ret;
    int carry=0,count=1;
    while(!multiplyVec.empty()){
        int sum=carry;
        for(int index=0;index<count;index++){
            sum+=multiplyVec[index].empty()?0:multiplyVec[index][0];
            multiplyVec[index].erase(multiplyVec[index].begin());
        }
        carry=sum/10;
        ret+=(char)(sum%10+'0');
        if(multiplyVec[0].empty()){
            while(multiplyVec[0].empty()){
                //当一行的每个数都使用过之后擦除该行
                multiplyVec.erase(multiplyVec.begin());
                //下降阶段
                count--;
                //如果删除了多行，multiplyVec可能在删除最后一行之后为空，那下一个multiplyVec[0]使用就会出错
                //所以应该在删除每一行之后判断multiplyVec是否为空，为空则跳出循环
                if(multiplyVec.empty())break;
            }
        }
        //平稳阶段
        else if(count==multiplyVec.size()){
            continue;
        } else
            //上升阶段
            count++;
    }
    if(carry)ret+=(char)(carry+'0');
    std::reverse(ret.begin(),ret.end());
    return ret;
}

//普通竖式运算思想，将每一位num2与num1相乘结果进一步累加，num2除了第一位的其他位与num1运算的结果
//需要补0，补零就不用保证num2的长度小于num1的长度,思路更易于理解但是时间和空间消耗增加
//时间复杂度：O(MN)。M,N 分别为 num1 和 num2 的长度。
//空间复杂度：O(M+N)。用于存储计算结果。
std::string multiplyPaddingZero(std::string num1,std::string num2){
    //有一个数为0时直接返回0避免返回多个0的字符串
    if(num1=="0"||num2=="0")
        return "0";
    int len1=num1.size();
    int len2=num2.size();
    std::vector<std::vector<int>> multiplyVec(len2);
    for(int i=len2-1;i>=0;i--){
        int  carry=0,num=0;
        for(int count=len2-1-i;count>0;count--){
            multiplyVec[len2-1-i].emplace_back(0);
        }
        for(int j=len1-1;j>=0;j--){
            num=(num2[i]-'0')*(num1[j]-'0')+carry;
            multiplyVec[len2-1-i].emplace_back(num%10);
            carry=num/10;
        }
        if(carry)multiplyVec[len2-1-i].emplace_back(carry);
    }
    std::string ret;
    int carry=0;
    while(!multiplyVec.empty()){
        int sum = carry;
        for(int index=0;index<multiplyVec.size();index++){
                sum+=multiplyVec[index][0];
                multiplyVec[index].erase(multiplyVec[index].begin());
        }
        carry=sum/10;
        ret+=(char)(sum%10+'0');
        while(!multiplyVec.empty()&&multiplyVec[0].empty())multiplyVec.erase(multiplyVec.begin());
    }
    if(carry)ret+=(char)(carry+'0');
    std::reverse(ret.begin(),ret.end());
    return ret;
}

//优化竖式.时间复杂度：O*(*M N*)O∗(∗MN∗)。M,NM,N 分别为 num1 和 num2 的长度;空间复杂度：O*(M+N)O∗(M+N)。用于存储计算结果.
//虽然两者时间复杂度和空间复杂度相同，但优化竖式执行速度极大提高，空间消耗成半减小，普通竖式耗时主要还是对每步计算的字符串相加这个过程
//乘数 num1 位数为 MM，被乘数 num2 位数为 NN， num1 x num2 结果 res 最大总位数为 M+N
//num1[i] x num2[j] 的结果为 tmp(位数为两位，"0x","xy"的形式)，其第一位位于 res[i+j]，第二位位于 res[i+j+1]。
std::string multiplyOptimization(std::string num1,std::string num2) {
    //有一个数为0时直接返回0避免返回多个0的字符串
    if (num1 == "0" || num2 == "0")
        return "0";
    int len1 = num1.size();
    int len2 = num2.size();
    std::vector<int> multiply(len1+len2);
    for(int i=len1-1;i>=0;i--){
        int n1=num1[i]-'0';
        for(int j=len2-1;j>=0;j--){
            int n2=num2[j]-'0';
            int sum=multiply[i+j+1]+n1*n2;
            multiply[i+j+1]=sum%10;
            multiply[i+j]+=sum/10;
        }
    }
    std::string ret;
    for(int i=0;i<len1+len2;i++){
        if(i==0&&multiply[0]==0)continue;
        ret+=(char)(multiply[i]+'0');
    }
    return ret;
}


int main(){
    std::cout<<multiplyOptimization("123","456")<<std::endl;
}