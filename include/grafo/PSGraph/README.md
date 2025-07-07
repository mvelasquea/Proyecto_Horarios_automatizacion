# PSGraph
A implementation of generic graph with C++ Templates 

#Documentation

The main logic to use this graph pack are that each inserted vertex is identified by your alias. So, if an vertex is called 'A', is not possible to insert other vertex with this alias. 

Actually, the PSGraph contains this artifices:

The vertex is a generic basic type (int, double, string..).

## Edges 
are composed by : 
###### 2 Vertex;
###### A double weight;
###### A bool flag called 'isDigraph' to set if this edge has direction.

###Methods

#####Constructor (T u, T w, bool isDigraph = false, double weight = 1) : 
Receives 2 vertex with type 'T' and 2 optionals attributes 'isDigraph' and weight to set, repectively, if this is a digraph and your weight (if the graph use weights);
#####GetEdge() : 
Returns a vector with vertex type with 2 vertex where if this is an digraph the first position has a path to second position;
#####ToString() :
Retuns current Edge as String follwing this rule: Be E an Edge and v,w your vertex, this fuction returns the string "v-w"; 
#####Contains(T v) :
This function takes a vertex and returns true if the given vertex is equal to 1 of the 2 vertices contained in the current edge.
#####IsInitial(T v, bool isDigraph) :
Verify if the vertex v is contained in current Edge and if its has a path to other vertice of this Edge.(To digraphs).
#####GetOtherV(T v) :
Given a vertex v that is contained in current Edge, this function retuns the other vertex of this relation.
#####GetReverse() :
Return the reverse relation of this edge. So, if have an edge between v and w, and v has a path to w, but w hasn't(to digraphs), this function returns an edge where w has a path to v, but v hasn't.


## Graph
Are composed by:
###### A vector of vertex.
###### A map (string, Edge) of Edges.
###### A bool flag called 'isDigraph' to set if this edge has direction.

###Methods

#####Deg() : 
Returns a int with the sum of degress of all vertex in Graph.
#####Deg(T v) :
Return the degress of this vertex in Graph.
#####MakeHash(t_Edge e) :
Make the default Hash used in all Graph maps.
#####ContainsVertice(T v) :
Returns a boolvalue that represents if this Graph contains the vertice v.
#####InsertVertice(T v) :
Insert the vertex v in Graph.



