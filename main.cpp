#include "CargaDatos.h"
#include "Filtros.h"
#include "GeneradorHorarios.h"
#include "Visualizacion.h"
#include "Exportador.h"
#include <iostream>

int main() {
    std::string archivo = "data/cursos.csv";
    auto datos = CargaDatos::cargarCursos(archivo);

    std::vector<Curso> todos;
    for (const auto& [codigo, lista] : datos) {
        todos.insert(todos.end(), lista.begin(), lista.end());
    }

    auto filtrados = Filtros::filtrarPorTurno(todos, "mañana");
    auto combinaciones = GeneradorHorarios::generarCombinaciones(filtrados, 5);

    if (!combinaciones.empty()) {
        Visualizacion::imprimirHorario(combinaciones[0]);
        Exportador::exportarCSV(combinaciones[0], "data/horario_final.csv");
    } else {
        std::cout << "No se encontraron horarios válidos.\n";
    }

    return 0;
}
