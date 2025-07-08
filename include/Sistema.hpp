#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Curso.hpp"

class Sistema {
private:
    std::unordered_map<std::string, Curso> cursos; // curso_codigo -> Curso

public:
    Sistema();

    // Carga cursos desde CSV
    void cargarCursos(const std::string& rutaCSV);

    // Acceso
    Curso* obtenerCurso(const std::string& codigo);
    const std::unordered_map<std::string, Curso>& getCursos() const { return cursos; }

    // Extra
    void imprimirCursos() const;
};
