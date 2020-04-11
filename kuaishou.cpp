//
// Created by anranzhai on 2020/4/11.
//
#include <iostream>
#include <vector>
using namespace std;
int main(){
    int groupNum;
    cin>>groupNum;
    vector<int> money;
    int m;
    for(int i=0;i<groupNum;i++){
        cin>>m;
        money.emplace_back(m);
    }
    if(groupNum==0)
        return 0;
    int left=money[0],right=money[groupNum-1];
    int max=0;
    for(int i=1,j=groupNum-2;i<=j;){
        if(left==right){
            if(max<left){
                max=left;
                if(i!=j)
                    left+=money[i++];
            }
        }
        else if(left<right){
            left+=money[i++];
        } else
            right+=money[j--];
    }
    if(left==right)
        max=left;
    cout<<max<<endl;
}
