
/**
Reorder List Total Accepted: 1354 Total Submissions: 7689 My Submissions
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
 */
class Solution {
public:
    void reorderList(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == NULL) return;
        ListNode* front, *end;
        front = end = head;
        stack<ListNode*> s;
        while(end -> next != NULL){
            s.push(end);
            end = end -> next;
        }
        
        while(front != end){
            ListNode* temp = front -> next;
            front -> next = end;
            end -> next = temp;    
            front = temp;     // that is the only place we need to pay attention to.    !!!!!front = front -> next   is wrong!!!!!!!!!! now front -> next = end not the next node
            if(front == end){
                break;
            }
            end = s.top();
            s.pop();   // end = s.top(); s.pop(); 和front ＝ temp； 这两行没法替换， 不然最后一个end －》 next 就会报错了 
        }
        
        end -> next = NULL;// 这里也要注意， 最后的end 需要 next ＝ null 不然就形成环了
    }
};