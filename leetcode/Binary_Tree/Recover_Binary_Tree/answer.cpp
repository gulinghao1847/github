/*
Recover Binary Search Tree Total Accepted: 6677 Total Submissions: 29840 My Submissions
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
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

/*
remember to update information
*/
class Solution {
private:
    TreeNode* first;
    TreeNode* second;
    TreeNode* last;
public:
    void swap(TreeNode* a, TreeNode* b){
        int temp = a -> val;
        a -> val = b -> val;
        b -> val = temp;
    }
    
    void visit(TreeNode* root){
        if(last == NULL){
            last = root;
        }else{
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
    }
    
    void inOrderTraversal(TreeNode* root){
        if(root == NULL) return;
        inOrderTraversal(root -> left);
        visit(root);
        inOrderTraversal(root -> right);
    }
    
    void recoverTree(TreeNode *root) {
        first = second = last = NULL;
        inOrderTraversal(root);
        swap(first, second);
    }
};
