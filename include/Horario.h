#ifndef HORARIO_H
#define HORARIO_H

#include "Curso.h"
#include <vector>

class Horario {
private:
    std::vector<Curso> cursos;

public:
    Horario(const std::vector<Curso>& cursos);
    int calcularCargaTotal() const;
    const std::vector<Curso>& obtenerCursos() const;
};

#endif
