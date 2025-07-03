#include "Validacion.h"
#include <unordered_map>

bool Validacion::validarGrupoUnicoPorCurso(const std::vector<Curso>& cursos) {
    std::unordered_map<std::string, int> conteo;
    for (const auto& curso : cursos) {
        conteo[curso.obtenerCodigo()]++;
        if (conteo[curso.obtenerCodigo()] > 1) return false;
    }
    return true;
}
