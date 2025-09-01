#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

// Estructura para los datos del curso con el formato especificado
struct CursoData {
    std::string curso;
    std::string nombre;
    std::string grupo_id;
    std::string tipo;
    std::string aula;
    std::string horas;
    std::string docente;
    int cupos;
    bool seleccionado;
    
    CursoData(const std::string& c, const std::string& n, const std::string& g, 
              const std::string& t, const std::string& a, const std::string& h, 
              const std::string& d, int cu, bool sel = false)
        : curso(c), nombre(n), grupo_id(g), tipo(t), aula(a), horas(h), docente(d), cupos(cu), seleccionado(sel) {}
};

class SistemaHorarios {
private:
    std::vector<CursoData> cursos;
    
public:
    SistemaHorarios() {
        cargarDatosIniciales();
    }
    
    void cargarDatosIniciales() {
        // Datos con el formato especificado que me proporcionaste
        cursos = {
            CursoData("1703133", "PROGRAMACION WEB 1", "1", "F", "B201", "1_08:00-09:40 3_08:00-09:40", "María López", 25),
            CursoData("1703133", "PROGRAMACION WEB 1", "2", "F", "B202", "1_08:30-10:10 3_08:30-10:10", "Carlos Sánchez", 28),
            CursoData("1703133", "PROGRAMACION WEB 1", "101", "L", "Lab1", "2_10:00-11:40", "Juan Pérez", 18),
            CursoData("1703134", "ESTRUCTURAS DE DATOS", "1", "F", "C105", "1_08:00-09:40 3_08:00-09:40", "Laura Méndez", 22),
            CursoData("1703134", "ESTRUCTURAS DE DATOS", "2", "F", "C106", "1_09:00-10:40 3_09:00-10:40", "Diego Castillo", 21),
            CursoData("1703134", "ESTRUCTURAS DE DATOS", "101", "L", "Lab5", "2_10:00-11:40", "Andrés López", 19),
            CursoData("1703135", "BASE DE DATOS 1", "1", "F", "D303", "1_10:00-11:40 3_10:00-11:40", "Ana Martínez", 18),
            CursoData("1703135", "BASE DE DATOS 1", "2", "F", "D304", "1_10:30-12:10 3_10:30-12:10", "Ricardo Torres", 19),
            CursoData("1703135", "BASE DE DATOS 1", "101", "L", "Lab9", "2_14:00-15:40", "Claudia Ruiz", 15),
            CursoData("1701212", "PROGRAMACION WEB 1", "1", "F", "D401", "1_16:00-18:00 2_08:00-10:00", "Ing. Sandra Vega", 25),
            CursoData("1701212", "PROGRAMACION WEB 1", "101", "L", "Lab2", "4_08:00-12:00", "Ing. Miguel Flores", 15)
        };
    }
    
    void mostrarTitulo() {
        std::cout << "\n";
        std::cout << "===============================================\n";
        std::cout << "    SISTEMA DE GESTIÓN DE HORARIOS\n";
        std::cout << "      Checklist de Cursos y Grupos\n";
        std::cout << "===============================================\n";
        std::cout << "\n";
    }
    
    void mostrarTabla() {
        std::cout << "\n";
        std::cout << std::left 
                  << std::setw(3) << "Sel"
                  << std::setw(10) << "Curso"
                  << std::setw(25) << "Nombre"
                  << std::setw(6) << "Grupo"
                  << std::setw(5) << "Tipo"
                  << std::setw(8) << "Aula"
                  << std::setw(25) << "Horas"
                  << std::setw(18) << "Docente"
                  << std::setw(6) << "Cupos"
                  << std::endl;
        
        std::cout << std::string(110, '-') << std::endl;
        
        for (size_t i = 0; i < cursos.size(); ++i) {
            const auto& curso = cursos[i];
            std::cout << std::left
                      << std::setw(3) << (curso.seleccionado ? "[X]" : "[ ]")
                      << std::setw(10) << curso.curso
                      << std::setw(25) << curso.nombre.substr(0, 24)
                      << std::setw(6) << curso.grupo_id
                      << std::setw(5) << curso.tipo
                      << std::setw(8) << curso.aula
                      << std::setw(25) << curso.horas.substr(0, 24)
                      << std::setw(18) << curso.docente.substr(0, 17)
                      << std::setw(6) << curso.cupos
                      << std::endl;
        }
        
        std::cout << std::string(110, '-') << std::endl;
        std::cout << "Total de cursos: " << cursos.size() << std::endl;
        std::cout << "Cursos seleccionados: " << contarSeleccionados() << std::endl;
        std::cout << "\n";
    }
    
    void mostrarMenu() {
        std::cout << "OPCIONES DISPONIBLES:\n";
        std::cout << "1. Seleccionar/deseleccionar curso\n";
        std::cout << "2. Seleccionar todos los cursos\n";
        std::cout << "3. Deseleccionar todos los cursos\n";
        std::cout << "4. Agregar nuevo curso\n";
        std::cout << "5. Editar curso existente\n";
        std::cout << "6. Eliminar curso\n";
        std::cout << "7. Exportar seleccionados a CSV\n";
        std::cout << "8. Mostrar formato de horas\n";
        std::cout << "9. Salir\n";
        std::cout << "\nIngrese su opción: ";
    }
    
    void ejecutar() {
        int opcion;
        
        while (true) {
            mostrarTitulo();
            mostrarTabla();
            mostrarMenu();
            
            std::cin >> opcion;
            
            switch (opcion) {
                case 1:
                    toggleSeleccion();
                    break;
                case 2:
                    seleccionarTodos();
                    break;
                case 3:
                    deseleccionarTodos();
                    break;
                case 4:
                    agregarCurso();
                    break;
                case 5:
                    editarCurso();
                    break;
                case 6:
                    eliminarCurso();
                    break;
                case 7:
                    exportarCSV();
                    break;
                case 8:
                    mostrarFormatoHoras();
                    break;
                case 9:
                    std::cout << "\n¡Gracias por usar el Sistema de Gestión de Horarios!\n";
                    return;
                default:
                    std::cout << "\nOpción inválida. Presione Enter para continuar...\n";
                    std::cin.ignore();
                    std::cin.get();
            }
        }
    }
    
    void toggleSeleccion() {
        int indice;
        std::cout << "\nIngrese el número del curso (1-" << cursos.size() << "): ";
        std::cin >> indice;
        
        if (indice < 1 || indice > static_cast<int>(cursos.size())) {
            std::cout << "Índice inválido.\n";
            return;
        }
        
        cursos[indice - 1].seleccionado = !cursos[indice - 1].seleccionado;
        std::cout << "Curso " << (cursos[indice - 1].seleccionado ? "seleccionado" : "deseleccionado") << ".\n";
        
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    void seleccionarTodos() {
        for (auto& curso : cursos) {
            curso.seleccionado = true;
        }
        std::cout << "\nTodos los cursos han sido seleccionados.\n";
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    void deseleccionarTodos() {
        for (auto& curso : cursos) {
            curso.seleccionado = false;
        }
        std::cout << "\nTodos los cursos han sido deseleccionados.\n";
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    void agregarCurso() {
        std::cout << "\n=== AGREGAR NUEVO CURSO ===\n";
        std::string curso, nombre, grupo_id, tipo, aula, horas, docente;
        int cupos;
        
        std::cin.ignore();
        std::cout << "Código del curso: ";
        std::getline(std::cin, curso);
        
        std::cout << "Nombre del curso: ";
        std::getline(std::cin, nombre);
        
        std::cout << "Grupo ID: ";
        std::getline(std::cin, grupo_id);
        
        std::cout << "Tipo (F=Formal, L=Laboratorio): ";
        std::getline(std::cin, tipo);
        
        std::cout << "Aula: ";
        std::getline(std::cin, aula);
        
        std::cout << "Horas (formato: 1_08:00-09:40 3_08:00-09:40): ";
        std::getline(std::cin, horas);
        
        std::cout << "Docente: ";
        std::getline(std::cin, docente);
        
        std::cout << "Cupos: ";
        std::cin >> cupos;
        
        cursos.push_back(CursoData(curso, nombre, grupo_id, tipo, aula, horas, docente, cupos));
        
        std::cout << "\nCurso agregado exitosamente.\n";
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    void editarCurso() {
        int indice;
        std::cout << "\nIngrese el número del curso a editar (1-" << cursos.size() << "): ";
        std::cin >> indice;
        
        if (indice < 1 || indice > static_cast<int>(cursos.size())) {
            std::cout << "Índice inválido.\n";
            return;
        }
        
        auto& curso = cursos[indice - 1];
        
        std::cout << "\n=== EDITAR CURSO ===\n";
        std::cout << "Datos actuales del curso:\n";
        std::cout << "Código: " << curso.curso << "\n";
        std::cout << "Nombre: " << curso.nombre << "\n";
        std::cout << "Grupo: " << curso.grupo_id << "\n";
        std::cout << "Tipo: " << curso.tipo << "\n";
        std::cout << "Aula: " << curso.aula << "\n";
        std::cout << "Horas: " << curso.horas << "\n";
        std::cout << "Docente: " << curso.docente << "\n";
        std::cout << "Cupos: " << curso.cupos << "\n\n";
        
        std::cin.ignore();
        std::string nuevo_valor;
        
        std::cout << "Nuevo código (Enter para mantener): ";
        std::getline(std::cin, nuevo_valor);
        if (!nuevo_valor.empty()) curso.curso = nuevo_valor;
        
        std::cout << "Nuevo nombre (Enter para mantener): ";
        std::getline(std::cin, nuevo_valor);
        if (!nuevo_valor.empty()) curso.nombre = nuevo_valor;
        
        std::cout << "Nuevo grupo ID (Enter para mantener): ";
        std::getline(std::cin, nuevo_valor);
        if (!nuevo_valor.empty()) curso.grupo_id = nuevo_valor;
        
        std::cout << "Nuevo tipo (Enter para mantener): ";
        std::getline(std::cin, nuevo_valor);
        if (!nuevo_valor.empty()) curso.tipo = nuevo_valor;
        
        std::cout << "Nueva aula (Enter para mantener): ";
        std::getline(std::cin, nuevo_valor);
        if (!nuevo_valor.empty()) curso.aula = nuevo_valor;
        
        std::cout << "Nuevas horas (Enter para mantener): ";
        std::getline(std::cin, nuevo_valor);
        if (!nuevo_valor.empty()) curso.horas = nuevo_valor;
        
        std::cout << "Nuevo docente (Enter para mantener): ";
        std::getline(std::cin, nuevo_valor);
        if (!nuevo_valor.empty()) curso.docente = nuevo_valor;
        
        std::cout << "Nuevos cupos (0 para mantener): ";
        int nuevos_cupos;
        std::cin >> nuevos_cupos;
        if (nuevos_cupos > 0) curso.cupos = nuevos_cupos;
        
        std::cout << "\nCurso editado exitosamente.\n";
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    void eliminarCurso() {
        int indice;
        std::cout << "\nIngrese el número del curso a eliminar (1-" << cursos.size() << "): ";
        std::cin >> indice;
        
        if (indice < 1 || indice > static_cast<int>(cursos.size())) {
            std::cout << "Índice inválido.\n";
            return;
        }
        
        const auto& curso = cursos[indice - 1];
        std::cout << "\n¿Está seguro de eliminar el curso " << curso.curso << " - " << curso.nombre << "? (s/n): ";
        char confirmacion;
        std::cin >> confirmacion;
        
        if (confirmacion == 's' || confirmacion == 'S') {
            cursos.erase(cursos.begin() + indice - 1);
            std::cout << "Curso eliminado exitosamente.\n";
        } else {
            std::cout << "Operación cancelada.\n";
        }
        
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    void exportarCSV() {
        std::vector<CursoData> seleccionados;
        for (const auto& curso : cursos) {
            if (curso.seleccionado) {
                seleccionados.push_back(curso);
            }
        }
        
        if (seleccionados.empty()) {
            std::cout << "\nNo hay cursos seleccionados para exportar.\n";
            std::cout << "Presione Enter para continuar...\n";
            std::cin.ignore();
            std::cin.get();
            return;
        }
        
        std::ofstream archivo("cursos_seleccionados.csv");
        if (!archivo.is_open()) {
            std::cout << "\nError al crear el archivo CSV.\n";
            return;
        }
        
        // Escribir encabezados
        archivo << "curso,nombre,grupo_id,tipo,aula,horas,docente,cupos\n";
        
        // Escribir datos
        for (const auto& curso : seleccionados) {
            archivo << curso.curso << ","
                    << "\"" << curso.nombre << "\","
                    << curso.grupo_id << ","
                    << curso.tipo << ","
                    << curso.aula << ","
                    << "\"" << curso.horas << "\","
                    << "\"" << curso.docente << "\","
                    << curso.cupos << "\n";
        }
        
        archivo.close();
        
        std::cout << "\nArchivo 'cursos_seleccionados.csv' creado exitosamente.\n";
        std::cout << "Cursos exportados: " << seleccionados.size() << "\n";
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    void mostrarFormatoHoras() {
        std::cout << "\n=== FORMATO DE HORAS ===\n";
        std::cout << "El formato de horas utilizado es:\n";
        std::cout << "DIA_HORA_INICIO-HORA_FIN\n\n";
        
        std::cout << "Códigos de días:\n";
        std::cout << "1 = Lunes\n";
        std::cout << "2 = Martes\n";
        std::cout << "3 = Miércoles\n";
        std::cout << "4 = Jueves\n";
        std::cout << "5 = Viernes\n\n";
        
        std::cout << "Ejemplos:\n";
        std::cout << "1_08:00-09:40 3_08:00-09:40  -> Lunes y Miércoles de 8:00 a 9:40\n";
        std::cout << "2_10:00-11:40                -> Martes de 10:00 a 11:40\n";
        std::cout << "4_08:00-12:00                -> Jueves de 8:00 a 12:00\n";
        std::cout << "1_16:00-18:00 2_08:00-10:00  -> Lunes 16:00-18:00 y Martes 8:00-10:00\n\n";
        
        std::cout << "Tipos de curso:\n";
        std::cout << "F = Formal (Teoría)\n";
        std::cout << "L = Laboratorio (Práctica)\n\n";
        
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore();
        std::cin.get();
    }
    
    int contarSeleccionados() {
        int contador = 0;
        for (const auto& curso : cursos) {
            if (curso.seleccionado) contador++;
        }
        return contador;
    }
};

int main() {
    SistemaHorarios sistema;
    sistema.ejecutar();
    return 0;
}
