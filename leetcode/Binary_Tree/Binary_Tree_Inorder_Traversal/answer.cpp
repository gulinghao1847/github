/*
Binary Tree Inorder Traversal Total Accepted: 8322 Total Submissions: 24416 My Submissions
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

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
    void inorderTra(TreeNode* root, vector<int>& res){
        if(root -> left){
            inorderTra(root -> left, res);
        }
        res.push_back(root -> val);
        if(root -> right){
            inorderTra(root -> right, res);
        }
    }
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        if(root == NULL){
            return res;
        }
        inorderTra(root, res);
        return res;
    }
};

