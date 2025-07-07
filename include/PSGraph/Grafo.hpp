#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

using namespace std;

// --- Clase Arista ---

template <typename T>
class Arista {
public:
    T origen;
    T destino;
    double peso;
    bool dirigido;

public:
    Arista() noexcept = default;
    Arista(T origen, T destino, bool dirigido = false, double peso = 1.0) noexcept;

    vector<T> obtenerVertices() const;
    string toString() const;

    bool contiene(const T& v) const noexcept;
    bool esInicial(const T& v) const noexcept;
    T obtenerOtroVertice(const T& v) const;

    Arista<T> obtenerInversa() const noexcept;

    bool operator==(const Arista<T>& a) const noexcept;
    bool operator<(const Arista<T>& a) const;
};

// --- Clase Grafo ---

template <typename T>
class Grafo {
private:
    vector<T> vertices_;
    map<string, Arista<T>> aristas_;
    bool dirigido_;

    string hashArista(const Arista<T>& arista) const;

public:
    explicit Grafo(bool dirigido = false) noexcept;

    bool contieneVertice(const T& v) const noexcept;
    void insertarVertice(const T& v);

    bool contieneArista(const Arista<T>& a) const;
    void insertarArista(const Arista<T>& a);
    void eliminarArista(const Arista<T>& a);

    int grado(const T& v) const;
    int gradoTotal() const;

    vector<T> obtenerVecinos(const T& v) const;

    void dfsAux(const T& v, map<T, bool>& visitados) const;
    int contarComponentesConexas() const;
    bool existeCamino(const T& origen, const T& destino) const;

    bool existeCicloDirigidoUtil(const T& v, map<T, bool>& visitados, map<T, bool>& pila) const;
    bool existeCiclo() const;

    void imprimir() const;
};

// -- Declaración de helper para id único --
template <typename T>
std::string to_id(T obj);

#include "Grafo_impl.hpp"

#endif
