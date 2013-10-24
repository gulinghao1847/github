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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Note: The Solution object is instantiated only once and is reused by each test case
        vector<ListNode*>::iterator it = lists.begin();
		//the following while loop is to erase the empty link lists.
        while(it != lists.end()) {
            if(*it == NULL) lists.erase(it);
            else ++it;
        }
		//--------------------end--------------------------
		//test
        if(lists.size() == 0){
            return NULL;
        }
        make_heap(lists.begin(), lists.end(), comp());
        ListNode* head = NULL;
        ListNode* cur = NULL;
        while(lists.size() > 0){
            if(head == NULL){
                head = lists[0];
                cur = lists[0];
            }
            else{
                cur -> next = lists[0];
                cur = cur -> next;
            }
            pop_heap(lists.begin(), lists.end(), comp());
            if(lists[lists.size() - 1] -> next != NULL){
                lists[lists.size() - 1] = lists[lists.size() - 1] -> next;
                push_heap(lists.begin(), lists.end(), comp());
            }else
                lists.pop_back();
        }
        return head;
    }
	//class comp
    class comp {
        public:
            bool operator() (const ListNode* l, const ListNode* r){
                return (l->val > r->val);
            }
    };
};