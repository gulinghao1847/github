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
    int max(int a, int b){
        return a>b?a:b;
    }
    
    int maxDepth(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL){
            return 0;
        }
        
        return max(maxDepth(root -> left), maxDepth(root -> right)) + 1;
    }
};