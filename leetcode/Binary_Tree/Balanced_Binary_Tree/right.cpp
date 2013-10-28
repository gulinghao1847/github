/**
Balanced Binary Tree Total Accepted: 2220 Total Submissions: 7097 My Submissions
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
 */
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/*
本题目要注意的就是什么是balanced binary tree， 一个node 是balanced tree ， 必须左子节点是， 右子节点是， 且abs（left - right） <= 1 即自己也是
代码如下， 注意临界的判定条件， 就是递归的中止时间
*/
class Solution {
public:
    bool checkBalanced(TreeNode* root, int& len){
        if(root == NULL) {
            len = 0;
            return true;
        }
        if(root -> left == NULL && root -> right == NULL){
            len = 1;
            return true;
        }
        int left = 0;
        int right = 0;
        bool l = checkBalanced(root -> left, left);
        bool r = checkBalanced(root -> right, right);
        len = max(left, right) + 1;
        return l && r && abs(left - right) <= 1;
    }
    bool isBalanced(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int len = 0;
        return checkBalanced(root, len);
    }
};