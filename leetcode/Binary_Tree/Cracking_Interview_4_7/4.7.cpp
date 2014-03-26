/*
Design an algorithm and write code to find the first common ancesotr of two nodes in a binary tree. Avoid storing additional nodes in a data structure.
*/
bool find(TreeNode* root, TreeNode* p)//check if a node is in this subtree
{
	if(root == NULL){
		return false;
	}
	if(root == p){
		return true;
	}
	/* if this TreeNode* p is in this subtree, there will be three conditions
	(1)root == p;
	(2)p is in the left subtree
	(3)p is in the right subtree
	*/
	return root == p || find(root -> left, p) || find(root -> right, p);
}
TreeNode* commonAncestorHelper(TreeNode* root, TreeNode* p, TreeNode* q){
	if(root == q || root == q) return root;
	//check these 2 node
	bool p_pos = find(root -> left, p);
	bool q_pos = find(root -> left, q);
	if(p_pos == q_pos)//same side
	{
		return p_pos == true ? commonAncestorHelper(root -> left, p, q) : commonAncestorHelper(root -> right, p, q); 
	}else{
		return root;
	}
}
TreeNode* commonAncestor(TreeNode* root, TreeNode* p, TreeNode* q){
	//check
	if(root == NULL || p == NULL || q == NULL){
		return NULL;
	}
	//check both of the 2 treeNode are in the root
	if(!find(root, p) || !find(root, q)){
		return NULL;
	}
	return commonAncestorHelper(root, p, q);
}
