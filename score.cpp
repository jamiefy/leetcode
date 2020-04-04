#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
int main(){
    int numOfClass=0;
    std::cin>>numOfClass;
    std::vector<int> scoreOfClass;
    int score;
    for(int i=0;i<numOfClass;i++){
        std::cin>>score;
        scoreOfClass.emplace_back(score);
    }
   //float sum=std::accumulate(scoreOfClass.begin(),scoreOfClass.end(),0);
    int queNum=0;
    std::vector<float> cntVec;
    std::cin>>queNum;
    int num;
    for(int i=0;i<queNum;i++){
        std::cin>>num;
        float cnt=0;
        std::for_each(scoreOfClass.begin(),scoreOfClass.end(),[=,&cnt](const int &sc){
            if(sc<=scoreOfClass[num-1])
                cnt++;
        });
        cntVec.emplace_back(cnt);
    }
    for(int i=0;i<queNum;i++){
        std::cout<<std::fixed<<std::showpoint<<(cntVec[i]-1.0)/numOfClass*100.0<<std::endl;
    }
}