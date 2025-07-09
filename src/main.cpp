#include "Sistema.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Sistema sistema;
        sistema.cargarCursos("../data/ESPIS-cursos-2017.csv");
        //sistema.imprimirCursos();
        sistema.cargarGrupos("../data/h2.csv");
        //sistema.imprimirGrupos();
        sistema.cargarGrafo();
        //sistema.imprimirGrafo();
        for (auto& [codigo, curso] : sistema.getCursos()) {
            std::cout << "Curso: " << codigo << ", grupos: " << curso.getGrupos().size() << "\n";
            for (const auto& grupo : curso.getGrupos()) {
                std::cout << "  Grupo: " << grupo.getIdGrupo()
                        << ", Tipo: " << (grupo.esLab() ? "Lab" : "Teorico") << "\n";
            }
        }
        sistema.generarHorarios();
        sistema.verHorarios();

        std::cout << "Datos cargados correctamente.\n";
    } catch (const std::exception& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
    }
    return 0;
}