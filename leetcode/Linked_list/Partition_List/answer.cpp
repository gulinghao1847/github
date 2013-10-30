/**
Partition List Total Accepted: 1522 Total Submissions: 6122 My Submissions
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
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
    ListNode *partition(ListNode *head, int x) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        ListNode* lt =  new ListNode(0);
        ListNode* gt = new ListNode(0);
        ListNode* ltCur = lt;
        ListNode* gtCur = gt;
        ListNode* cur = head;
        while(cur != NULL){
            if(x > cur -> val){
                ltCur -> next = new ListNode(cur -> val);
                ltCur = ltCur -> next;
            }else{
                gtCur -> next = new ListNode(cur -> val);
                gtCur = gtCur -> next;
            }
            cur = cur -> next;
        }
        ltCur -> next = gt -> next;
        return lt -> next;
    }
};