#ifndef CARGADATOS_H
#define CARGADATOS_H

#include "Curso.h"
#include <string>
#include <unordered_map>
#include <vector>

class CargaDatos {
public:
    static std::unordered_map<std::string, std::vector<Curso>> cargarCursos(const std::string& archivoCSV);
};

#endif
