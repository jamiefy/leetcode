//
// Created by anranzhai on 2020/5/17.
//
#include <iostream>
#include <vector>
using namespace std;
vector<int> tree;
int n;

void buildTree(vector<int> nums) {
    for (int i = n, j = 0;  i < 2 * n; i++,  j++)
        tree[i] = nums[j];
    for (int i = n - 1; i > 0; --i)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
}
//时间复杂度：O(n)。因为我们在 for 循环的每次迭代中计算一个节点的和。而一个线段树中大约有2n 个节点。
//这可以通过以下方式证明：具有 n 个元素的数组线段树有 n 个叶节点（数组元素本身）。每一层中的节点数是下面一层中节点数的一半。
//因此，如果我们按层对节点数求和，二叉树总共有2^h-1个节点，共有2^(h-1)个叶节点。
//空间复杂度：O(n)，我们用了 2n 的额外空间来存储整个线段树。

//更新线段树 :当我们更新数组中某个索引 i处的元素时，我们需要重建线段树，因为一些树节点上的和值也会随之产生变化。我们将再次使用
//自下而上的方法。首先更新存储 a[i]a[i] 元素的叶节点。从那里我们将一路向上，直到根节点，并用其子节点值的总和来更新每个父节点的值。
void update(int pos, int val) {
    pos += n;
    tree[pos] = val;
    while (pos > 0) {
        int left = pos;
        int right = pos;
        if (pos % 2 == 0) {
            right = pos + 1;
        } else {
            left = pos - 1;
        }
        // parent is updated after child is updated
        tree[pos / 2] = tree[left] + tree[right];
        pos /= 2;//pos等于2或者3时除以2等于1，进入循环后会更改tree[0]的值但是不影响结果
    }
}
//时间复杂度：O(logn)。因为有几个树节点的范围包括第 i 个数组元素，每个层上都有一个。共有log(n) 层。
//空间复杂度：O(1)。

//区域和检索：我们可以通过以下方式使用线段树进行区域和检索 [L,R]：算法保持循环不变：l≤r 以及已经算出 [L…l] 和 [r…R] 的总和，
//其中 l 和 r 分别是计算总和时的左边界和右边界。每次迭代的范围 [l,r] 都会缩小，直到在算法的大约 logn 次迭代后两个边界相遇为止。
int sumRange(int l, int r) {
    // get leaf with value 'l'
    l += n;
    // get leaf with value 'r'
    r += n;
    int sum = 0;
    //当l==r时仍会进入循环进入其中一个if，把总和tree[l]加进去
    while (l <= r) {
        if ((l % 2) == 1) {
            sum += tree[l];
            l++;
        }
        if ((r % 2) == 0) {
            sum += tree[r];
            r--;
        }
        l /= 2;
        r /= 2;
    }
    return sum;
}

void NumArray(vector<int> &nums) {
    if (nums.size() > 0) {
        n = nums.size();
        tree.resize(2*n,0);
        buildTree(nums);
    }
}
