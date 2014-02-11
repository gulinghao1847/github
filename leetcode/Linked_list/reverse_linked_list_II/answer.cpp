/*

Reverse Linked List II Total Accepted: 5483 Total Submissions: 21824 My Submissions
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.
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
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        stack<ListNode*> s;
        if(head == NULL) return head;
        ListNode* dummy = new ListNode(0);
        dummy -> next = head;
        int count = 0;
        ListNode* cur = head;
        int flag = 0;
        ListNode* pre = dummy;
        ListNode* tail = NULL;
        while(cur != NULL){
            count++;
            if(count >= m && count <= n){
                    s.push(cur);
            }
            if(count == m - 1){
                pre = cur;
            }
            if(count == n + 1){
                tail = cur;
            }
            cur = cur -> next;
        }
        cur = pre;
        while(!s.empty()){
            cur -> next = s.top();
            s.pop();
            cur = cur -> next;
        }
        cur -> next = tail;
        return dummy -> next;
    }
};

