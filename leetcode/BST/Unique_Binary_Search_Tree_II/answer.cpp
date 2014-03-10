/*
Unique Binary Search Trees II Total Accepted: 4383 Total Submissions: 16971 My Submissions
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
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
    void generate(vector<TreeNode*>& result, int begin, int end){
        if(begin > end){
            result.push_back(NULL);
            return;
        }
        for(int i = begin; i <= end; i++){
            vector<TreeNode*> l;
            generate(l, begin, i - 1);
            vector<TreeNode*> r;
            generate(r, i + 1, end);
            for(int ii = 0; ii < l.size(); ii++){
                for(int jj = 0; jj < r.size(); jj++){
                    TreeNode* node = new TreeNode(i);
                    node -> left = l[ii];
                    node -> right = r[jj];
                    result.push_back(node);
                }
            }
        }
    }
    
    vector<TreeNode *> generateTrees(int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<TreeNode*> result;
        generate(result, 1, n);
        return result;
    }
};

