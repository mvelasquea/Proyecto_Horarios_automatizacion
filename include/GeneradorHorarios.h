#ifndef GENERADORHORARIOS_H
#define GENERADORHORARIOS_H

#include "Curso.h"
#include <vector>

class GeneradorHorarios {
public:
    static std::vector<std::vector<Curso>> generarCombinaciones(const std::vector<Curso>& cursos, int k);
};

#endif