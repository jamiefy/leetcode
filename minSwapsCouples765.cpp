//
// Created by anranzhai on 2020/4/29.
//
#include <iostream>
#include <vector>
using namespace std;
//并查集
//我们设想一下加入有两对情侣互相坐错了位置，我们至多只需要换一次。
//如果三对情侣相互坐错了位置，A1+B2,B1+C2,C1+A2。他们三个之间形成了一个环，我们只需要交换两次。
//如果四队情侣相互坐错了位置，即这四对情侣不与其他情侣坐在一起，A1+B2,B1+C2,C1+D2,D1+A2.他们四个之间形成了一个环，他们只需要交换三次并且不用和其他情侣交换，就可以将这四对情侣交换好，
//以此类推，其实就是假设k对情侣形成一个环状的错误链，我们只需要交换k - 1次就可以将这k对情侣的位置排好。
//所以问题转化成N对情侣中，有几个这样的错误环。
//我们可以使用并查集来处理，每次遍历相邻的两个位置，如果他们本来就是情侣，他们处于大小为1的错误环中，只需要交换0次。如果不是情侣，说明他们呢两对处在同一个错误环中，我们将他们合并（union），将所有的错坐情侣合并和后，答案就是情侣对 - 环个数。
//这也说明，最差的情况就是所有N对情侣都在一个环中，这时候我们需要N - 1调换。
//最好情况每对情侣已经坐好了，已经有N个大小为1的环，这时候我们需要N - N次调换。
class Solution{
public:
    void init(int n){
        for(int i=0;i<2*n;i+=2){
            parent.emplace_back(i);
            parent.emplace_back(i);
            rank.push_back((i+1)%2);
            rank.push_back((i)%2);
        }

    }
    //路径压缩
    int find(int x){
        return parent[x]==x?x:(parent[x]=find(parent[x]));
    }
    void unite(int x,int y){
        int rootx=find(x);
        int rooty=find(y);
        if(rootx==rooty)return;
        if(rank[rootx]<rank[rooty])
            parent[rootx]=rooty;
        else{
            parent[rooty]=rootx;
            if(rank[rootx]==rank[rooty])
                rank[rootx]++;
        }
    }
    int minSwapsCouples765(vector<int> &row){
        init(row.size());
        //把可以交换的块全都连在一起，形成一个大小为k的环，每个环需要交换k-1次以使情侣配对
        for(int i=0;i<row.size();i+=2){
            unite(row[i],row[i+1]);
        }
        int ans=row.size();
        for(int i=0;i<2*row.size();i++){
            if(parent[i]==i)ans--;
        }
        return ans;
    }

private:
    vector<int> parent;
    vector<int> rank;
};


//贪心算法
//时间复杂度: O(N^2)，其中 NN 为情侣对的数量。
//空间复杂度: O(1)，互相交换不需要开辟额外的空间。
int minSwapsCouples(vector<int> &row){
    int ans=0;
    for(int i=0;i<row.size();i+=2){
        int x=row[i];
        //x异或1=最低位取相反数
        if(row[i+1]==(x^1))continue;
        ans++;
        //如果情侣未配对，在该位之后寻找另一位与之配对-交换
        for(int j=i+1;j<row.size();j++){
            if(row[j]==(x^1)){
                row[j]=row[i+1];
                row[i+1]=x^1;
                break;
            }
        }
    }

}

int main(){
    vector<int> vec{0,2,1,3};
    Solution s;
    cout<<s.minSwapsCouples765(vec);
}