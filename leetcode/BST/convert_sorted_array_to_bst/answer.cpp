/*
Convert Sorted Array to Binary Search Tree Total Accepted: 6120 Total Submissions: 19085 My Submissions
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
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
    TreeNode* convertToBST(vector<int>& num, int begin, int end){
        if(end - begin < 0){
            return NULL;
        }
        int mid = (begin + end) / 2;
        TreeNode* root = new TreeNode(num[mid]);
        root -> left = convertToBST(num, begin, mid - 1);
        root -> right = convertToBST(num, mid + 1, end);
        return root;
    }
    TreeNode *sortedArrayToBST(vector<int> &num) {
        return convertToBST(num, 0, num.size() - 1);
    }
};

