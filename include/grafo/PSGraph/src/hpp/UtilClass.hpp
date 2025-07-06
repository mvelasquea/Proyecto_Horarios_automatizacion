

template<class T>
bool DFSstructure<T>::ContainsKey(DFSmaps map_, string key){

    switch(map_){

        case e_preOrder : return this->preOrder.find(key) == this->preOrder.end();
        case e_posOrder : return this->posOrder.find(key) == this->posOrder.end();
        case e_dad : return this->dad.find(key) == this->dad.end();
    }
};

template<class T>
void DFSstructure<T>::Print(){

    typename map<string,int>::iterator  it_pre, it_pos;
    typename map<string,T>::iterator  it_dad;

    cout << "\nPre Order...\n\n";
    cout <<  ".______________"  <<  "._________________.\n";
    cout <<  "|_____key______"  <<  "|______value______|\n";
    for (it_pre = preOrder.begin(); it_pre!=preOrder.end(); ++it_pre){

        cout.fill('_');
        cout.width(1);
        cout << "|";
        cout.width(13);
        cout <<  it_pre->first ;
        cout.width(1);
        cout << "_|";
        cout.width(16);
        cout <<  it_pre->second;
        cout.width(1);
        cout << "_|\n";
    }

    cout << "\n";

    cout << "\nPos Order...\n\n";

    cout <<  ".______________"  <<  "._________________.\n";
    cout <<  "|_____key______"  <<  "|______value______|\n";
    for (it_pos = posOrder.begin(); it_pos!=posOrder.end(); ++it_pos){
        
        cout.width(1);
        cout << "|";
        cout.width(13);
        cout <<  it_pos->first ;
        cout.width(1);
        cout << "_|";
        cout.width(16);
        cout <<  it_pos->second;
        cout.width(1);
        cout << "_|\n";
    }

    cout << "\nDad...\n\n";

    cout <<  ".______________"  <<  "._________________.\n";
    cout <<  "|_____key______"  <<  "|______value______|\n";
    for (it_dad = dad.begin(); it_dad!=dad.end(); ++it_dad){
        
        cout.width(1);
        cout << "|";
        cout.width(13);
        cout <<  it_dad->first ;
        cout.width(1);
        cout << "_|";
        cout.width(16);
        cout <<  it_dad->second;
        cout.width(1);
        cout << "_|\n";
    }

    cout << "\n\n";

}

    // -- Constructors
    
template<class T>
DFSstructure<T>::DFSstructure(){

};