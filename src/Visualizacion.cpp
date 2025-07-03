#include "Visualizacion.h"
#include <iostream>

void Visualizacion::imprimirHorario(const std::vector<Curso>& cursos) {
    for (const auto& curso : cursos) {
        for (const auto& horario : curso.obtenerHorarios()) {
            std::cout << curso.obtenerCodigoGrupo() << " | "
                      << curso.obtenerNombre() << " | "
                      << horario.dia << " " << horario.franja
                      << " [" << horario.tipo << "]\n";
        }
    }
}
