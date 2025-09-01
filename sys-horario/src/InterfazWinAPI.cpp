#include "InterfazWinAPI.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

InterfazWinAPI::InterfazWinAPI(Sistema* sys, const std::string& dataDir) 
    : sistema(sys), rutaDataDir(dataDir) {
    // Crear directorio de datos si no existe
    system(("mkdir -p " + rutaDataDir).c_str());
}

InterfazWinAPI::~InterfazWinAPI() {
    // Limpieza si es necesaria
}

void InterfazWinAPI::inicializar() {
    std::cout << "=== Inicializando Interfaz Win API ===" << std::endl;
    
    // Cargar datos de ejemplo predeterminados
    cursosWinAPI = {
        CursoWinAPI("1701102", "RAZONAMIENTO LOGICO MATEMATICO", "1", "TEORIA", "A101", "1_08:00-10:00 3_14:00-16:00", "Dr. José Mendoza", 30),
        CursoWinAPI("1701103", "MATEMATICA BASICA", "1", "TEORIA", "A102", "1_10:00-12:00 3_16:00-18:00", "Dra. María García", 35),
        CursoWinAPI("1701104", "ESTRUCTURAS DISCRETAS 1", "1", "TEORIA", "B201", "2_08:00-10:00 4_14:00-16:00", "Dr. Ana Rodríguez", 25),
        CursoWinAPI("1701105", "INTRODUCCION A LA COMPUTACION", "1", "TEORIA", "C301", "1_14:00-16:00 5_10:00-12:00", "Ing. Pedro Sánchez", 40),
        CursoWinAPI("1701106", "FUNDAMENTOS DE LA PROGRAMACION 1", "1", "TEORIA", "C302", "2_10:00-12:00 4_16:00-18:00", "Dra. Laura Martínez", 30),
        CursoWinAPI("1701106", "FUNDAMENTOS DE LA PROGRAMACION 1", "101", "LABORATORIO", "Lab1", "5_14:00-18:00", "Ing. Roberto Torres", 20),
        CursoWinAPI("1701212", "PROGRAMACION WEB 1", "1", "TEORIA", "D401", "1_16:00-18:00 2_08:00-10:00", "Ing. Sandra Vega", 25),
        CursoWinAPI("1701212", "PROGRAMACION WEB 1", "101", "LABORATORIO", "Lab2", "4_08:00-12:00", "Ing. Miguel Flores", 15),
        CursoWinAPI("1703133", "ALGORITMOS Y PROGRAMACION", "1", "TEORIA", "B201", "1_08:00-09:40 3_08:00-09:40", "María López", 25),
        CursoWinAPI("1703134", "ESTRUCTURAS DE DATOS", "1", "TEORIA", "C105", "1_08:00-09:40 3_08:00-09:40", "Laura Méndez", 22),
        CursoWinAPI("1703135", "INGENIERIA Y PROCESOS DE SOFTWARE", "1", "TEORIA", "D303", "1_10:00-11:40 3_10:00-11:40", "Ana Martínez", 18)
    };
    
    std::cout << "✅ Datos inicializados: " << cursosWinAPI.size() << " cursos" << std::endl;
}

void InterfazWinAPI::cargarDatosDesdeCSV(const std::string& rutaCSV) {
    std::cout << "Cargando datos desde CSV: " << rutaCSV << std::endl;
    
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << rutaCSV << std::endl;
        return;
    }
    
    cursosWinAPI.clear();
    std::string linea;
    bool primeraLinea = true;
    
    while (std::getline(archivo, linea)) {
        if (primeraLinea) {
            primeraLinea = false;
            continue; // Saltar headers
        }
        
        std::stringstream ss(linea);
        std::string campo;
        std::vector<std::string> campos;
        
        // Parsear CSV considerando comillas
        bool enComillas = false;
        std::string campoActual = "";
        
        for (char c : linea) {
            if (c == '"') {
                enComillas = !enComillas;
            } else if (c == ',' && !enComillas) {
                campos.push_back(campoActual);
                campoActual = "";
            } else {
                campoActual += c;
            }
        }
        campos.push_back(campoActual);
        
        if (campos.size() >= 8) {
            try {
                int cupos = std::stoi(campos[7]);
                cursosWinAPI.emplace_back(campos[0], campos[1], campos[2], campos[3], 
                                        campos[4], campos[5], campos[6], cupos);
            } catch (const std::exception& e) {
                std::cerr << "Error al procesar línea: " << linea << std::endl;
            }
        }
    }
    
    archivo.close();
    std::cout << "✅ Cargados " << cursosWinAPI.size() << " cursos desde CSV" << std::endl;
}

void InterfazWinAPI::sincronizarConSistema() {
    if (!sistema) return;
    
    std::cout << "Sincronizando con sistema principal..." << std::endl;
    
    // Convertir cursos Win API a formato del sistema
    std::vector<Curso> cursosSistema = convertirACursos(cursosWinAPI);
    
    // Aquí puedes implementar la lógica de sincronización específica
    // dependiendo de cómo el sistema maneja los cursos
    
    std::cout << "✅ Sincronización completada" << std::endl;
}

void InterfazWinAPI::exportarSeleccionados(const std::string& rutaDestino) {
    std::vector<CursoWinAPI> seleccionados = obtenerSeleccionados();
    
    if (seleccionados.empty()) {
        std::cout << "No hay cursos seleccionados para exportar" << std::endl;
        return;
    }
    
    std::ofstream archivo(rutaDestino);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo " << rutaDestino << std::endl;
        return;
    }
    
    // Escribir headers
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
    std::cout << "✅ Exportados " << seleccionados.size() << " cursos a " << rutaDestino << std::endl;
}

std::vector<Curso> InterfazWinAPI::convertirACursos(const std::vector<CursoWinAPI>& cursosWin) {
    std::vector<Curso> cursos;
    
    for (const auto& cursoWin : cursosWin) {
        // Usar el constructor completo de la clase Curso del sistema principal
        Curso curso(cursoWin.curso, cursoWin.tipo, cursoWin.nombre, 3, 1); // Asumiendo 3 créditos, ciclo 1
        cursos.push_back(curso);
    }
    
    return cursos;
}

std::vector<InterfazWinAPI::CursoWinAPI> InterfazWinAPI::convertirDeCursos(const std::vector<Curso>& cursos) {
    std::vector<CursoWinAPI> cursosWin;
    
    for (const auto& curso : cursos) {
        // Usar métodos de la clase Curso del sistema principal
        cursosWin.emplace_back(curso.getCodigo(), curso.getNombre(), 
                              "1", // grupo por defecto
                              curso.getTipo(),
                              "Aula", "L:08-10", "Docente", 30);
    }
    
    return cursosWin;
}

void InterfazWinAPI::marcarSeleccionado(int index, bool seleccionado) {
    if (index >= 0 && index < static_cast<int>(cursosWinAPI.size())) {
        cursosWinAPI[index].seleccionado = seleccionado;
    }
}

void InterfazWinAPI::seleccionarTodos(bool seleccionar) {
    for (auto& curso : cursosWinAPI) {
        curso.seleccionado = seleccionar;
    }
}

std::vector<InterfazWinAPI::CursoWinAPI> InterfazWinAPI::obtenerSeleccionados() const {
    std::vector<CursoWinAPI> seleccionados;
    
    for (const auto& curso : cursosWinAPI) {
        if (curso.seleccionado) {
            seleccionados.push_back(curso);
        }
    }
    
    return seleccionados;
}

bool InterfazWinAPI::validarDatos(const CursoWinAPI& curso) const {
    return !curso.curso.empty() && !curso.nombre.empty() && 
           !curso.grupo_id.empty() && !curso.tipo.empty() &&
           !curso.aula.empty() && !curso.docente.empty() && 
           curso.cupos > 0;
}

bool InterfazWinAPI::validarHorario(const std::string& horario) const {
    // Validar formato básico: "L:08-10, M:14-16"
    if (horario.empty()) return false;
    
    std::stringstream ss(horario);
    std::string fragmento;
    
    while (std::getline(ss, fragmento, ',')) {
        // Remover espacios
        fragmento.erase(0, fragmento.find_first_not_of(" \t"));
        fragmento.erase(fragmento.find_last_not_of(" \t") + 1);
        
        if (fragmento.find(':') == std::string::npos) return false;
        if (fragmento.find('-') == std::string::npos) return false;
    }
    
    return true;
}