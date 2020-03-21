//
// Created by anranzhai on 2020/3/21.
//
#include <iostream>
#include <vector>
class Solution {
    //m == seats.length
    //n == seats[i].length
    //1 <= m <= 8
    //1 <= n <= 8
    int memory[8][1 << 8];
    std::vector<int> compressed_seats;
    int f(int X, int row_num, int width) {
        if (memory[row_num][X] != -1)
            return memory[row_num][X];
        int ans = 0;
        for (int scheme = 0; scheme != (1 << width); ++scheme) {
            //如果该scheme在没座位的位置安排了学生或者存在两个位置相邻的情况，则直接跳过
            if (scheme & ~X || scheme & (scheme << 1))
                continue;
            int curans = 0;
            //判断当前scheme中1的个数也就是座位上做的学生数
            for (int j = 0; j != width; ++j)
                if ((1 << j) & scheme)
                    ++curans;
            //当到达最后一行时停止继续向下，如果当前curans大于至今最大的ans即坐座位上的学生数则使ans=curans
            if (row_num == compressed_seats.size() - 1)
                ans = std::max(ans, curans);
            else {
                //递归向下一行，当前行影响下一行，将下一行可坐学生的有座位位置作为递归参数next_seats
                int next_seats = compressed_seats[row_num + 1];
                next_seats &= ~(scheme << 1);
                next_seats &= ~(scheme >> 1);
                ans = std::max(ans, curans + f(next_seats, row_num + 1, width));
            }
        }
        //得到该行该scheme能坐的最多学生数
        memory[row_num][X] = ans;
        return ans;
    }

    //压缩每行有座位的位置为1，制作二进制状态行
    int compress(std::vector<char>& row) {
        int ans = 0;
        for (char c : row) {
            ans <<= 1;
            if (c == '.')
                ++ans;
        }
        return ans;
    }

public:
    int maxStudents(std::vector<std::vector<char>>& seats) {
        for (int i = 0; i != seats.size(); ++i)
            for (int j = 0; j != (1 << seats[0].size()); ++j)
                memory[i][j] = -1;
        for (auto row: seats)
            //把目前有座位的状态行压到座位压缩状态数组中
            compressed_seats.push_back(compress(row));
        return f(compressed_seats[0], 0, seats[0].size());
    }
};
//题解：https://leetcode-cn.com/problems/maximum-students-taking-exam/solution/can-jia-kao-shi-de-zui-da-xue-sheng-shu-by-leetcod/