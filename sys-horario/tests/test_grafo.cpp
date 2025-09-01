#include <iostream>
#include "../include/PSGraph/Grafo.hpp"

using namespace std;

int main() {
    // Crear grafo no dirigido de enteros
    Grafo<int> g(false);

    // Insertar aristas (que insertan vértices implícitamente)
    g.insertarArista(Arista<int>(1, 2));
    g.insertarArista(Arista<int>(2, 3));
    g.insertarArista(Arista<int>(3, 4));
    g.insertarArista(Arista<int>(4, 1));
    g.insertarArista(Arista<int>(2, 4));
    g.insertarArista(Arista<int>(5, 6)); // componente desconectada

    cout << "Grafo: \n";
    g.imprimir();

    cout << "\nGrado de 2: " << g.grado(2) << "\n";
    cout << "Grado total (número de aristas): " << g.gradoTotal() << "\n";

    cout << "\nVecinos de 3: ";
    for (int v : g.obtenerVecinos(3)) cout << v << " ";
    cout << "\n";

    cout << "\nNúmero de componentes conexas: " << g.contarComponentesConexas() << "\n";

    cout << "\n¿Existe camino entre 1 y 4? " << (g.existeCamino(1, 4) ? "Sí" : "No") << "\n";
    cout << "¿Existe camino entre 1 y 6? " << (g.existeCamino(1, 6) ? "Sí" : "No") << "\n";

    // Grafo dirigido para ciclo
    Grafo<int> gd(true);
    gd.insertarArista(Arista<int>(1, 2, true));
    gd.insertarArista(Arista<int>(2, 3, true));
    gd.insertarArista(Arista<int>(3, 1, true)); // ciclo 1->2->3->1

    cout << "\nGrafo dirigido con ciclo:\n";
    gd.imprimir();
    cout << "¿Existe ciclo en grafo dirigido? " << (gd.existeCiclo() ? "Sí" : "No") << "\n";

    // Grafo dirigido sin ciclo
    Grafo<int> gd2(true);
    gd2.insertarArista(Arista<int>(1, 2, true));
    gd2.insertarArista(Arista<int>(2, 3, true));

    cout << "\nGrafo dirigido sin ciclo:\n";
    gd2.imprimir();
    cout << "¿Existe ciclo en grafo dirigido? " << (gd2.existeCiclo() ? "Sí" : "No") << "\n";

    return 0;
}
