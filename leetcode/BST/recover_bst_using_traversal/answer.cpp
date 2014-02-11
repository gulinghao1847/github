/*
Recover Binary Search Tree Total Accepted: 4611 Total Submissions: 21004 My Submissions
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.

Discuss


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
private:
    TreeNode* last;
    TreeNode* first;
    TreeNode* second;
public:
    void visit(TreeNode* root){
        if(last == NULL){
            last = root;
            return;
        }
        if(last -> val > root -> val){
            if(first == NULL){
                first = last;
                second = root;
            }else{
                second = root;
            }
        }
         last = root;
    }
    void inOrderTraversal(TreeNode* root){
        if(root == NULL) return;
        inOrderTraversal(root -> left);
        visit(root);
        inOrderTraversal(root -> right);
    }
    void swap(TreeNode* first, TreeNode* second){
        int temp;
        temp = second -> val;
        second -> val= first -> val;
        first -> val = temp;
    }
    void recoverTree(TreeNode *root) {
        last = first = second = NULL;
        inOrderTraversal(root);
        if(first == NULL) return;
        swap(first, second);
    }
};

