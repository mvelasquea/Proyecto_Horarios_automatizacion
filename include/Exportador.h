#ifndef EXPORTADOR_H
#define EXPORTADOR_H

#include "Curso.h"
#include <vector>
#include <string>

class Exportador {
public:
    static void exportarCSV(const std::vector<Curso>& cursos, const std::string& nombreArchivo);
    static void exportarJSON(const std::vector<Curso>& cursos, const std::string& nombreArchivo); // ✅ AÑADIDO
};

#endif
