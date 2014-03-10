/*
Implement an algorithm to delete a node in the middle of a singly linked list.
given only access to that node
Example:
input: the node c from the linked list: a -> b -> c -> d -> e
output: nothing is returned, but the new linked list looks like  a -> b -> d -> e
*/
/*
class ListNode{
	int val;
	ListNode* next;
	ListNode(int val){val = val; next = NULL;}
};
*/

void deleteNode(ListNode* node){
	if(node == NULL || node -> next == NULL) return;
	ListNode* cur = node;
	while(cur -> next != NULL){
		cur -> val = cur -> next -> val;
	}
	delete cur;
	return;
}

/*
做出这种解法纯属有病啊， 一道很简单的O(1)的题目非要o(n), 这道题目本质就是delete list 中的一个node的应用
同时要注意， 如果删除的是list的最后一个点的话， 要注意， 这种做法是没有办法实现的， 也是没有办法实现的
*/

void deleteNode(ListNode* node){
	if(node == NULL || node -> next == NULL) return;
	ListNode* next = node -> next;
	node -> next = next -> next;
	node -> val = next -> val;
	delete next;
	return;
}