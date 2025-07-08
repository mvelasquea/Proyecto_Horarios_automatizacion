#include "Sistema.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Sistema sistema;
        sistema.cargarCursos("../data/ESPIS-cursos-2017.csv");
        sistema.cargarGrupos("../data/h1.csv");
        sistema.cargarGrafo();
        
        // Verificar datos cargados
        sistema.verificarDatosCargados();
        
        // Generar horarios (true para incluir laboratorios)
        sistema.generarHorarios(true);
        
        if (sistema.getHorarios().empty()) {
            cout << "\nNo se encontraron horarios válidos. Posibles razones:\n";
            cout << "1. Conflictos horarios entre grupos obligatorios\n";
            cout << "2. No hay suficientes grupos para cubrir todos los cursos\n";
            cout << "3. Los laboratorios requeridos no tienen grupos disponibles\n";
        } else {
            sistema.verHorarios();
            cout << "\nTotal de horarios generados: " << sistema.getHorarios().size() << endl;
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}