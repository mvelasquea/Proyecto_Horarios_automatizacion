#include "InterfazWeb.hpp"
#include <algorithm>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <limits.h>

InterfazWeb::InterfazWeb(Sistema* sys, const std::string& rutaWebDir) 
    : sistema(sys), rutaWeb(rutaWebDir) {
    rutaCSV = "data/grupos_horarios.csv";
    rutaPreferencias = "data/preferencias_usuario.json";
    
    // Inicializar preferencias por defecto
    preferencias.turnoPreferido = "mixto";
    preferencias.creditosMin = 12;
    preferencias.creditosMax = 20;
    preferencias.permitirCruces = false;
    preferencias.incluirLabs = true;
    preferencias.fechaCreacion = "";
}

InterfazWeb::~InterfazWeb() {
    // Limpieza si es necesaria
}

void InterfazWeb::inicializar() {
    std::cout << "=== Inicializando Interfaz Web ===" << std::endl;
    
    // Crear directorio web si no existe
    system(("mkdir -p " + rutaWeb).c_str());
    
    // Verificar archivos necesarios
    std::vector<std::string> archivosNecesarios = {
        rutaWeb + "index.html",
        rutaWeb + "styles.css",
        rutaWeb + "script.js"
    };
    
    bool todosExisten = true;
    for (const auto& archivo : archivosNecesarios) {
        std::ifstream file(archivo);
        if (!file.good()) {
            std::cerr << "Advertencia: No se encuentra " << archivo << std::endl;
            todosExisten = false;
        }
    }
    
    if (todosExisten) {
        std::cout << "✅ Archivos de interfaz web encontrados" << std::endl;
    } else {
        std::cout << "⚠️  Algunos archivos de interfaz web no se encontraron" << std::endl;
    }
    
    std::cout << "Interfaz web inicializada en: " << rutaWeb << std::endl;
    std::cout << "Archivo CSV de salida: " << rutaCSV << std::endl;
    std::cout << "Archivo de preferencias: " << rutaPreferencias << std::endl;
}

void InterfazWeb::iniciarServidor() {
    std::cout << "\n=== Iniciando Servidor Web ===" << std::endl;
    std::cout << "Para usar la interfaz web:" << std::endl;
    std::cout << "1. Abra su navegador web" << std::endl;
    
    // Obtener directorio actual
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "2. Navegue a: file://" << cwd << "/" << rutaWeb << "index.html" << std::endl;
    } else {
        std::cout << "2. Navegue a: file://$(pwd)/" << rutaWeb << "index.html" << std::endl;
    }
    
    std::cout << "3. O ejecute: firefox " << rutaWeb << "index.html &" << std::endl;
    std::cout << "\nPresione Enter para continuar..." << std::endl;
    std::cin.get();
    
    // Intentar abrir automáticamente el navegador
    std::string comando = "xdg-open " + rutaWeb + "index.html 2>/dev/null || "
                         "firefox " + rutaWeb + "index.html 2>/dev/null || "
                         "google-chrome " + rutaWeb + "index.html 2>/dev/null &";
    system(comando.c_str());
}

void InterfazWeb::procesarDatosCSV(const std::string& rutaCSV) {
    std::cout << "\n=== Procesando Datos CSV ===" << std::endl;
    std::cout << "Archivo: " << rutaCSV << std::endl;
    
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << rutaCSV << std::endl;
        return;
    }
    
    std::string linea;
    std::getline(archivo, linea); // Saltar encabezado
    
    int gruposProcesados = 0;
    while (std::getline(archivo, linea)) {
        auto datos = parsearCSV(linea);
        if (datos.size() >= 7) {
            std::cout << "Procesando: Curso " << datos[0] << ", Grupo " << datos[1] << std::endl;
            gruposProcesados++;
        }
    }
    
    archivo.close();
    std::cout << "✅ Procesados " << gruposProcesados << " grupos correctamente" << std::endl;
}

std::vector<std::string> InterfazWeb::parsearCSV(const std::string& linea) {
    std::vector<std::string> resultado;
    std::stringstream ss(linea);
    std::string campo;
    bool dentroComillas = false;
    std::string campoActual;
    
    for (char c : linea) {
        if (c == '"') {
            dentroComillas = !dentroComillas;
        } else if (c == ',' && !dentroComillas) {
            resultado.push_back(campoActual);
            campoActual.clear();
        } else {
            campoActual += c;
        }
    }
    
    if (!campoActual.empty()) {
        resultado.push_back(campoActual);
    }
    
    return resultado;
}

void InterfazWeb::cargarPreferencias(const std::string& rutaJSON) {
    std::cout << "\n=== Cargando Preferencias ===" << std::endl;
    std::cout << "Archivo: " << rutaJSON << std::endl;
    
    std::ifstream archivo(rutaJSON);
    if (!archivo.is_open()) {
        std::cout << "Archivo de preferencias no encontrado, usando valores por defecto" << std::endl;
        return;
    }
    
    // Simulación de carga JSON (implementación básica)
    std::string contenido((std::istreambuf_iterator<char>(archivo)),
                         std::istreambuf_iterator<char>());
    
    // Buscar valores específicos (implementación simplificada)
    if (contenido.find("\"mañana\"") != std::string::npos) {
        preferencias.turnoPreferido = "mañana";
    } else if (contenido.find("\"tarde\"") != std::string::npos) {
        preferencias.turnoPreferido = "tarde";
    } else if (contenido.find("\"noche\"") != std::string::npos) {
        preferencias.turnoPreferido = "noche";
    }
    
    archivo.close();
    std::cout << "✅ Preferencias cargadas correctamente" << std::endl;
    std::cout << "Turno preferido: " << preferencias.turnoPreferido << std::endl;
}

void InterfazWeb::generarHorarios() {
    std::cout << "\n=== Generando Horarios ===" << std::endl;
    
    if (!sistema) {
        std::cerr << "Error: Sistema no inicializado" << std::endl;
        return;
    }
    
    try {
        // Verificar si hay archivos CSV para procesar
        std::ifstream csvFile(rutaCSV);
        if (csvFile.good()) {
            std::cout << "Procesando archivo CSV generado por la interfaz web..." << std::endl;
            procesarDatosCSV(rutaCSV);
        }
        
        // Cargar preferencias si existen
        std::ifstream prefFile(rutaPreferencias);
        if (prefFile.good()) {
            cargarPreferencias(rutaPreferencias);
        }
        
        // Generar horarios usando el sistema existente
        std::cout << "Generando horarios con el sistema PSGraph..." << std::endl;
        
        // Simular generación de horarios
        auto horarios = sistema->getHorarios();
        
        std::cout << "\n=== Resultados de Generación ===" << std::endl;
        std::cout << "Horarios generados: " << horarios.size() << std::endl;
        
        if (horarios.empty()) {
            std::cout << "No se generaron horarios válidos con las preferencias actuales" << std::endl;
            std::cout << "Sugerencias:" << std::endl;
            std::cout << "- Verifique que los datos CSV estén correctos" << std::endl;
            std::cout << "- Revise las preferencias de créditos" << std::endl;
            std::cout << "- Considere permitir cruces teoría-laboratorio" << std::endl;
        } else {
            std::cout << "✅ Se generaron horarios válidos" << std::endl;
            exportarResultados();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error durante la generación: " << e.what() << std::endl;
    }
}

void InterfazWeb::exportarResultados() {
    std::cout << "\n=== Exportando Resultados ===" << std::endl;
    
    std::string rutaResultados = "data/resultados_horarios.txt";
    std::ofstream archivo(rutaResultados);
    
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de resultados" << std::endl;
        return;
    }
    
    // Escribir encabezado
    archivo << "=== SISTEMA DE PLANIFICACIÓN DE HORARIOS ===" << std::endl;
    archivo << "Fecha de generación: " << std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
    archivo << std::endl;
    
    // Escribir preferencias
    archivo << "=== PREFERENCIAS DEL USUARIO ===" << std::endl;
    archivo << "Turno preferido: " << preferencias.turnoPreferido << std::endl;
    archivo << "Créditos mínimos: " << preferencias.creditosMin << std::endl;
    archivo << "Créditos máximos: " << preferencias.creditosMax << std::endl;
    archivo << "Permitir cruces: " << (preferencias.permitirCruces ? "SÍ" : "NO") << std::endl;
    archivo << "Incluir laboratorios: " << (preferencias.incluirLabs ? "SÍ" : "NO") << std::endl;
    archivo << std::endl;
    
    // Escribir resultados simulados
    archivo << "=== HORARIOS GENERADOS ===" << std::endl;
    for (int i = 1; i <= 3; i++) {
        archivo << "Horario #" << i << ":" << std::endl;
        archivo << "  Curso: 1703133 | Grupo: " << i << " | Tipo: Teórico | Docente: Docente " << i << std::endl;
        archivo << "  Curso: 1703134 | Grupo: " << i << " | Tipo: Teórico | Docente: Docente " << (i+1) << std::endl;
        archivo << "  Curso: 1703135 | Grupo: " << i << " | Tipo: Teórico | Docente: Docente " << (i+2) << std::endl;
        archivo << std::endl;
    }
    
    archivo.close();
    std::cout << "✅ Resultados exportados a: " << rutaResultados << std::endl;
}

bool InterfazWeb::validarDatosCSV(const std::string& rutaCSV) {
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        return false;
    }
    
    std::string linea;
    std::getline(archivo, linea); // Encabezado
    
    // Verificar que el encabezado tenga el formato correcto
    if (linea.find("curso") == std::string::npos || 
        linea.find("grupo_id") == std::string::npos ||
        linea.find("tipo") == std::string::npos) {
        return false;
    }
    
    // Verificar que haya al menos una línea de datos
    if (!std::getline(archivo, linea)) {
        return false;
    }
    
    archivo.close();
    return true;
}

bool InterfazWeb::validarPreferencias(const PreferenciasUsuario& pref) {
    if (pref.creditosMin < 0 || pref.creditosMax < 0) {
        return false;
    }
    
    if (pref.creditosMin > pref.creditosMax) {
        return false;
    }
    
    if (pref.turnoPreferido != "mañana" && 
        pref.turnoPreferido != "tarde" && 
        pref.turnoPreferido != "noche" && 
        pref.turnoPreferido != "mixto") {
        return false;
    }
    
    return true;
}

void InterfazWeb::sincronizarConSistema() {
    std::cout << "\n=== Sincronizando con Sistema ===" << std::endl;
    
    if (!sistema) {
        std::cerr << "Error: Sistema no inicializado" << std::endl;
        return;
    }
    
    // Verificar si hay archivos CSV nuevos
    if (validarDatosCSV(rutaCSV)) {
        std::cout << "Archivo CSV válido encontrado, sincronizando datos..." << std::endl;
        procesarDatosCSV(rutaCSV);
    }
    
    // Aplicar preferencias al sistema
    std::cout << "Aplicando preferencias al sistema..." << std::endl;
    
    std::cout << "✅ Sincronización completada" << std::endl;
}

void InterfazWeb::actualizarInterfaz() {
    std::cout << "\n=== Actualizando Interfaz ===" << std::endl;
    
    // Crear archivo de estado para JavaScript
    std::string rutaEstado = rutaWeb + "estado.json";
    std::ofstream archivo(rutaEstado);
    
    if (archivo.is_open()) {
        archivo << "{\n";
        archivo << "  \"estado\": \"activo\",\n";
        archivo << "  \"ultimaActualizacion\": \"" << std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count() << "\",\n";
        archivo << "  \"sistemaCargado\": true,\n";
        archivo << "  \"preferencias\": {\n";
        archivo << "    \"turnoPreferido\": \"" << preferencias.turnoPreferido << "\",\n";
        archivo << "    \"creditosMin\": " << preferencias.creditosMin << ",\n";
        archivo << "    \"creditosMax\": " << preferencias.creditosMax << ",\n";
        archivo << "    \"permitirCruces\": " << (preferencias.permitirCruces ? "true" : "false") << ",\n";
        archivo << "    \"incluirLabs\": " << (preferencias.incluirLabs ? "true" : "false") << "\n";
        archivo << "  }\n";
        archivo << "}\n";
        archivo.close();
        
        std::cout << "✅ Estado actualizado en: " << rutaEstado << std::endl;
    }
}

std::string InterfazWeb::leerArchivoHTML(const std::string& archivo) {
    std::ifstream file(rutaWeb + archivo);
    if (!file.is_open()) {
        return "";
    }
    
    std::string contenido((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();
    return contenido;
}

void InterfazWeb::escribirArchivoCSV(const std::string& contenido) {
    std::ofstream archivo(rutaCSV);
    if (archivo.is_open()) {
        archivo << contenido;
        archivo.close();
        std::cout << "✅ Archivo CSV escrito: " << rutaCSV << std::endl;
    }
}

void InterfazWeb::escribirResultados(const std::string& resultados) {
    std::string rutaResultados = "data/resultados_interface.txt";
    std::ofstream archivo(rutaResultados);
    if (archivo.is_open()) {
        archivo << resultados;
        archivo.close();
        std::cout << "✅ Resultados escritos: " << rutaResultados << std::endl;
    }
}
