/*
Unique Binary Search Trees Total Accepted: 8005 Total Submissions: 22719 My Submissions
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
class Solution {
public:
    int numTrees(int n) {
        int result = 0;
        if(n <= 0) return 0;
        if(n == 1) return 1;
        for(int i = 0; i < n; i++)
        {
            int l = numTrees(i);
            int r = numTrees(n - i - 1);
            if(!l) result += r;
            else if(!r) result += l;
            else if(l && r) result += l*r;
        }
        return result;
    }
};

