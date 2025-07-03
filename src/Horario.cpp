#include "Horario.h"

Horario::Horario(const std::vector<Curso>& c) : cursos(c) {}

int Horario::calcularCargaTotal() const {
    int total = 0;
    for (const auto& curso : cursos) {
        total += curso.obtenerCreditos();
    }
    return total;
}

const std::vector<Curso>& Horario::obtenerCursos() const {
    return cursos;
}
