/*
Clone Graph Total Accepted: 6392 Total Submissions: 30641 My Submissions
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodaes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
/*
	这一题考的主要的东西和另外一题有些类似， 就是如何deep copy 一个link， 因为如果直接copy的话copy的是原始的pointer， 因此要找到一个映射， 旧的node和新的node之间的关系
	然后再用bfs就可以了
*/

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(node == NULL) return NULL;
        queue<UndirectedGraphNode*> q;
        map<int, UndirectedGraphNode*> mp;
        UndirectedGraphNode* head = new UndirectedGraphNode(node -> label);
        q.push(node);
        mp[node -> label] = head;
        while(!q.empty()){
            UndirectedGraphNode* myNode = q.front();
            q.pop();
            for(int i = 0; i < myNode -> neighbors.size(); i++){
                //has not been visited
                if(mp.find(myNode -> neighbors[i] -> label) == mp.end()){
                    UndirectedGraphNode* newNode = new UndirectedGraphNode(myNode -> neighbors[i] -> label);
                    mp[myNode -> label] -> neighbors.push_back(newNode);
                    mp[myNode -> neighbors[i] -> label] = newNode;
                    q.push(myNode -> neighbors[i]);
                }else//has been visited
                {
                    mp[myNode -> label] -> neighbors.push_back(mp[myNode -> neighbors[i] -> label]);
                }
            }
        }
        return head; 
    }
};

