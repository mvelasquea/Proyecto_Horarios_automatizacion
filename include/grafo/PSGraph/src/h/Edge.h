#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ostream>

#define t_Edge Edge<T>

using namespace std;

template <class T>
class Edge{

public:
	T u;
	T w;
	
	double weight;
	bool isDigraph;

public:

	vector<T> GetEdge();
	Edge<T>(T u, T w, bool isDigraph = false, double weight = 1);

	string ToString();
	bool Contains(T v);
	bool IsInitial(T v, bool isDigraph);
	T GetOtherV(T v);
	Edge<T> GetReverse();

	bool operator==(Edge<T> e);
	bool operator!=(Edge<T> e);
	bool operator>(Edge<T> e);
	bool operator<(Edge<T> e);
};


#include "../hpp/Edge.hpp"
#endif
