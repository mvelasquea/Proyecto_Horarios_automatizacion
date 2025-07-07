#include "Sistema.hpp"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Uso: " << argv[0] << " <ruta a CSV de grupos>\n";
            return 1;
        }

        Sistema sistema;
        if (!sistema.cargarDatos(argv[1])) {
            std::cerr << "No se pudieron cargar los datos.\n";
            return 1;
        }
        sistema.imprimirDatos();

        std::cout << "Datos cargados correctamente.\n";
    } catch (const std::exception& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
    }
    return 0;
}
