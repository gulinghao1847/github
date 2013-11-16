/*
Populating Next Right Pointers in Each Node II Total Accepted: 2062 Total Submissions: 7118 My Submissions
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
         1
       /  \
      2    3
     / \    \
    4   5    7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
*/
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
/*
Use BFS to solve this problem
*/
class Solution {
public:
    void connect(TreeLinkNode *root) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(root == NULL) return;
        
        queue<TreeLinkNode*> s;
        s.push(root);
        int lvl1 = 1;
        int lvl2 = 0;
        int depth = 0;
        while(!s.empty()){
            TreeLinkNode* node = s.front();
            s.pop();
            lvl1--;
            //add its next
            if(lvl1 != 0){
                node -> next = s.front();
            }
            //push its child to the stack
            if(node -> left){
                s.push(node -> left);
                lvl2++;
            }
            
            if(node -> right){
                s.push(node -> right);
                lvl2++;
            }
            
            if(lvl1 == 0){
                lvl1 = lvl2;
                lvl2 = 0;
                depth++;
            }
        }
    }
};

