/*Symmetric Tree Total Accepted: 11890 Total Submissions: 37260 My Submissions
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.

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

/*recursion
*/
class Solution {
public:
    bool isSymmetricHelper(TreeNode* a, TreeNode* b){
        if(!a && !b) return true;
        if(!a || !b) return false;
        return a -> val == b -> val &&  isSymmetricHelper(a -> left, b -> right) && isSymmetricHelper(a -> right, b -> left);  
    }
    
    bool isSymmetric(TreeNode *root) {
        if(!root) return true;
        return isSymmetricHelper(root -> left, root -> right);
    }
};

/*
iteration
*/
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if(!root) return true;
        queue<TreeNode*> l;
        queue<TreeNode*> r;
        l.push(root);
        r.push(root);
        while(!l.empty()){
            TreeNode* left = l.front();
            TreeNode* right = r.front();
            l.pop();
            r.pop();
            if(!left && !right) continue;
            if(!left || !right) return false;
            if(left -> val != right -> val) return false;
            l.push(left -> left);
            l.push(left -> right);
            r.push(right -> right);
            r.push(right -> left);
        }
        return true;
    }
};

