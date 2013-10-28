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
    TreeNode* run(vector<TreeNode*>& result, int begin, int end, int n){
        if(begin > end) return NULL;
        for(int i = begin; i <= end; i++){
            TreeNode* root = new TreeNode(i + 1);
            if(begin == 0 && end == n - 1) result.push_back(root);
            root -> left = run(result, begin, i - 1, n);
            root -> right = run(result, i + 1, end, n);
        }
    }
    vector<TreeNode *> generateTrees(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<TreeNode*> result;
        if(n < 0) return result;
        if(n == 0) {result.push_back(NULL); return result;}
        run(result, 0, n - 1, n);
        return result;
    }
};