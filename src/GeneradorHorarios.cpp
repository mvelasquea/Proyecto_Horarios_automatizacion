#include "GeneradorHorarios.h"
#include "Validacion.h"

void backtrack(std::vector<Curso>& seleccion, const std::vector<Curso>& cursos, int i, int k,
               std::vector<std::vector<Curso>>& soluciones) {
    if (seleccion.size() == static_cast<size_t>(k)) {
        if (Validacion::validarGrupoUnicoPorCurso(seleccion)) {
            soluciones.push_back(seleccion);
        }
        return;
    }
    if (i >= static_cast<int>(cursos.size())) return;

    seleccion.push_back(cursos[i]);
    backtrack(seleccion, cursos, i + 1, k, soluciones);
    seleccion.pop_back();
    backtrack(seleccion, cursos, i + 1, k, soluciones);
}

std::vector<std::vector<Curso>> GeneradorHorarios::generarCombinaciones(const std::vector<Curso>& cursos, int k) {
    std::vector<std::vector<Curso>> soluciones;
    std::vector<Curso> seleccion;
    backtrack(seleccion, cursos, 0, k, soluciones);
    return soluciones;
}