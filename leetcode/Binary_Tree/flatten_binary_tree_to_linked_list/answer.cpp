/*

Flatten Binary Tree to Linked List Total Accepted: 6185 Total Submissions: 23592 My Submissions
Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
click to show hints.
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
    void flatten(TreeNode *root) {
        if(root == NULL){
            return;
        }
        TreeNode* right = root -> right;
        TreeNode* leftRight = root;
        
        if(root -> left != NULL){
            root -> right = root -> left;
            root -> left = NULL;   // very important, without this sentence , the program will have runtime error
            leftRight = root -> right;
            while(leftRight -> right != NULL) leftRight = leftRight -> right;
            leftRight -> right = right;
        }
        flatten(root -> right);
    }
};

