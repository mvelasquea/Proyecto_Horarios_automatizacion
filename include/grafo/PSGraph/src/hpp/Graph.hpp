
	// -- Methods --

/* Returns the total Degress of Graph G(V,E) */

template<class T>
int Graph<T>::Deg(){
	return this->edges.size() * 2;
};

/* Returns the degress of v{V} */

template<class T>
int Graph<T>::Deg(T v){
	
	if(!this->ContainsVertice(v))
		return -1;

	int Sum = 0;
	for (it_Edges = Edges.begin(); it_Edges!=Edges.end(); ++it_Edges)
		Sum+= (it_Edges->second.Contains(v));
	
	return Sum;
};

/*Make a hashCode to insert a new edge */

template<class T>
string Graph<T>::MakeHash(t_Edge e){
	return e.ToString();
};

/* Verify if this Graph contains the Vertice v */

template<class T>
bool Graph<T>::ContainsVertice(T v){
	
	for(int i = 0; i < this->vertices.size(); i++){
		if(vertices[i] == v){
			return true;
		}
	}
	return false;
};

/* Insert a vertice in Graph if her not contains it */

template<class T>
void Graph<T>::InsertVertice(T v){
	
	if(!this->ContainsVertice(v)){
		this->vertices.push_back(v);

		this->SortVertices();
	}
};

/* Verify if this Graph contains the Edge e */

template<class T>
bool Graph<T>::ContainsEdge(t_Edge e){
	
	return (Edges.find(MakeHash(e))!= Edges.end());
};

/* Insert an Edge in Graph if her not contains it */

template<class T>
void Graph<T>::InsertEdge(t_Edge e){

	if(!this->ContainsEdge(e)){
		Edges.insert(std::pair<string,t_Edge>(MakeHash(e),e));

		if(!this->isDigraph){

			Edges.insert(std::pair<string,t_Edge>(MakeHash(e.GetReverse()),e.GetReverse()));
		}
	}
};

/* Remove an Edge in Graph if her contains it */

template<class T>
void Graph<T>::RemoveEdge(t_Edge e){

	if(this->ContainsEdge(e)){
		this->Edges.erase(this->MakeHash());
	}
};

/* Realize a DFS search in current Graph */

template<class T>
DFSstructure<T> Graph<T>::DFS(){

	DFSstructure<T> dfsSTC = DFSstructure<T>(); 

	int preCount = 0; 
	int posCount = 0;
	for(int i =0; i < vertices.size(); i++){
		if(dfsSTC.ContainsKey(e_preOrder, functions.VerticeToString(vertices[i]))){
			
			dfsSTC.dad[functions.VerticeToString(vertices[i])] = vertices[i];
			DFSR(vertices[i], dfsSTC, preCount, posCount);
		}
	}
	return dfsSTC;
};

/* Complementary function to realize DFS */

template<class T>
void Graph<T>::DFSR(T vertice, DFSstructure<T>& dfsSTC, int& preCount, int& posCount){

	dfsSTC.preOrder[functions.VerticeToString(vertice)] = preCount++;

	vector<T> neighboors = GetNeighboors(vertice);

	for(int j = 0; j < neighboors.size(); j++){

		if(dfsSTC.ContainsKey(e_preOrder, functions.VerticeToString(neighboors[j]))){

			dfsSTC.dad[functions.VerticeToString(neighboors[j])] = vertice;

			DFSR(neighboors[j], dfsSTC, preCount, posCount);
		}
	}
	dfsSTC.posOrder[functions.VerticeToString(vertice)] = posCount++;
};

/*  Verify if Exists cycles in current Graph  */

template<class T>
bool Graph<T>::ExistsCycle(){

	DFSstructure<T> dfsStc = this->DFS();

	for(int i =0; i < vertices.size(); i++){

		vector<T> neighboors = GetNeighboors(vertices[i]);

		for(int j = 0; j < neighboors.size(); j++){

			string hashV = functions.VerticeToString(vertices[i]);
			string hashN = functions.VerticeToString(neighboors[j]);

			if(	dfsStc.preOrder[hashV] > dfsStc.preOrder[hashN] && 
				dfsStc.posOrder[hashV] < dfsStc.posOrder[hashN])
				return true;
		}
	}
	return false;
};

/*  Generate an Graph with G vertex and inverse edges of diagraph G,
 * 	if v-w is a G edge -> w-v is a r_G edge */

template<class T>
Graph<T>  Graph<T>::GetReverse(){

	if(this->isDigraph)
		return this;

	Graph<T> r_Graph = Graph<T>(this->isDigraph);

	r_Graph.vertices = this->vertices;

	for(int i =0; i < vertices.size(); i++){
		
		vector<T> neighboors = GetNeighboors(vertices[i]);

		for(int j = 0; j < neighboors.size(); j++){
		
			r_Graph.InsertEdge(t_Edge(neighboors[j], vertices[i]));
		}
	}

	return r_Graph;
};

/*  Kosaraju-Sharir algorithm.. find the strongly connected components of a directed graph */

template<class T>
int Graph<T>::Kosaraju(map<T, int>& componentGroup){

	int preCount = 0;
	int posCount = 0;
	int quantity = 0;

	vector<T> posOrderSorted = vector<T>();
	posOrderSorted.resize(this->vertices.size());

	Graph r_Graph = this->GetReverse();
	DFSstructure<T> dfsSTC = DFSstructure<T>(); 

	// Phase 1

	for(int i =0; i < vertices.size(); i++){
		// if vertice[i] is not visited.
		if(dfsSTC.ContainsKey(e_preOrder, functions.VerticeToString(vertices[i])))
			r_Graph.DFSR(vertices[i], dfsSTC, preCount, posCount);
	}
 
	/* Sort the posOrder map to vector */	
	for(int i =0; i < vertices.size(); i++)
		posOrderSorted[dfsSTC.posOrder[functions.VerticeToString(vertices[i])]]  = vertices[i];
	
	//Phase 2
	for(int i = vertices.size(); i >= 0; i--){

		T v = posOrderSorted[i];

		if(componentGroup.find(v)== componentGroup.end()){
			DFSRsc(v, componentGroup, quantity);
			quantity++;
		}
	}

	return quantity;
};

/* Complementary function of Kosaraju-Sharir algorithm */

template<class T>
void Graph<T>::DFSRsc(T vertice, map<T, int>& componentGroup, int quantity){

	componentGroup[vertice] = quantity;

	vector<T> neighboors = GetNeighboors(vertice);
	
	for(int j = 0; j < neighboors.size(); j++)
		if(componentGroup.find(neighboors[j])== componentGroup.end())
			DFSRsc(neighboors[j], componentGroup, quantity);
};

/* Count how many connexities components has in Graph */

template<class T>
int Graph<T>::CountConnexities(map<string, int>& componentGroup){

	int componentsQuantity = 0;

	for(int i =0; i < vertices.size(); i++)
		if(componentGroup.find(functions.VerticeToString(vertices[i]))== componentGroup.end())
			DFSCOMP(vertices[i], componentGroup, componentsQuantity++);
	
	return componentsQuantity;
};

/* Complementary function of CountConnexities */

template<class T>
void Graph<T>::DFSCOMP(T vertice, map<string, int>& componentGroup, int quantity){

	componentGroup.insert(std::pair<string,int>(functions.VerticeToString(vertice),quantity));

	vector<T> neighboors = GetNeighboors(vertice);

	for(int j = 0; j < neighboors.size(); j++)
		if(componentGroup.find(functions.VerticeToString(neighboors[j]))== componentGroup.end())
			DFSCOMP(neighboors[j], componentGroup, quantity);
};

/* Verify if has an way from vertice u to vertice w */

template<class T>
bool Graph<T>::HasWay(T u, T w){

	map<T, bool> visits = map<T,bool>();

	ReachV(u, visits);

	return visits[w];
};

/* Reach the Graph - Complementary function of Graph<T>::HasWay */

template<class T>
void Graph<T>::ReachV(T v, map<T, bool>& visited){

	visited[v] = true;
	
	vector<T> neighboors = GetNeighboors(v);

	for(int i = 0; i < neighboors.size(); i++){

		if(!visited[neighboors[i]]){
			ReachV(neighboors[i], visited);
		}
	}
};

/* Sort the vertice vector **Is used ever a vertice is inserted */

template <class T>
void Graph<T>::SortVertices(){

	sort (this->vertices.begin(), this->vertices.begin() + this->vertices.size());
};

/* Get the Neighboors of vertice v */

template <class T>
vector<T> Graph<T>::GetNeighboors(T v){
	
	vector<T> neighboors = vector<T>();
	neighboors.clear();

	for (it_Edges = Edges.begin(); it_Edges!=Edges.end(); ++it_Edges)
		if(it_Edges->second.IsInitial(v, isDigraph))
			neighboors.push_back(it_Edges->second.GetOtherV(v));
		
	return neighboors;
}

/* Print a representation of this Graph */

template<class T>
void Graph<T>::Print(){

	for(int i = 0; i < this->vertices.size(); i++){
		
		cout << this->vertices[i] << ": ";

		for (it_Edges = Edges.begin(); it_Edges!=Edges.end(); ++it_Edges)
			if(it_Edges->second.IsInitial(vertices[i], isDigraph))
				cout << it_Edges->second.GetOtherV(vertices[i]) << " ";
		
		printf("\n");
	}
};
	// -- Constructors
	
template<class T>
Graph<T>::Graph(bool isDigraph){
	this->vertices.clear();
	this->Edges.clear();
	this->isDigraph = isDigraph;
	this->functions = Functions<T>();
};