#include "Sistema.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor
Sistema::Sistema() {}

void Sistema::imprimirCursos() const {
    std::cout << "\n===== Cursos Cargados =====\n";
    for (const auto& [codigo, curso] : cursos) {
        std::cout << "Curso [" << codigo << "]: " << curso.getNombre()
                  << " | Tipo: " << curso.getTipo()
                  << " | Créditos: " << curso.getCreditos()
                  << " | Ciclo: " << curso.getCiclo();
        if (!curso.getPrerequisito1().empty())
            std::cout << " | PRQ1: " << curso.getPrerequisito1();
        if (!curso.getPrerequisito2().empty())
            std::cout << " | PRQ2: " << curso.getPrerequisito2();
        std::cout << std::endl;
    }
    std::cout << "===== Fin de impresión =====\n";
}

void Sistema::cargarCursos(const std::string& rutaCSV) {
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir archivo: " << rutaCSV << std::endl;
        return;
    }

    std::string linea;
    // Leer cabecera
    if (!std::getline(archivo, linea)) {
        std::cerr << "Archivo CSV vacío o mal formateado.\n";
        return;
    }

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        try {
            std::stringstream ss(linea);
            std::vector<std::string> campos;
            std::string campo;
            while (std::getline(ss, campo, ',')) campos.push_back(campo);

            // Se espera al menos 9 campos por línea
            if (campos.size() < 9) {
                std::cerr << "Línea incompleta: " << linea << std::endl;
                continue;
            }

            std::string codigo = campos[0];
            std::string tipo = campos[1];
            std::string nombre = campos[2];
            int creditos = std::stoi(campos[3]);
            int ciclo = campos[4].empty() ? 0 : std::stoi(campos[4]);
            std::string prq1 = campos[5];
            std::string prq2 = campos[6];

            // Crear y agregar el curso
            Curso curso(codigo, tipo, nombre, creditos, ciclo, prq1, prq2);
            cursos.emplace(codigo, std::move(curso));
        }
        catch (const std::exception& e) {
            std::cerr << "Error procesando línea: " << linea << "\nMotivo: " << e.what() << std::endl;
            continue;
        }
    }
}

void Sistema::imprimirGrupos() const {
    for (const auto& [codigo, curso] : cursos) {
        std::cout << "Curso: " << codigo << " - " << curso.getNombre() << "\n";
        const auto& grupos = curso.getGrupos();
        if (grupos.empty()) {
            std::cout << "  No tiene grupos cargados.\n";
            continue;
        }
        for (const auto& grupo : grupos) {
            std::cout << "  Grupo ID: " << grupo.getIdGrupo()
                      << ", Tipo: " << (grupo.esLab() ? "Lab" : "Teórico")
                      << ", Docente: " << grupo.getDocente()
                      << ", Cupos: " << grupo.getVacantes()
                      << ", Horas: ";
            for (const auto& hora : grupo.getHoras()) {
                std::cout << hora.getDia() << "_"
                          << hora.getInicio() / 60 << ":"
                          << (hora.getInicio() % 60 < 10 ? "0" : "") << hora.getInicio() % 60
                          << "-"
                          << hora.getFin() / 60 << ":"
                          << (hora.getFin() % 60 < 10 ? "0" : "") << hora.getFin() % 60 << " ";
            }
            std::cout << "\n";
        }
        std::cout << "----------------------------------\n";
    }
}


void Sistema::cargarGrupos(const std::string& rutaCSV) {
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir archivo: " << rutaCSV << std::endl;
        return;
    }

    std::string linea;
    // Leer cabecera
    if (!std::getline(archivo, linea)) {
        std::cerr << "Archivo CSV vacío o mal formateado.\n";
        return;
    }

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#') continue;  // ignorar líneas vacías o comentarios

        try {
            std::stringstream ss(linea);
            std::vector<std::string> campos;
            std::string campo;
            while (std::getline(ss, campo, ',')) campos.push_back(limpiarCampo(campo));

            if (campos.size() < 7) {
                std::cerr << "Línea incompleta: " << linea << std::endl;
                continue;
            }

            std::string codigoCurso = campos[0];
            std::string grupo_id = campos[1];
            std::string tipoStr = campos[2];
            char tipoChar = tipoStr.empty() ? 'F' : tipoStr[0];  // 'F' o 'L'
            std::string aula = campos[3];
            std::string horasStr = campos[4];
            std::string docente = campos[5];
            int cupos = std::stoi(campos[6]);

            auto it = cursos.find(codigoCurso);
            if (it == cursos.end()) {
                std::cerr << "Curso no encontrado para grupo: " << codigoCurso << std::endl;
                continue;
            }

            Curso& curso = it->second;
            bool esLab = (tipoChar == 'L' || tipoChar == 'l');
            Grupo grupo(grupo_id, esLab, docente, cupos);

            // Parsear horas
            std::stringstream hs(horasStr);
            std::string token;
            while (hs >> token) {
                // token ejemplo: "1_08:00-09:40"
                Hora h = parsearHora(token, aula); // parsearHora debe estar implementada
                grupo.agregarHora(h);
            }

            grupo.setCurso(&curso);
            curso.agregarGrupo(grupo);
        }
        catch (const std::exception& e) {
            std::cerr << "Error procesando línea: " << linea << "\nMotivo: " << e.what() << std::endl;
            continue;
        }
    }
}

Hora Sistema::parsearHora(const std::string& strHora, const std::string& aula) {
    // Ejemplo strHora: "1_08:00-09:40"
    int dia = std::stoi(strHora.substr(0, 1));

    size_t posGuion = strHora.find('-');
    size_t posUnderscore = strHora.find('_');

    std::string inicioStr = strHora.substr(posUnderscore + 1, posGuion - posUnderscore - 1);
    std::string finStr = strHora.substr(posGuion + 1);

    auto toMinutos = [](const std::string& t) {
        int h = std::stoi(t.substr(0, 2));
        int m = std::stoi(t.substr(3, 2));
        return h * 60 + m;
    };

    int hi = toMinutos(inicioStr);
    int hf = toMinutos(finStr);

    return Hora(dia, hi, hf, aula);
}

Curso* Sistema::obtenerCurso(const std::string& codigo) {
    auto it = cursos.find(codigo);
    return it == cursos.end() ? nullptr : &it->second;
}

std::string Sistema::limpiarCampo(const std::string& campo) {
    std::string res = campo;
    // Quitar espacios al inicio y fin
    while (!res.empty() && isspace(res.front())) res.erase(res.begin());
    while (!res.empty() && isspace(res.back())) res.pop_back();
    // Quitar comillas si existen
    if (!res.empty() && res.front() == '"') res.erase(res.begin());
    if (!res.empty() && res.back() == '"') res.pop_back();
    return res;
}


bool sonCompatibles(const Grupo& g1, const Grupo& g2) {
    // Restricción 1: No seleccionar más de un grupo del mismo curso,
    // excepto si uno es laboratorio y el otro teoría.
    if (g1.getCurso()->getCodigo() == g2.getCurso()->getCodigo()) {
        if (g1.esLab() != g2.esLab()) {
            return true;  // compatible: teoría + laboratorio del mismo curso
        } else {
            return false; // dos grupos del mismo tipo y mismo curso no son compatibles
        }
    }

    // Restricción 2: Evitar choque de horarios salvo teoría-laboratorio.
    for (const Hora& h1 : g1.getHoras()) {
        for (const Hora& h2 : g2.getHoras()) {
            if (h1.seCruzaCon(h2)) {
                // Si son diferentes tipos (teoría-laboratorio), se permite cruzar
                if (g1.esLab() != g2.esLab()) {
                    continue; // seguir verificando otras horas
                } else {
                    return false; // choque horario no permitido entre mismos tipos
                }
            }
        }
    }

    // Si pasó todas las pruebas, son compatibles
    return true;
}
