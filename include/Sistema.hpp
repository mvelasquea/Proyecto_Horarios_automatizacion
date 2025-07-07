#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Curso.hpp"
#include "Grupo.hpp"
#include "PSGraph/Grafo.hpp"

class Sistema {
private:
    std::unordered_map<std::string, Curso> cursos; // curso_codigo -> Curso
    Grafo<Grupo*> grafoGrupos;                     // grafo no dirigido de punteros a Grupo

    // Determina si dos grupos no pueden programarse juntos
    bool sonIncompatibles(Grupo* g1, Grupo* g2);

public:
    Sistema();

    // Carga cursos y grupos desde un archivo CSV
    bool cargarDatos(const std::string& rutaCSV);

    // Acceso
    Curso* obtenerCurso(const std::string& codigo);
    Grupo* obtenerGrupo(const std::string& idGrupo);
    std::vector<Grupo*> obtenerGruposDeCurso(const std::string& codigo);

    // Extra
    void imprimirDatos() const;
    const std::unordered_map<std::string, Curso>& getCursos() const { return cursos; }
    const Grafo<Grupo*>& getGrafoGrupos() const { return grafoGrupos; }
};
