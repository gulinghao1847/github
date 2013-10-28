/*
Unique Binary Search Trees Total Accepted: 2024 Total Submissions: 6019 My Submissions
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
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int count = 0;
        if(n == 0) return 0;
        if(n == 1) return 1;
        for(int i = 1; i <= n; i++){
            int l = numTrees(i - 1);
            int r = numTrees(n - i);
            if(!l) count+=r;
            else if(!r) count+=l;
            else if(l&&r)count+=l*r;
        }
        return count;
    }
};