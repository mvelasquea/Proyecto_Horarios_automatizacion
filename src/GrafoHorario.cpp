#include "GrafoHorario.h"

void GrafoHorario::agregarCurso(const Curso& curso) {
    nodos[curso.obtenerCodigoGrupo()] = curso;
}

void GrafoHorario::construirConflictos() {
    for (auto it1 = nodos.begin(); it1 != nodos.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != nodos.end(); ++it2) {
            for (const auto& h1 : it1->second.obtenerHorarios()) {
                for (const auto& h2 : it2->second.obtenerHorarios()) {
                    if (h1.dia == h2.dia && h1.franja == h2.franja) {
                        conflictos[it1->first].insert(it2->first);
                        conflictos[it2->first].insert(it1->first);
                    }
                }
            }
        }
    }
}

const std::map<std::string, std::set<std::string>>& GrafoHorario::obtenerGrafo() const {
    return conflictos;
}
