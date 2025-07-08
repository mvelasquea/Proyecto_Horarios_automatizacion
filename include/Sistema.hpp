#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Curso.hpp"
#include "Hora.hpp"

class Sistema {
private:
    std::unordered_map<std::string, Curso> cursos; // curso_codigo -> Curso

public:
    Sistema();

    // Carga cursos desde CSV
    void cargarCursos(const std::string& rutaCSV);
    void cargarGrupos(const std::string& rutaCSV);
    Hora parsearHora(const std::string& strHora, const std::string& aula);
    // Acceso
    Curso* obtenerCurso(const std::string& codigo);
    const std::unordered_map<std::string, Curso>& getCursos() const { return cursos; }

    // Extra
    string limpiarCampo(const std::string& campo);
    void imprimirCursos() const;
    void imprimirGrupos() const;
};
