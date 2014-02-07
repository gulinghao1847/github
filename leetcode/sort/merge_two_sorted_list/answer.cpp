/*
Merge Two Sorted Lists Total Accepted: 7317 Total Submissions: 22460 My Submissions
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode* head = new ListNode(0);
        ListNode* first = l1;
        ListNode* second = l2;
        ListNode* cur = head;
        while(first != NULL && second != NULL){
            if(first -> val < second -> val){
                cur -> next = first;
                first = first -> next;
            }else{
                cur -> next = second;
                second = second -> next;
            }
            cur = cur -> next;
        }
        while(first != NULL){
            cur -> next = first;
            first = first -> next;
            cur = cur -> next;
        }
        while(second != NULL){
            cur -> next = second;
            second = second -> next;
            cur = cur -> next;
        }
        cur -> next = NULL;
        return head -> next;
    }
};

