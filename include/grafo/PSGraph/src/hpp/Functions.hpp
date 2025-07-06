// -- Vertices --


template <class T>
string Functions<T>::VerticeToString(T v){

	string output;
	stringstream str;
	str << v;
	str >> output;
	return output;
};



template <class T>
Functions<T>::Functions(){


};
