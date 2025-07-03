// === include/Filtros.h ===
#ifndef FILTROS_H
#define FILTROS_H

#include "Curso.h"
#include <vector>
#include <string>

class Filtros {
public:
    static std::vector<Curso> filtrarPorTurno(const std::vector<Curso>& cursos, const std::string& turno);
};

#endif
