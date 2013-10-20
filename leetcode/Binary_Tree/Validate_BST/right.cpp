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
    TreeNode* last;
public:
    bool run(TreeNode* root){
        if(root == NULL){
            return true;
        }
        
        bool left = run(root -> left);
        
        if(last == NULL){
            last = root;
        }else{
            if(last -> val >= root -> val){
                return false;
            }else{
                last = root;
            }
        }
        
        bool right = run(root -> right);
        
        return left&&right;
    }
    bool isValidBST(TreeNode *root) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        last = NULL;
        return run(root);
    }
};