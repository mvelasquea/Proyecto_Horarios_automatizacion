#ifndef GRAFOHORARIO_H
#define GRAFOHORARIO_H

#include "Curso.h"
#include <map>
#include <set>
#include <string>

class GrafoHorario {
private:
    std::map<std::string, Curso> nodos;
    std::map<std::string, std::set<std::string>> conflictos;

public:
    void agregarCurso(const Curso& curso);
    void construirConflictos();
    const std::map<std::string, std::set<std::string>>& obtenerGrafo() const;
};

#endif
