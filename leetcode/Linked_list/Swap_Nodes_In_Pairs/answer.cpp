/*
Swap Nodes in Pairs Total Accepted: 7372 Total Submissions: 23144 My Submissions
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
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
    ListNode *swapPairs(ListNode *head) {
        if(head == NULL) return head;
        ListNode* dummy = new ListNode(0);
        ListNode* pre = dummy;
        ListNode* first = head;
        dummy -> next = head;
        ListNode* next = NULL;
        ListNode* second = head -> next;
        while(first != NULL && second != NULL){
            next = second -> next;
            pre -> next = second;
            second -> next = first;
            first -> next = next;
            pre = first;
            first = next;
            second = next != NULL ? next -> next : NULL;
        }
        return dummy -> next;
    }
};

