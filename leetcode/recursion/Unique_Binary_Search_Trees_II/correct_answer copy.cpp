/*
Unique Binary Search Trees II Total Accepted: 1006 Total Submissions: 3939 My Submissions
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.


OJ's Binary Tree Serialization:
The serialization of a binary tree follows a level order traversal, where '#' signifies a path terminator where no node exists below.

Here's an example:
   1
  / \
 2   3
    /
   4
    \
     5
The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
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
/*
非常经典的一道递归的题目， 当递归程序中有for loop的时候该如何处理， 仔细揣摩
*/
class Solution {
public:
    void run(vector<TreeNode*>& result, int begin, int end){
        if(begin > end){
            result.push_back(NULL);
            return;
        }
        for(int i = begin; i <= end; i++){
            vector<TreeNode*> left;
            run(left, begin, i - 1);
            vector<TreeNode*> right;
            run(right, i + 1, end);
            for(int ii = 0; ii < left.size(); ii++){
                for(int jj = 0; jj < right.size(); jj++){
                    TreeNode* root = new TreeNode(i + 1);
                    root -> left = left[ii];
                    root -> right = right[jj];
                    result.push_back(root);
                }
            }
		}
    }   
    vector<TreeNode *> generateTrees(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<TreeNode*> result;
        if(n < 0) return result;
        run(result, 0, n - 1);
        return result;
    }
};

/*
wrong version 2: because run function return vector<TreeNode*>, but it shouldn't
class Solution {
public:
    vector<TreeNode*> run(vector<TreeNode*>& result, int begin, int end){
        if(begin > end){
            result.push_back(NULL);
            return result;
        }
        for(int i = begin; i <= end; i++){
            vector<TreeNode*> left;
            run(left, begin, i - 1);
            vector<TreeNode*> right;
            run(right, i + 1, end);
            for(int ii = 0; ii < left.size(); ii++){
                for(int jj = 0; jj < right.size(); jj++){
                    TreeNode* root = new TreeNode(i);
                    root -> left = left[ii];
                    root -> right = right[jj];
                    result.push_back(root);
                }
            }
        }
    }
    
    vector<TreeNode *> generateTrees(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<TreeNode*> result;
        if(n < 0) return result;
        run(result, 1, n);
        return result;
    }
};
*/