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
    void run(vector<vector<int>>&result, vector<int>& now, TreeNode* root, int value, int target){
        if(root == NULL) return;
        int sum = value + root -> val;
        
        now.push_back(root -> val);               // every node need to push its val;
        
        if(root -> left == NULL && root -> right == NULL){   //leafNode
            if(sum == target){
                result.push_back(now);
            }
            now.pop_back();      //pop before return
            return;
        }
        
        run(result, now, root -> left, sum, target);
        run(result, now, root -> right, sum, target);
        now.pop_back();     //pop before return;
        
        return;
    }
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int>> result;
        vector<int> now;
        if(root == NULL){
            return result;
        }
        run(result, now, root, 0, sum);
        return result;
    }
};