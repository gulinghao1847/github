/*
Reorder List Total Accepted: 5352 Total Submissions: 28501 My Submissions
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
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
    void reorderList(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == NULL) return;
        stack<ListNode*> s;
        ListNode* cur = head;
        while(cur != NULL){
            s.push(cur);
            cur = cur -> next;
        }
        ListNode* tail = s.top();
        s.pop();
        cur = head;
        while(cur != tail){
            ListNode* temp = cur -> next;
            cur -> next = tail;
            tail -> next = temp;
            cur = temp;
            if(cur == tail) break;
            tail = s.top();
            s.pop();
        }
        cur -> next = NULL;
        return;
    }
};
