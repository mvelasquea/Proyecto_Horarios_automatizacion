// -- operators

template<class T>
bool Edge<T>::operator==(Edge<T> e){

	return (this->u == e.u && this->w == e.w) || 
	(!this->isDigraph && this->u == e.w && this->w == e.u);
};

template<class T>
bool Edge<T>::operator!=(Edge<T> e){

	return (this->u != e.u || this->w != e.w) && 
	(this->isDigraph || (this->u != e.w || this->w != e.u));
};

template<class T>
bool Edge<T>::operator<(Edge<T> e){

	return (this->ToString() < e.ToString());
};

template<class T>
bool Edge<T>::operator>(Edge<T> e){

	return (this->ToString() > e.ToString());
};

	// -- Methods

/*verify if an Edge (or relashionship) contains a vertice*/

template <class T>
bool Edge<T>::Contains(T v){
	return (this->u == v || this->w == v);
};

/* Verifiry if vertice v is the start of Edge, so, if is adjacent to u */

template <class T>
bool Edge<T>::IsInitial(T v, bool isDigraph){
	return isDigraph ? this->u == v : this->Contains(v);
};

template <class T>
Edge<T> Edge<T>::GetReverse(){
	return Edge<T>(this->w, this->u);
};



/*return the other extreme of an edge*/

template <class T>
T Edge<T>::GetOtherV(T v){

	if(v == this->u)
		return this->w;
	else if(v == this->w)
		return this->u;

	return (T)NULL;
};

/*Returns the vertices of an Edges*/

template <class T>
vector<T> Edge<T>::GetEdge(){

	vector<T> vertices;
	vertices.push_back(this->u);
	vertices.push_back(this->w);
	return vertices;
};

/*represents an Edge as a String*/

template <class T>
string Edge<T>::ToString(){

	string output;
	stringstream str;
	str << this->u << "-" << this->w;
	str >> output;
	return output;
};

	// -- Constructors --


template <class T>
Edge<T>::Edge(T u, T w, bool isDigraph, double weight){
	this->u = u;
	this->w = w;
	this->isDigraph = isDigraph;
	this->weight = weight;
};
