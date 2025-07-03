#ifndef VALIDACION_H
#define VALIDACION_H

#include "Curso.h"
#include <vector>

class Validacion {
public:
    static bool validarGrupoUnicoPorCurso(const std::vector<Curso>& cursos);
    static bool validarChoquesTeoriaTeoria(const Curso& a, const Curso& b);
};

#endif