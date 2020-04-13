#include<iostream>
#include <vector>
using namespace std;
//模拟二进制取余，判断所有余数是否都是1
class Solution {
public:
    /**
     * 返回无重复幂因子的 N进制完美数之和的所有幂因子
     * @param R int整型
     * @param N int整型 N进制
     * @return int整型vector
     */
    vector<int> GetPowerFactor(int R, int N) {
        vector<int> yu;
        vector<int> result;
        while(R > 0){
            int temp = R % N;
            yu.push_back(temp);
            R = R / N;
        }
        for(int i=0;i<yu.size();i++){
            if(yu[i] == 1)
                result.push_back(i);
            else if(yu[i] > 1)
                return vector<int>(0,0);
        }
        return result;
    }
};

int main(){
    Solution solution;
    vector<int> result = solution.GetPowerFactor(39,3);
    for(auto i:result)
        cout<<i<<' ';
    return 0;
}
