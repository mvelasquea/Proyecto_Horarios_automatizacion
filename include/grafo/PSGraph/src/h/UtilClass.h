#ifndef UTILSCLASS_H
#define UTILSCLASS_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


using namespace std;

enum DFSmaps {e_preOrder, e_posOrder, e_dad};    

template<class T>
class DFSstructure{

public:
    map<string, int> preOrder;
    map<string, int> posOrder;
    map<string, T> dad;

    bool ContainsKey(DFSmaps map_, string key);
    void Print();

public:
	DFSstructure<T>();
};


#include "../hpp/UtilClass.hpp"
#endif