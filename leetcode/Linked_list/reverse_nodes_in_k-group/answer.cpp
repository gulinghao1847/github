/*
Reverse Nodes in k-Group Total Accepted: 4384 Total Submissions: 18506 My Submissions
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
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
delete node and add node in a linked list
and cur!!!!!!some data may change, like cur -> next. So we need to store them.
*/
class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(k <= 1) return head;
        ListNode dummy(0);
        dummy.next = head;
        int count = 0;
        stack<ListNode*> st;
        ListNode* cur = head;
        ListNode* pre = &dummy;
        while(cur != NULL){
            st.push(cur);
            count++;
            ListNode* temp = cur -> next;
            if(count == k){
                count = 0;
                while(!st.empty()){
                    pre -> next = st.top();
                    st.pop();
                    pre = pre -> next;
                }
                pre -> next = temp;
            }
            cur = temp;
        }
        return dummy.next;
    }
};

