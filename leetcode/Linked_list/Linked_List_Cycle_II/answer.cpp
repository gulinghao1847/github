/*
Linked List Cycle II Total Accepted: 5170 Total Submissions: 17168 My Submissions
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Follow up:
Can you solve it without using extra space?

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
    ListNode *detectCycle(ListNode *head)  {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        map<long long, int> mp;
        ListNode* cur = head;
        while(cur != NULL){
            if(mp[(long long)cur] >= 1){
                return cur;
            }else{
                mp[(long long)cur]++;
                cur = cur -> next;
            }
        }
        return NULL;
    }
};
