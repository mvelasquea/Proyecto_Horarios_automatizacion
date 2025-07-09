#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Estructura para los datos del curso
struct CursoData {
    std::string curso;
    std::string grupo_id;
    std::string tipo;
    std::string aula;
    std::string horas;
    std::string docente;
    int cupos;
    bool seleccionado;
};

// Variables globales
std::vector<CursoData> g_cursos;

// Prototipos de funciones
void MostrarMenu();
void MostrarCursos();
void AgregarCurso();
void EditarCurso();
void EliminarCurso();
void SeleccionarCurso();
void SeleccionarTodos();
void DeseleccionarTodos();
void ExportarCSV();
void CargarDatosEjemplo();
int LeerOpcion();
std::string LeerTexto(const std::string& prompt);
int LeerEntero(const std::string& prompt);

int main() {
    std::cout << "=== Gestor de Cursos y Grupos - Exportador CSV ===" << std::endl;
    std::cout << "Versión de consola para Linux" << std::endl;
    std::cout << "===============================================" << std::endl;
    
    // Cargar datos de ejemplo
    CargarDatosEjemplo();
    
    int opcion;
    do {
        MostrarMenu();
        opcion = LeerOpcion();
        
        switch (opcion) {
            case 1:
                MostrarCursos();
                break;
            case 2:
                AgregarCurso();
                break;
            case 3:
                EditarCurso();
                break;
            case 4:
                EliminarCurso();
                break;
            case 5:
                SeleccionarCurso();
                break;
            case 6:
                SeleccionarTodos();
                break;
            case 7:
                DeseleccionarTodos();
                break;
            case 8:
                ExportarCSV();
                break;
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
        
        if (opcion != 0) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (opcion != 0);
    
    return 0;
}

void MostrarMenu() {
    std::cout << "\n=== MENÚ PRINCIPAL ===" << std::endl;
    std::cout << "1. Mostrar cursos" << std::endl;
    std::cout << "2. Agregar curso" << std::endl;
    std::cout << "3. Editar curso" << std::endl;
    std::cout << "4. Eliminar curso" << std::endl;
    std::cout << "5. Seleccionar/Deseleccionar curso" << std::endl;
    std::cout << "6. Seleccionar todos" << std::endl;
    std::cout << "7. Deseleccionar todos" << std::endl;
    std::cout << "8. Exportar cursos seleccionados a CSV" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void MostrarCursos() {
    std::cout << "\n=== LISTA DE CURSOS ===" << std::endl;
    if (g_cursos.empty()) {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }
    
    std::cout << std::left;
    std::cout << std::setw(3) << "#" 
              << std::setw(3) << "Sel" 
              << std::setw(10) << "Curso" 
              << std::setw(8) << "Grupo" 
              << std::setw(12) << "Tipo" 
              << std::setw(8) << "Aula" 
              << std::setw(20) << "Horas" 
              << std::setw(20) << "Docente" 
              << std::setw(6) << "Cupos" << std::endl;
    
    std::cout << std::string(90, '-') << std::endl;
    
    for (size_t i = 0; i < g_cursos.size(); ++i) {
        const auto& curso = g_cursos[i];
        std::cout << std::setw(3) << (i + 1)
                  << std::setw(3) << (curso.seleccionado ? "[X]" : "[ ]")
                  << std::setw(10) << curso.curso
                  << std::setw(8) << curso.grupo_id
                  << std::setw(12) << curso.tipo
                  << std::setw(8) << curso.aula
                  << std::setw(20) << curso.horas
                  << std::setw(20) << curso.docente
                  << std::setw(6) << curso.cupos << std::endl;
    }
    
    // Mostrar resumen
    int seleccionados = std::count_if(g_cursos.begin(), g_cursos.end(), 
                                     [](const CursoData& c) { return c.seleccionado; });
    std::cout << "\nTotal de cursos: " << g_cursos.size() << std::endl;
    std::cout << "Cursos seleccionados: " << seleccionados << std::endl;
}

void AgregarCurso() {
    std::cout << "\n=== AGREGAR CURSO ===" << std::endl;
    
    CursoData nuevo;
    nuevo.curso = LeerTexto("Código del curso: ");
    nuevo.grupo_id = LeerTexto("ID del grupo: ");
    
    // Validar tipo
    std::cout << "Tipo de curso (1=TEORIA, 2=LABORATORIO, 3=PRACTICA): ";
    int tipoOpcion = LeerOpcion();
    switch (tipoOpcion) {
        case 1: nuevo.tipo = "TEORIA"; break;
        case 2: nuevo.tipo = "LABORATORIO"; break;
        case 3: nuevo.tipo = "PRACTICA"; break;
        default: nuevo.tipo = "TEORIA"; break;
    }
    
    nuevo.aula = LeerTexto("Aula: ");
    nuevo.horas = LeerTexto("Horario (ej: L:08-10, M:14-16): ");
    nuevo.docente = LeerTexto("Docente: ");
    nuevo.cupos = LeerEntero("Número de cupos: ");
    nuevo.seleccionado = false;
    
    g_cursos.push_back(nuevo);
    std::cout << "Curso agregado exitosamente!" << std::endl;
}

void EditarCurso() {
    std::cout << "\n=== EDITAR CURSO ===" << std::endl;
    MostrarCursos();
    
    if (g_cursos.empty()) return;
    
    std::cout << "\nSeleccione el número del curso a editar (1-" << g_cursos.size() << "): ";
    int indice = LeerOpcion() - 1;
    
    if (indice < 0 || indice >= static_cast<int>(g_cursos.size())) {
        std::cout << "Índice no válido." << std::endl;
        return;
    }
    
    CursoData& curso = g_cursos[indice];
    
    std::cout << "Editando curso: " << curso.curso << " - Grupo " << curso.grupo_id << std::endl;
    std::cout << "Presione Enter para mantener el valor actual." << std::endl;
    
    std::string temp = LeerTexto("Código del curso [" + curso.curso + "]: ");
    if (!temp.empty()) curso.curso = temp;
    
    temp = LeerTexto("ID del grupo [" + curso.grupo_id + "]: ");
    if (!temp.empty()) curso.grupo_id = temp;
    
    std::cout << "Tipo actual: " << curso.tipo << std::endl;
    std::cout << "Nuevo tipo (1=TEORIA, 2=LABORATORIO, 3=PRACTICA, 0=mantener): ";
    int tipoOpcion = LeerOpcion();
    switch (tipoOpcion) {
        case 1: curso.tipo = "TEORIA"; break;
        case 2: curso.tipo = "LABORATORIO"; break;
        case 3: curso.tipo = "PRACTICA"; break;
    }
    
    temp = LeerTexto("Aula [" + curso.aula + "]: ");
    if (!temp.empty()) curso.aula = temp;
    
    temp = LeerTexto("Horario [" + curso.horas + "]: ");
    if (!temp.empty()) curso.horas = temp;
    
    temp = LeerTexto("Docente [" + curso.docente + "]: ");
    if (!temp.empty()) curso.docente = temp;
    
    std::cout << "Cupos actuales: " << curso.cupos << std::endl;
    std::cout << "Nuevos cupos (0=mantener): ";
    int nuevoCupos = LeerOpcion();
    if (nuevoCupos > 0) curso.cupos = nuevoCupos;
    
    std::cout << "Curso editado exitosamente!" << std::endl;
}

void EliminarCurso() {
    std::cout << "\n=== ELIMINAR CURSO ===" << std::endl;
    MostrarCursos();
    
    if (g_cursos.empty()) return;
    
    std::cout << "\nSeleccione el número del curso a eliminar (1-" << g_cursos.size() << "): ";
    int indice = LeerOpcion() - 1;
    
    if (indice < 0 || indice >= static_cast<int>(g_cursos.size())) {
        std::cout << "Índice no válido." << std::endl;
        return;
    }
    
    const CursoData& curso = g_cursos[indice];
    std::cout << "¿Está seguro de eliminar el curso " << curso.curso 
              << " - Grupo " << curso.grupo_id << "? (s/N): ";
    
    std::string confirmacion;
    std::getline(std::cin, confirmacion);
    
    if (confirmacion == "s" || confirmacion == "S") {
        g_cursos.erase(g_cursos.begin() + indice);
        std::cout << "Curso eliminado exitosamente!" << std::endl;
    } else {
        std::cout << "Eliminación cancelada." << std::endl;
    }
}

void SeleccionarCurso() {
    std::cout << "\n=== SELECCIONAR/DESELECCIONAR CURSO ===" << std::endl;
    MostrarCursos();
    
    if (g_cursos.empty()) return;
    
    std::cout << "\nSeleccione el número del curso (1-" << g_cursos.size() << "): ";
    int indice = LeerOpcion() - 1;
    
    if (indice < 0 || indice >= static_cast<int>(g_cursos.size())) {
        std::cout << "Índice no válido." << std::endl;
        return;
    }
    
    g_cursos[indice].seleccionado = !g_cursos[indice].seleccionado;
    std::cout << "Curso " << (g_cursos[indice].seleccionado ? "seleccionado" : "deseleccionado") 
              << " exitosamente!" << std::endl;
}

void SeleccionarTodos() {
    for (auto& curso : g_cursos) {
        curso.seleccionado = true;
    }
    std::cout << "\nTodos los cursos han sido seleccionados." << std::endl;
}

void DeseleccionarTodos() {
    for (auto& curso : g_cursos) {
        curso.seleccionado = false;
    }
    std::cout << "\nTodos los cursos han sido deseleccionados." << std::endl;
}

void ExportarCSV() {
    std::cout << "\n=== EXPORTAR A CSV ===" << std::endl;
    
    // Filtrar cursos seleccionados
    std::vector<CursoData> cursosSeleccionados;
    for (const auto& curso : g_cursos) {
        if (curso.seleccionado) {
            cursosSeleccionados.push_back(curso);
        }
    }
    
    if (cursosSeleccionados.empty()) {
        std::cout << "No hay cursos seleccionados para exportar." << std::endl;
        return;
    }
    
    std::string nombreArchivo = LeerTexto("Nombre del archivo CSV (sin extensión): ");
    if (nombreArchivo.empty()) {
        nombreArchivo = "cursos_seleccionados";
    }
    
    nombreArchivo += ".csv";
    
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "Error al crear el archivo CSV." << std::endl;
        return;
    }
    
    // Escribir cabecera
    archivo << "Curso,Grupo ID,Tipo,Aula,Horas,Docente,Cupos" << std::endl;
    
    // Escribir datos
    for (const auto& curso : cursosSeleccionados) {
        archivo << "\"" << curso.curso << "\",\"" << curso.grupo_id << "\",\"" 
                << curso.tipo << "\",\"" << curso.aula << "\",\"" 
                << curso.horas << "\",\"" << curso.docente << "\"," 
                << curso.cupos << std::endl;
    }
    
    archivo.close();
    
    std::cout << "Archivo CSV exportado exitosamente: " << nombreArchivo << std::endl;
    std::cout << "Cursos exportados: " << cursosSeleccionados.size() << std::endl;
}

void CargarDatosEjemplo() {
    g_cursos = {
        {"1703133", "1", "TEORIA", "B201", "L:08-10, M:14-16", "María López", 25, false},
        {"1703133", "2", "TEORIA", "B202", "L:08-10, M:14-16", "Carlos Sánchez", 28, false},
        {"1703133", "101", "LABORATORIO", "Lab1", "M:10-12", "Juan Pérez", 18, false},
        {"1703134", "1", "TEORIA", "C105", "L:08-10, M:14-16", "Laura Méndez", 22, false},
        {"1703134", "2", "TEORIA", "C106", "L:09-11, M:15-17", "Diego Castillo", 21, false},
        {"1703135", "1", "TEORIA", "D303", "L:10-12, M:16-18", "Ana Martínez", 18, false}
    };
}

int LeerOpcion() {
    int opcion;
    std::cin >> opcion;
    std::cin.ignore(); // Limpiar buffer
    return opcion;
}

std::string LeerTexto(const std::string& prompt) {
    std::cout << prompt;
    std::string texto;
    std::getline(std::cin, texto);
    return texto;
}

int LeerEntero(const std::string& prompt) {
    std::cout << prompt;
    int valor;
    std::cin >> valor;
    std::cin.ignore(); // Limpiar buffer
    return valor;
}
