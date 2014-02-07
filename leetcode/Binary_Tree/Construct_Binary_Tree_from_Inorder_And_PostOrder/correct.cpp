/*
Construct Binary Tree from Inorder and Postorder Traversal Total Accepted: 4060 Total Submissions: 16164 My Submissions
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
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
    TreeNode* run(vector<int> &inorder, int inBegin, int inEnd, vector<int>& postorder, int postBegin, int postEnd){
        int s1 = inorder.size();
        int s2 = postorder.size();
        if(inBegin > inEnd || postBegin > postEnd){
            return NULL;
        }
        //find the root in postorder array
        TreeNode* root = new TreeNode(postorder[postEnd]);
        
        //find the root in inorder array
        int idx = 0;
        for(idx = inBegin; idx <= inEnd; idx++){
            if(inorder[idx] == root -> val)break;
        }
        
        int sizeLeft = idx - inBegin;
        int sizeRight = inEnd - idx;
        
        root -> left = run(inorder, inBegin, idx - 1, postorder, postBegin, postBegin + sizeLeft - 1);
        root -> right = run(inorder, idx + 1, inEnd, postorder, postBegin + sizeLeft, postEnd - 1);
        return root;
    }
    
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        return run(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
};