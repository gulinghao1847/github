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
    int min(int a, int b){
        return a>b?b:a;
    }
    int minDepth(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL) return 0;
        if(root -> left == NULL && root -> right == NULL){
            return 1;
        }
        
        if(!root -> left) return (minDepth(root -> right) + 1); 
        
        if(!root -> right) return (minDepth(root -> left) + 1);
        
        return min(minDepth(root -> left), minDepth(root -> right)) + 1;
    }
};