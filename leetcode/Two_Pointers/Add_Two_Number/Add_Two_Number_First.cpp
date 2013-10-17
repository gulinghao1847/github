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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if((!l1)&&(!l2)) return NULL;
        ListNode* n1 = l1;
        ListNode* n2 = l2;
        int addOn = 0;
        int v1 = 0;
        int v2 = 0;
        int value = 0;
        ListNode* next;
        ListNode* head = new ListNode(0);
        next = head;
        
        while(n1||n2){
            v1 = (n1)?(n1 -> val):0;     
            v2 = (n2)?(n2 -> val):0;
            value = v1 + v2 + addOn;
            if(value > 9 ){
                value = value - 10;
                addOn = 1;
            }else{
                addOn = 0;
            }
            next -> val = value;
            
            
            if(n1||n2){
                next -> next = new ListNode(0);
                next = next -> next;
            }
            n1 = (n1)?(n1 -> next):NULL;
            n2 = (n2)?(n2 -> next):NULL; 
            
        }
        
        return head;
    }
};