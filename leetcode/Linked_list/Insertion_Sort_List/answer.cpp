/*
Insertion Sort List Total Accepted: 6675 Total Submissions: 26911 My Submissions
Sort a linked list using insertion sort.
*/
/*
The idea behind this is:
Step 1: Delete this node from the linked list(cancatenating the previous node with its next node)
Step 2: Insert this node into the linked list
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
    ListNode *insertionSortList(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == NULL) return head;
        ListNode* dummy = new ListNode(INT_MIN);
        dummy -> next = head;
        ListNode* cur = head -> next;
        ListNode* pre = head;
        while(cur != NULL){
            int value = cur -> val;
            //changing the pointer at the orginal place
            if(pre -> val < cur -> val){
                pre = cur;
                cur = cur -> next;
                continue;
            }
            ListNode* temp = cur -> next;
            pre -> next = temp;
            //changing the pointer at the new place
            ListNode* iter = dummy -> next;
            ListNode* preIter = dummy;
            //find the right place
            while(iter && preIter -> val < value && iter -> val < value){
                preIter = iter;
                iter = iter -> next;
            }
            //update pointer
            preIter -> next = cur;
            cur -> next = iter;
            //update while loop var
            cur = temp;
        }
        return dummy -> next;
    }
};
/*
from line31 to line 35, important! track the pre pointer
line 39, dont write as: ListNode* iter = head; cause head is not the next point of dummy!
*/

//new method, treat sorted list and unsorted list differently

class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if(!head) return NULL;
        ListNode* dummy = new ListNode(INT_MIN);
        dummy -> next = head;
        ListNode* unsorted = head -> next;
        head -> next = NULL;
        while(unsorted){
            ListNode* insertValue = unsorted;
            unsorted = unsorted -> next;
            /*important!!!!!*/ListNode* cur = dummy -> next;
            ListNode* last = dummy;
            bool done = false;
            while(cur){
                if(insertValue -> val < cur -> val){
                    last -> next = insertValue;
                    insertValue -> next = cur;
                    done = true;
                    break;
                }else{
                    last = cur;
                    cur = cur -> next;
                }
            }
            if(!done){
                last -> next = insertValue;
                insertValue -> next = NULL;
            }
        }
        return dummy -> next;
    }
};
