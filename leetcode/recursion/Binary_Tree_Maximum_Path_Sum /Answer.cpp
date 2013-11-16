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
hard problem, the idea is obviously. But we need to consider many conditions, which is the hardest part;
*/

class Solution {
public:
    int run(TreeNode* root, int& maxSum){
        if(root == NULL){
            return INT_MIN;
        }
        if(root -> left == NULL && root -> right == NULL){
            maxSum = max(root -> val, maxSum);
            return root -> val;
        }
        int left = run(root -> left, maxSum);
        int right = run(root -> right, maxSum);
        
        //we need to do two things next
        //first: find the max that should be returned;
        int maxOf2 = max(left, right);
        int ret = maxOf2 + root -> val;  //that is the value which is returned
        ret = max(ret, root -> val); //!!!!returned value should be the max of these 2!!!!!!!
        //second : find the max value at this node and compare it to the maxSum
        /*
        we need to find the maxSum from these value: maxSum, left + right + root -> val, left, right, max(left, right) + root -> val
        and root -> val itself!!!!!!!!!! be careful at this point
        */
        int connected = root -> val;
        if(left != INT_MIN) connected += left;
        if(right != INT_MIN) connected += right;
        maxSum = max(maxSum, max(connected, max(maxOf2, max(ret, root -> val))));
        //all 2 things have been done, then we return the value of ret;
        return ret;
    }
    int maxPathSum(TreeNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int max_sum = INT_MIN;
        int ret = run(root, max_sum);
        return max_sum;
    }
};

