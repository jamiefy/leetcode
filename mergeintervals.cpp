//
// Created by Administator on 2019/12/11.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <stack>

//左边界排序，按左边界从小到大的顺序取区间进行判断，已知压进ret的区间满足后进的区间左边界大于前面区间的右边界，以此类推，所以每次
//判断是否能进栈只需要拿欲进栈区间左边界跟栈顶区间右边界比较
//时间复杂度：O(n^2)
//空间复杂度：O(n)
int searchMin(std::vector<std::vector<int>>& intervals){
    int min=intervals[0][0],minRow=0;
    for(int i=0;i<intervals.size();i++){
        if(intervals[i][0]!=INT32_MAX && min>intervals[i][0]){
            min=intervals[i][0];
            minRow=i;
        }
    }
    return minRow;
}

std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    int num=intervals.size();
    if(num==0)
        return intervals;
    std::vector<std::vector<int>> ret;
    int initialRow=searchMin(intervals);
    std::vector<int> initialVec=intervals[initialRow];
    intervals[initialRow][0]=INT32_MAX;
    ret.emplace_back(initialVec);
    for(int i=1;i<intervals.size();i++){
        int minRow=searchMin(intervals);
        std::vector<int> minVec=intervals[minRow];
        intervals[minRow][0]=INT32_MAX;
        if(ret[ret.size()-1][1]>=minVec[0])
            ret[ret.size()-1][1]=std::max(ret[ret.size()-1][1],minVec[1]);
        else
            ret.emplace_back(minVec);
    }
    return ret;
}

//代码简化： 1.排序自定义比较函数 2.原地合并
//时间复杂度：O(nlgn),除去 sort 的开销，我们只需要一次线性扫描，所以主要的时间开销是排序的 O(nlgn)
//空间复杂度：O(1)
//实际运行速度是上面未简化代码的2倍
std::vector<std::vector<int>> mergeSort(std::vector<std::vector<int>>& intervals) {
    int num=intervals.size();
    if(num==0)
        return intervals;
    //(std::vector<int>& interval1,std::vector<int>& interval2)比(std::vector<int> interval1,std::vector<int> interval2)会使整个代码优化一倍的时间
    std::sort(intervals.begin(),intervals.end(),[](std::vector<int>& interval1,std::vector<int>& interval2){
        return interval1[0]<interval2[0];
    });
    for(auto it=intervals.begin();it+1!=intervals.end();){
        if(it->at(1)>=(it+1)->at(0)){
            it->at(1)=std::max(it->at(1),(it+1)->at(1));
            intervals.erase(it+1);
        } else
            it++;
    }
    return intervals;
}

//上面的优化，运行速度最快，不使用迭代器直接使用下标，不原地合并使用另一个数组存放新的区间
std::vector<std::vector<int>> mergeSortImp(std::vector<std::vector<int>>& intervals) {
    int num = intervals.size();
    if (num == 0)
        return intervals;
    //(std::vector<int>& interval1,std::vector<int>& interval2)比(std::vector<int> interval1,std::vector<int> interval2)会使整个代码优化一倍的时间
    std::sort(intervals.begin(), intervals.end(), [](std::vector<int> &interval1, std::vector<int> &interval2) {
        return interval1[0] < interval2[0];
    });
    std::vector<std::vector<int>> ret{intervals[0]};
    for(int i=1;i<intervals.size();i++){
        if(ret[ret.size()-1][1]>=intervals[i][0])
            ret[ret.size()-1][1]=std::max(ret[ret.size()-1][1],intervals[i][1]);
        else
            ret.emplace_back(intervals[i]);
    }
    return ret;
}


//把图用邻接表表示，用两个方向的有向边模拟无向边。然后，为了考虑每个顶点属于哪个连通块，我们从任意一个未被访问的节点出发，遍历相邻点，直到所有顶点都被访问过。为了效率更快，我们将所有访问过的节点
//记录在 Set 中，可以在常数时间内查询和插入。最后，我们考虑每个连通块，将所有区间合并成一个新的 Interval ，区间左端点 start 是最小的左端点，区间右端点 end 是最大的右端点。这个算法显然是正确的，
//因为这是最暴力的方法。我们对两两区间进行比较，所以可以知道他们是否重合。连通块搜索的原理是因为两个区间可能不是直接重合，而是通过第三个区间而间接重合。
//时间复杂度：O(n^2)建图的时间开销 O(V + E) = O(V) + O(E) = O(n) + O(n^2) = O(n^2)，最坏情况所有区间都相互重合，遍历整个图有相同的开销，因为 visited 数组保证了每个节点只会被访问一次。最后每个
//节点都恰好属于一个连通块，所以合并的时间开销是 O(V) = O(n)。总和为：O(n^2) + O(n^2) + O(n) = O(n^2)。运行时间超出时间限制，在n极大时不能通过。
//空间复杂度：O(n^2),根据之前提到的，最坏情况下每个区间都是相互重合的，所以两两区间都会有一条边，所以内存占用量是输入大小的平方级别。
std::map<std::vector<int>,std::set<std::vector<int>>> graph;
std::map<int,std::vector<std::vector<int>>> nodesInConnectedBlock;
std::map<std::vector<int>,bool> visited;

void buildGraph(std::vector<std::vector<int>>& intervals){
    for(auto interval:intervals){
        //一定要插入一对数值<std::vector<int>,,std::vector<std::vector<int>>并采用std::set<std::vector<int>>{}初始化
        graph.insert({interval,std::set<std::vector<int>>{}});
        visited.insert({interval, false});
    }
    for(auto interval1:intervals){
        for(auto interval2:intervals){
            //判断任意两个区间是否存在直接重叠
            if(interval1!=interval2 && interval1[0]<=interval2[1] && interval1[1]>=interval2[0]){
                graph[interval1].emplace(interval2);
                graph[interval2].emplace(interval1);
            }
        }
    }
}

void markComponentsDFSInOneConnectedBlock(std::vector<int>& interval,int num){
    std::stack<std::vector<int>> nodesStackInOneConnectedBlock({interval});
    //一定要插入一对数值<int,std::vector<std::vector<int>>并采用std::set<std::vector<int>>{}初始化
    nodesInConnectedBlock.insert({num,std::vector<std::vector<int>>{}});

    while(!nodesStackInOneConnectedBlock.empty()){
        std::vector<int> top=nodesStackInOneConnectedBlock.top();
        nodesStackInOneConnectedBlock.pop();

        if(visited[top]== false){
            nodesInConnectedBlock[num].emplace_back(top);
            //visited直接插入std::vector<int>
            visited[top]= true;
            for(auto intervalInOneConnectedBlock:graph[top]){
                if(visited[intervalInOneConnectedBlock]== false)
                    nodesStackInOneConnectedBlock.emplace(intervalInOneConnectedBlock);
            }
        }
    }
}

void buildConnectedBlock(std::vector<std::vector<int>>& intervals) {
    int num=0;
    for(auto interval:intervals){
        if(visited[interval]== false){
            markComponentsDFSInOneConnectedBlock(interval,num);
            num++;
        }
    }
}

std::vector<int> mergeNodesInConnectedBlock(std::vector<std::vector<int>>& connectedBlock){
    int minStart=connectedBlock[0][0];
    for(auto node:connectedBlock){
        minStart=std::min(node[0],minStart);
    }
    int maxEnd=connectedBlock[0][1];
    for(auto node:connectedBlock){
        maxEnd=std::max(node[1],maxEnd);
    }
    return std::vector<int>{minStart,maxEnd};
}

std::vector<std::vector<int>> mergeConnectedBlock(std::vector<std::vector<int>>& intervals) {
    buildGraph(intervals);
    buildConnectedBlock(intervals);

    std::vector<std::vector<int>> ret;
    for(int num=0;num<nodesInConnectedBlock.size();num++)
        ret.emplace_back(mergeNodesInConnectedBlock(nodesInConnectedBlock[num]));
    return ret;
}



int main(){
    std::vector<std::vector<int>> intervals{{1,2},{3,4},{2,6},{5,7}};
    std::vector<std::vector<int>> ret=mergeConnectedBlock(intervals);
    for(int i=0;i<ret.size();i++){
        std::cout<<ret[i][0]<<" "<<ret[i][1]<<std::endl;
    }
}