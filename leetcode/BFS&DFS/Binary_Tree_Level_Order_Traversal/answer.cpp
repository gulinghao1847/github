/*
Binary Tree Level Order Traversal Total Accepted: 6259 Total Submissions: 20758 My Submissions
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
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
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        vector<int> lvl;
        if(root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);
        int lvl1 = 1;
        int lvl2 = 0;
        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            lvl1--;
            lvl.push_back(node -> val);
            if(node -> left){
                q.push(node -> left);
                lvl2++;
            }
            if(node -> right){
                q.push(node -> right);
                lvl2++;
            }
            if(lvl1 == 0){
                lvl1 = lvl2;
                lvl2 = 0;
                res.push_back(lvl);
                lvl.clear();
            }
        }
        return res;
    }
};
