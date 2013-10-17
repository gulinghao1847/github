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
    bool run(TreeNode* root, int sum, int now){
        if(root == NULL){
            return false;
        }
        int value = root -> val + now;
        
        if(root -> left ==  NULL && root -> right == NULL){
            if(value == sum){
                return true;
            }else{
                return false;
            }
        }
        
        //if(value != sum) return false;
        
        return run(root -> left, sum, value)||run(root -> right, sum, value);
    }
    
    bool hasPathSum(TreeNode *root, int sum) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(root == NULL){
            return false;
        }
        bool ret = run(root, sum, 0);
        return ret;
    }
};