/*
Sum Root to Leaf Numbers Total Accepted: 6974 Total Submissions: 24445 My Submissions
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.
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
    void calSum(TreeNode* root, int& result, int sum){
        if(root == NULL){
            return;
        }
        sum = sum*10 + root -> val;
        if(root -> left == NULL && root -> right == NULL){
            result = result + sum;
        }
        
        calSum(root -> left, result, sum);
        calSum(root -> right, result, sum);
    }
    int sumNumbers(TreeNode *root) {
        int result = 0;
        calSum(root, result, 0);
        return result;
    }
};
