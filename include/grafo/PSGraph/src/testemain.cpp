#ifndef Main
#define Main

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>	
#include <ostream>
#include <map>

#include "h/Edge.h"
#include "h/Graph.h"
#include "h/UtilClass.h"

using namespace std;

#define GType int	

#define m_Edge Edge<GType>

int main(void){

	Graph<GType> G = Graph<GType>();

	G.InsertVertice(1);
	G.InsertVertice(2);
	G.InsertVertice(3);
	G.InsertEdge(m_Edge(1, 2));
	G.InsertEdge(m_Edge(2, 3));
	G.InsertEdge(m_Edge(3, 1));

	map<string, int> visited;
	
	if(G.HasWay(1,3)) cout << "sim\n";
	DFSstructure<GType> DFS_ = G.DFS();
	cout << G.CountConnexities(visited) << "\n";
	G.Print();

	Graph<GType> r_G = G.GetReverse();

	

	DFS_.Print();
	if(G.ExistsCycle())
		cout << "tem ciclo\n";
map<GType, int> teste = map<GType, int>();
		cout << G.Kosaraju(teste) << "\n";
};

#endif