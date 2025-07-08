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
        sistema.imprimirGrafo();
        //sistema.generarHorarios(true);
        //sistema.verHorarios();

        std::cout << "Datos cargados correctamente.\n";
    } catch (const std::exception& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
    }
    return 0;
}