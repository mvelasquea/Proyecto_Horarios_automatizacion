#include "CargaDatos.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::unordered_map<std::string, std::vector<Curso>> CargaDatos::cargarCursos(const std::string& archivoCSV) {
    std::unordered_map<std::string, std::vector<Curso>> cursos;
    std::ifstream archivo(archivoCSV);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string codigo, nombre, creditos, grupo, dia, franja, tipo;

        std::getline(ss, codigo, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, creditos, ',');
        std::getline(ss, grupo, ',');
        std::getline(ss, dia, ',');
        std::getline(ss, franja, ',');
        std::getline(ss, tipo, ',');

        Curso curso(codigo, nombre, std::stoi(creditos), grupo);
        curso.agregarHorario({dia, franja, tipo});
        cursos[codigo].push_back(curso);
    }

    return cursos;
}
