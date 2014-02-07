/*
Binary Tree Level Order Traversal II Total Accepted: 5087 Total Submissions: 16368 My Submissions
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7]
  [9,20],
  [3],
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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<vector<int>> res;
        vector<int> now;
        if(root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);
        int lvl1 = 1;
        int lvl2 = 0;
        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            lvl1--;
            now.push_back(node -> val);
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
                res.push_back(now);
                now.clear();
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
