/*
Rotate List Total Accepted: 1419 Total Submissions: 6661 My Submissions
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

Discuss
 */
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(head == NULL) return head;
        int len = 0;
        ListNode* tail = NULL;
        ListNode* cur = head;
        ListNode* ret = NULL;
        while(cur != NULL){
            len++;
            tail = cur;
            cur = cur -> next;
        }
        tail -> next = head;
        int num = len - k%len;
        cur = tail;
        for(int i = 0; i < num; i++) cur = cur -> next;
        ret = cur -> next;
        cur -> next = NULL;
        return ret;
    }
};