/*
Remove Duplicates from Sorted List Total Accepted: 8300 Total Submissions: 24304 My Submissions
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.

Discuss
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
    ListNode *deleteDuplicates(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == NULL) return head;
        ListNode* last = head;
        ListNode* cur = head -> next;
        while(cur != NULL){
            if(cur -> val == last -> val){
                //ListNode* temp = cur -> next;
                last -> next = cur -> next;
            }else{
                last = cur;
            }
            cur = cur -> next;
        }
        return head;
    }
};