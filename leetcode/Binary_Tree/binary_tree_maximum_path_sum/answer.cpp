/*
Binary Tree Maximum Path Sum Total Accepted: 5382 Total Submissions: 28248 My Submissions
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.
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
class Solution {
public:
    int findMaxSum(TreeNode* root, int& max_sum){
        if(root == NULL){
            return INT_MIN;
        }
        if(root -> left == NULL && root -> right == NULL){
            max_sum = max_sum < root -> val ? root -> val : max_sum;
            return root -> val;
        }
        
        int leftMax = findMaxSum(root -> left, max_sum);
        int rightMax = findMaxSum(root -> right, max_sum);
        //max_sum
        int childMax = max(leftMax, rightMax);
        int whole = root -> val;
        if(root -> left) whole += leftMax;
        if(root -> right) whole += rightMax;
        max_sum = max(max(root -> val, childMax + root -> val), max(whole, max_sum));
        //return value:
        int ret = max(root -> val, root -> val + childMax);
        return ret;
    }
    int maxPathSum(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int max_sum = INT_MIN;
        findMaxSum(root, max_sum);
        return max_sum;
    }
};

