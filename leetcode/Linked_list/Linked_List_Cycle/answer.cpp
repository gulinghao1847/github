/*
Linked List Cycle Total Accepted: 7729 Total Submissions: 22291 My Submissions
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?
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
    bool hasCycle(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        map<long long, int> mp;
        ListNode* cur = head;
        while(cur != NULL){
            if(mp[(long long)cur] == 1){
                return true;
            }
            else{
                mp[(long long)cur]++; 
                cur = cur -> next;
            }
        }
        return false;
    }
};

