/*
Reverse Nodes in k-Group Total Accepted: 4384 Total Submissions: 18506 My Submissions
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode* dummy = new ListNode(0);
        dummy -> next = head;
        ListNode* pre = dummy;
        ListNode* cur = head;
        if(head == NULL) return head;
        stack<ListNode*> s;
        int count = 0;
        while(cur != NULL){
            count++;
            s.push(cur);
            ListNode* temp = cur -> next;
            if(count == k){
                while(!s.empty()){
                    pre -> next = s.top();
                    s.pop();
                    pre = pre -> next;
                }
                count = 0;
                pre -> next = temp;
            }
            cur = temp;
        }
        return dummy -> next;
    }
};

