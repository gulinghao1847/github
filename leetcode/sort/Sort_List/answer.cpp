/*
Sort List Total Accepted: 5001 Total Submissions: 25544 My Submissions
Sort a linked list in O(n log n) time using constant space complexity.
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
merge 和 linkedlist 结合的题目， 注意49 行要加入head -> next = NULL
*/
class Solution {
public:
    ListNode* merge(ListNode* left, ListNode* right){
        ListNode* dummy = new ListNode(0);
        ListNode* l = left;
        ListNode* r = right;
        ListNode* cur = dummy;
        while(l != NULL && r != NULL){
            ListNode* lCur = l;
            ListNode* rCur = r;
            if(lCur -> val < rCur -> val){
                cur -> next = lCur;
                l = l -> next;
            }else{
                cur -> next = rCur;
                r = r -> next;
            }
            cur = cur -> next;
        }
        while(l){
            cur -> next = l;
            l = l -> next;
            cur = cur -> next;
        }
        while(r){
            cur -> next = r;
            r = r -> next;
            cur = cur -> next;
        }
        return dummy -> next;
    }
    
    ListNode* mergeSort(ListNode* head, int size){
        if(size == 1){
            head -> next = NULL;   //VERY IMPORTANT
            return head;
        }
        
        if(size == 0){
            return NULL;
        }
        
        int mid = size / 2;
        int count = 0;
        ListNode* secHead = head;
        while(count != mid){
            secHead = secHead -> next;
            count++;
        }
        ListNode* left = mergeSort(head, mid);
        ListNode* right = mergeSort(secHead, size - mid);
        return merge(left, right);
    }
    
    ListNode *sortList(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == NULL) return head;
        ListNode* cur = head;
        int size = 0;
        while(cur != NULL) {
            cur = cur -> next;
            size++;
        }
        return mergeSort(head, size);
    }
};