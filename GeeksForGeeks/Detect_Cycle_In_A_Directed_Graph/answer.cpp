/*
A graph implemented by adjcent list
*/
#include <iostream>
#include <list>
#include <limits.h>
using namespace std;

class Graph{
	int V; //number of vertices
	list<int>* adj;
public:
	Graph(int num);
	void addEdge(int v, int w);
};

Graph::Graph(int num){
	V = num;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
	adj[v].push_back(w);
	adj[w].push_back(v);
}

