/*
Convert Sorted List to Binary Search Tree Total Accepted: 5346 Total Submissions: 19953 My Submissions
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
    TreeNode* run(ListNode* head, int size){
        if(size == 0||head == NULL){
            return NULL;
        }
        /*
        if(size == 1){
            TreeNode* root = new TreeNode(head -> val);
            return root;
        }
        */
        int mid = size/2;
        ListNode* node = head;
        int it = 0;
        while(it < mid){
            it++;
            node = node -> next;
        }
        TreeNode* root = new TreeNode(node -> val);
        
        root -> left = run(head, mid);
        root -> right = run(node -> next, (size - mid - 1)>0?(size - mid - 1):0);
        
        return root;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(head == NULL){
            return NULL;
        }
        
        int size = 0;
        ListNode* it = head;
        while(it != NULL){
            size++;
            it = it -> next;
        }
        
        TreeNode* ret = run(head, size);
        
        return ret;
    }
};

