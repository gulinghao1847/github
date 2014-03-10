/*
Binary Tree Zigzag Level Order Traversal Total Accepted: 5980 Total Submissions: 23076 My Submissions
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> result;
        if(root == NULL) return result;
        vector<int> now;
        queue<TreeNode*> q;
        q.push(root);
        int lvl1 = 1;
        int lvl2 = 0;
        int lvl = 0;
        while(!q.empty()){
            TreeNode* top = q.front();
            q.pop();
            lvl1--;
            now.push_back(top -> val);
            if(top -> left){
                lvl2++;
                q.push(top -> left);
            }
            if(top -> right){
                lvl2++;
                q.push(top -> right);
            }
            if(lvl1 == 0){
                if(lvl%2 == 0){
                    result.push_back(now);
                }else{
                    reverse(now.begin(), now.end());
                    result.push_back(now);
                }
                now.clear();
                lvl1 = lvl2;
                lvl2 = 0;
                lvl++;
            }
        }
        return result; 
    }
};

