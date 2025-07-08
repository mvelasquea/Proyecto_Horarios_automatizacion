#include "Sistema.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Sistema sistema;
        sistema.cargarCursos("../data/ESPIS-cursos-2017.csv");
        sistema.imprimirCursos();
        std::cout << "Datos cargados correctamente.\n";
    } catch (const std::exception& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
    }
    return 0;
}
