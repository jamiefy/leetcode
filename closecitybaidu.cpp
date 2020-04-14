//
// Created by anranzhai on 2020/4/14.
//
//初始每两个城市之间互相相连，m步封城操作，当x=0时y直接封城，x!=0时关闭x、y之间的通道，若m步之后城市未封城输出0，若封城输出封城的操作号
#include <iostream>
#include <vector>
#include <set>//set只存储键值,multiset可存储重复键值
using namespace std;


int main() {
    int n, m,s;
    cin >> n>>m>>s;
    int x,y;
    //vector存储下标对应的城市是否自己闭城
    vector<bool> cityClose(n+1, false);
    set<int> cityset;
    for(int i=1;i<=n;i++){
        cityset.emplace(i);
    }
    //vector存储与下标对应的城市相连接的城市,不包括自己，当set为空时也算做下标对应的城市闭城（使用set可以判断某城市是否和下标对应城市相连）
    vector<set<int>> city(n+1,cityset);
    for(int i=1;i<n+1;i++) {
        city[i].erase(i);
    }
    for(int i=1;i<=m;i++) {
        cin >> x >> y;
        if (x == 0) {
            cityClose[y] = true;
            for (int j = 1; j <= n; j++) {
                if (!cityClose[i] && city[i].count(y) != 0)
                    city[i].erase(y);
            }
        } else {
            if (!cityClose[x] && city[x].count(y) != 0)
                city[x].erase(y);
            if (!cityClose[y] && city[y].count(x) != 0)
                city[y].erase(x);
        }
        if (cityClose[s] || city[s].empty()) {
            cout << i;
            return 0;
        }
    }
    cout<<0;
    return 0;
}
