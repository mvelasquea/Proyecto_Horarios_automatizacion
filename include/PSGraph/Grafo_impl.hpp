#ifndef GRAFO_IMPL_HPP
#define GRAFO_IMPL_HPP

#include <sstream>

// ------- Helpers to_id --------
// Template general (para punteros genéricos)
template <typename T>
std::string to_id(T obj) {
    std::ostringstream oss;
    oss << reinterpret_cast<uintptr_t>(obj); // dirección en memoria (punteros)
    return oss.str();
}

// Especialización para int (útil si usas Grafo<int>)
template <>
inline std::string to_id<int>(int obj) {
    return std::to_string(obj);
}

// Especialización para std::string
template <>
inline std::string to_id<std::string>(std::string obj) {
    return obj;
}

// -- Implementación de métodos Arista --

template <typename T>
Arista<T>::Arista(T origen, T destino, bool dirigido, double peso) noexcept
    : origen(origen), destino(destino), dirigido(dirigido), peso(peso) {}

template <typename T>
vector<T> Arista<T>::obtenerVertices() const {
    return {origen, destino};
}

template <typename T>
string Arista<T>::toString() const {
    return to_id(origen) + "-" + to_id(destino);
}

template <typename T>
bool Arista<T>::contiene(const T& v) const noexcept {
    return (origen == v) || (destino == v);
}

template <typename T>
bool Arista<T>::esInicial(const T& v) const noexcept {
    return dirigido ? (origen == v) : contiene(v);
}

template <typename T>
T Arista<T>::obtenerOtroVertice(const T& v) const {
    if (v == origen) return destino;
    if (v == destino) return origen;
    throw std::invalid_argument("Vertice no pertenece a la arista.");
}

template <typename T>
Arista<T> Arista<T>::obtenerInversa() const noexcept {
    return Arista<T>(destino, origen, dirigido, peso);
}

template <typename T>
bool Arista<T>::operator==(const Arista<T>& a) const noexcept {
    if (dirigido != a.dirigido) return false;
    if (dirigido)
        return origen == a.origen && destino == a.destino;
    else
        return (origen == a.origen && destino == a.destino) ||
               (origen == a.destino && destino == a.origen);
}

template <typename T>
bool Arista<T>::operator<(const Arista<T>& a) const {
    return toString() < a.toString();
}

// -- Implementación Grafo --

template <typename T>
Grafo<T>::Grafo(bool dirigido) noexcept : dirigido_(dirigido) {}

template <typename T>
string Grafo<T>::hashArista(const Arista<T>& a) const {
    if (!dirigido_ && to_id(a.origen) > to_id(a.destino))
        return to_id(a.destino) + "-" + to_id(a.origen);
    return to_id(a.origen) + "-" + to_id(a.destino);
}

template <typename T>
bool Grafo<T>::contieneVertice(const T& v) const noexcept {
    return find(vertices_.begin(), vertices_.end(), v) != vertices_.end();
}

template <typename T>
void Grafo<T>::insertarVertice(const T& v) {
    if (!contieneVertice(v)) {
        vertices_.push_back(v);
        sort(vertices_.begin(), vertices_.end());
    }
}

template <typename T>
bool Grafo<T>::contieneArista(const Arista<T>& a) const {
    return aristas_.count(hashArista(a)) > 0;
}

template <typename T>
void Grafo<T>::insertarArista(const Arista<T>& a) {
    if (!contieneArista(a)) {
        insertarVertice(a.origen);
        insertarVertice(a.destino);
        aristas_[hashArista(a)] = a;
        if (!dirigido_) {
            Arista<T> inv = a.obtenerInversa();
            aristas_[hashArista(inv)] = inv;
        }
    }
}

template <typename T>
void Grafo<T>::eliminarArista(const Arista<T>& a) {
    auto it = aristas_.find(hashArista(a));
    if (it != aristas_.end()) {
        aristas_.erase(it);
        if (!dirigido_) {
            Arista<T> inv = a.obtenerInversa();
            aristas_.erase(hashArista(inv));
        }
    }
}

template <typename T>
int Grafo<T>::grado(const T& v) const {
    if (!contieneVertice(v)) return -1;
    int cuenta = 0;
    for (const auto& [k, arista] : aristas_) {
        if (arista.contiene(v)) cuenta++;
    }
    return cuenta;
}

template <typename T>
int Grafo<T>::gradoTotal() const {
    if (dirigido_) {
        return (int)aristas_.size();
    } else {
        return (int)(aristas_.size() / 2);
    }
}

template <typename T>
vector<T> Grafo<T>::obtenerVecinos(const T& v) const {
    vector<T> vecinos;
    for (const auto& [k, arista] : aristas_) {
        if (arista.esInicial(v)) {
            vecinos.push_back(arista.obtenerOtroVertice(v));
        }
    }
    return vecinos;
}

template <typename T>
const vector<T>& Grafo<T>::obtenerVertices() const {
    return vertices_;
}

template <typename T>
vector<Arista<T>> Grafo<T>::obtenerAristasDe(const T& v) const {
    vector<Arista<T>> aristasSalida;
    for (const auto& [k, arista] : aristas_) {
        if (arista.esInicial(v))
            aristasSalida.push_back(arista);
    }
    return aristasSalida;
}

template <typename T>
void Grafo<T>::dfsAux(const T& v, map<T, bool>& visitados) const {
    visitados[v] = true;
    for (const T& vecino : obtenerVecinos(v)) {
        if (!visitados[vecino]) {
            dfsAux(vecino, visitados);
        }
    }
}

template <typename T>
int Grafo<T>::contarComponentesConexas() const {
    map<T, bool> visitados;
    for (const T& v : vertices_) visitados[v] = false;

    int contador = 0;
    for (const T& v : vertices_) {
        if (!visitados[v]) {
            dfsAux(v, visitados);
            contador++;
        }
    }
    return contador;
}

template <typename T>
bool Grafo<T>::existeCamino(const T& origen, const T& destino) const {
    map<T, bool> visitados;
    for (const T& v : vertices_) visitados[v] = false;

    dfsAux(origen, visitados);
    return visitados[destino];
}

template <typename T>
bool Grafo<T>::existeCicloDirigidoUtil(const T& v, map<T, bool>& visitados, map<T, bool>& pila) const {
    visitados[v] = true;
    pila[v] = true;

    for (const T& vecino : obtenerVecinos(v)) {
        if (!visitados[vecino] && existeCicloDirigidoUtil(vecino, visitados, pila)) return true;
        else if (pila[vecino]) return true;
    }

    pila[v] = false;
    return false;
}

template <typename T>
bool Grafo<T>::existeCiclo() const {
    if (!dirigido_) return false;

    map<T, bool> visitados, pila;
    for (const T& v : vertices_) {
        visitados[v] = false;
        pila[v] = false;
    }

    for (const T& v : vertices_) {
        if (!visitados[v]) {
            if (existeCicloDirigidoUtil(v, visitados, pila)) return true;
        }
    }
    return false;
}

template <typename T>
void Grafo<T>::imprimir() const {
    for (const T& v : vertices_) {
        cout << to_id(v) << ": ";
        for (const T& vecino : obtenerVecinos(v))
            cout << to_id(vecino) << " ";
        cout << "\n";
    }
}

#endif
