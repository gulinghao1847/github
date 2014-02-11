/*
Remove Nth Node From End of List Total Accepted: 6818 Total Submissions: 23001 My Submissions
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/*
很tricky一点要判断的问题是要判断当第一个pointer 的一点是当first指向的是null 的时候该如何判断， 这个时候second 就会多数一次， 这就是错误的地方， 因此要将first->next == NULL 这个作为判定条件
事实上， second 是跟着first的点在同步的动， 而不是延时 的
*/
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if(head == NULL) return head;
        ListNode* dummy = new ListNode(0);
        dummy -> next = head;
        ListNode* first = head;
        ListNode* second = head;
        ListNode* preOfSec = dummy;
        int count = 0;
        while(first -> next != NULL){
            first = first -> next;
            count++;
            if(count >= n){
                preOfSec = second;
                second = second -> next;
            }
        }
        preOfSec -> next = second -> next;
        return dummy -> next;
    }
};

