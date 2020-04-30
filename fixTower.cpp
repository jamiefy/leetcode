//
// Created by anranzhai on 2020/4/30.
//
// 小招正在玩一款修塔游戏：系统中有n座高塔，每座高塔由若干个高度相同的方块堆砌而成。修塔游戏的规则为：
//       （1）每次从最高塔的塔尖拿走一个方块
//       （2）每次在最低塔的塔尖堆砌一个方块（注意读题，没说每次堆砌必须保证已经从最高塔尖拿走一个方块，也就是说没说总共只有这么多方块）
//小招每次只能完成上述两个动作中的一个动作。游戏的目标是使n座高塔中至少有k座高塔的高度相同，请问小招最少需要多少次才能完成游戏。
#include<bits/stdc++.h>
#define ll long long
using namespace std;
//排序->从左或右数的第k个数一定包括在k个数里->数学运算
//时间复杂度O(nlogn)
//空间复杂度O(1),固定常数空间202020
#define N 202020
int cas, n, m, tot, K;
int a[N];
int s[N];
ll sum[N];
int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        s[a[i]]++;
        if (s[a[i]] >= K) {
            printf("0\n");
            return 0;
        }
    }
    sort (a + 1, a + n + 1);
    //前i高度总共包括的方块数
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    //至少k个，如果是前k个则肯定包含a[k]
    ll ans1 = (ll)a[K] * K - sum[K];
    int tmp = K + 1;
    //如果后面有跟a[k]相等的则前面可少补成一个a[k]高度
    while(tmp <= n && a[tmp] == a[K]) tmp ++, ans1--;
    //如果是后k个则肯定包含a[n-k+1]
    ll ans2 = sum[n] - sum[n - K] - (ll)a[n - K + 1] * K;
    tmp = n - K;
    //如果前面有跟a[n-k+1]相等的则可少减成一个a[n-k+1]高度
    while(tmp >= 1 && a[tmp] == a[n - K + 1]) tmp --, ans2--;
    printf("%lld\n", min(ans1, ans2));
    return 0;
}

//递归
//int mincnt=INT32_MAX;
//void minDoesTake(map<int,int> heights,int cur,int k) {
//    auto point = heights.rbegin();
//    point->second--;
//    cur++;
//    if (heights.count(point->first - 1)){
//        //一定要在此处判断是否达到k个，而不应该在开头判断最低高度是否达到k个，因为最后达到k个的不一定是最低高度
//        if(++heights[point->first - 1]==k){
//            mincnt=std::min(mincnt,cur);
//            return;
//        }
//    }
//    else
//        heights[point->first - 1] = 1;
//    if (!point->second)heights.erase(point->first);
//    minDoesTake(heights, cur, k);
//}
//
//void minDoesBring(map<int,int> heights,int cur,int k){
//    if(heights.begin()->second==k){
//        mincnt=std::min(mincnt,cur);
//        return;
//    }
//
//    auto point=heights.begin();
//    point->second--;
//    cur++;
//    if(heights.count(point->first+1)){
//        if(++heights[point->first +1]==k){
//            mincnt=std::min(mincnt,cur);
//            return;
//        }
//    }
//    else
//        heights[point->first+1]=1;
//    if(!point->second)heights.erase(point->first);
//    minDoesBring(heights,cur,k);
//}
//
//int main() {
//    int n,k;
//    cin>>n>>k;
//    map<int,int> heights;
//    int sum=0;
//    for(int i=0;i<n;i++){
//        int x;
//        cin>>x;
//        if(heights.count(x))
//            heights[x]++;
//        else
//            heights[x]=1;
//        if(heights[x]==k){
//            cout<<0<<endl;
//            return 0;
//        }
//        sum+=x;
//    }
//    minDoesTake(heights,0,k);
//    minDoesBring(heights,0,k);
//
//    std::cout << mincnt<< std::endl;
//    return 0;
//}