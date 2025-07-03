#include "GrafoHorario.h"
#include "Curso.h"
#include <cassert>
#include <iostream>

int main() {
    Curso a("MAT101", "Matemáticas", 4, "A");
    a.agregarHorario({"Lunes", "08:00", "teoria"});
    Curso b("FIS101", "Física", 4, "B");
    b.agregarHorario({"Lunes", "08:00", "teoria"});

    GrafoHorario grafo;
    grafo.agregarCurso(a);
    grafo.agregarCurso(b);
    grafo.construirConflictos();

    auto g = grafo.obtenerGrafo();
    assert(g["MAT101-A"].count("FIS101-B"));

    std::cout << "Test de grafo pasado.\n";
    return 0;
}
