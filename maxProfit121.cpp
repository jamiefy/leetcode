//
// Created by anranzhai on 2020/3/9.
//
#include <iostream>
#include <vector>
int maxProfit(std::vector<int>& prices) {
    int minprice = INT32_MAX, maxprofit = 0;
    for (int price: prices) {
        maxprofit = std::max(maxprofit, price - minprice);
        minprice = std::min(price, minprice);
    }
    return maxprofit;
}

int main(){
    std::vector<int> vec{7,1,5,3,6,4};
    std::cout<<maxProfit(vec);
}
