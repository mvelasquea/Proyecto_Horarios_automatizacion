#include "Sistema.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

// Constructor
Sistema::Sistema() : grafoGrupos(false) {} // false = no dirigido

void Sistema::imprimirDatos() const {
    std::cout << "\n===== Cursos y Grupos Cargados =====\n";
    for (const auto& [codigo, curso] : cursos) {
        std::cout << "Curso [" << codigo << "]: " << curso.getNombre()
                  << " | Créditos: " << curso.getCreditos()
                  << " | Ciclo: " << curso.getCiclo() << '\n';

        // Mostrar prerrequisitos
        if (!curso.getPrerequisitos().empty()) {
            std::cout << "  Prerrequisitos: ";
            for (const auto& pr : curso.getPrerequisitos())
                std::cout << pr << " ";
            std::cout << '\n';
        }

        // Mostrar grupos
        for (const auto& grupo : curso.getGrupos()) {
            std::cout << "  Grupo " << grupo.getIdGrupo()
                      << " | " << (grupo.esLab() ? "LAB" : "TEO")
                      << " | Docente: " << grupo.getDocente()
                      << " | Vacantes: " << grupo.getVacantes()
                      << " | Aula: " << grupo.getAula()
                      << " | Cupo docente: " << grupo.getCupoDocente()
                      << "\n    Horarios: ";

            for (const auto& hora : grupo.getHoras()) {
                std::cout << "[Día " << (hora.getDia()+1)
                          << ": " << std::setw(2) << std::setfill('0')
                          << (hora.getInicio()/60) << ":" << std::setw(2) << (hora.getInicio()%60)
                          << "-" << std::setw(2) << (hora.getFin()/60) << ":" << std::setw(2) << (hora.getFin()%60)
                          << " (" << hora.getAula() << ", " << hora.getTipo() << ")] ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    std::cout << "===== Fin de impresión =====\n";
}

bool Sistema::cargarDatos(const std::string& rutaCSV) {
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir archivo: " << rutaCSV << std::endl;
        return false;
    }

    std::string linea;
    // Leer cabecera
    if (!std::getline(archivo, linea)) {
        std::cerr << "Archivo CSV vacío o mal formateado." << std::endl;
        return false;
    }

    std::vector<Grupo*> todosLosGrupos;

    // Helpers robustos
    auto safeStr   = [](const std::string& s) { return (s.empty() || s == "\"\"") ? "NULL" : s; };
    auto safeInt   = [](const std::string& s) -> int {
        try { return (s.empty() || s == "\"\"") ? 0 : std::stoi(s); }
        catch (...) { return 0; }
    };
    auto safeBool  = [](const std::string& s) { return (!s.empty() && s == "1"); };

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        try {
            std::stringstream ss(linea);
            std::vector<std::string> campos;
            std::string campo;
            while (std::getline(ss, campo, ',')) campos.push_back(campo);

            // Si la línea tiene menos de 12 columnas, reporta y salta
            if (campos.size() < 12) {
                std::cerr << "Campo vacío en línea: " << linea << std::endl;
                continue;
            }

            // Parseo seguro
            const std::string codigo     = safeStr(campos[0]);
            const std::string nombre     = safeStr(campos[1]);
            int creditos                = safeInt(campos[2]);
            int ciclo                   = safeInt(campos[3]);
            const std::string prereqsStr = safeStr(campos[4]);
            const std::string grupoId    = safeStr(campos[5]);
            bool esLab                   = safeBool(campos[6]);
            const std::string docente    = safeStr(campos[7]);
            int vacantes                 = safeInt(campos[8]);
            const std::string aula       = safeStr(campos[9]);
            const std::string diasHoras  = safeStr(campos[10]);
            int cupoDocente              = safeInt(campos[11]);

            // Crear o recuperar Curso
            if (cursos.find(codigo) == cursos.end()) {
                Curso curso(codigo, nombre, creditos, ciclo);
                if (prereqsStr != "NULL") {
                    std::stringstream ps(prereqsStr);
                    std::string p;
                    while (std::getline(ps, p, ';'))
                        if (!p.empty()) curso.agregarPrerequisito(p);
                }
                cursos.emplace(codigo, std::move(curso));
            }
            Curso& curso = cursos.at(codigo);

            // Crear Grupo y parsear horas
            Grupo grupo(grupoId, esLab, docente, vacantes, aula, cupoDocente);

            std::stringstream dhs(diasHoras);
            while (std::getline(dhs, campo, ';')) {
                auto posU = campo.find('_');
                if (posU == std::string::npos) continue;
                int dia = safeInt(campo.substr(0, posU)) - 1;
                auto intervalo = campo.substr(posU + 1);
                auto posD = intervalo.find('-');
                if (posD == std::string::npos) continue;
                std::string hi_s = intervalo.substr(0, posD);
                std::string hf_s = intervalo.substr(posD + 1);
                int hi = safeInt(hi_s.substr(0,2)) * 60 + safeInt(hi_s.substr(3,2));
                int hf = safeInt(hf_s.substr(0,2)) * 60 + safeInt(hf_s.substr(3,2));
                grupo.agregarHora(Hora(dia, hi, hf, aula, esLab ? "LAB" : "TEO"));
            }

            // Agregar al Curso y obtener puntero
            curso.agregarGrupo(grupo);
            auto& vec = const_cast<std::vector<Grupo>&>(curso.getGrupos());
            Grupo* ptr = &vec.back();
            todosLosGrupos.push_back(ptr);

            // Insertar vértice en el grafo
            grafoGrupos.insertarVertice(ptr);

        } catch (const std::exception& e) {
            std::cerr << "Error al procesar línea: " << linea << "\nMotivo: " << e.what() << std::endl;
            continue;
        }
    }

    // Construir aristas de incompatibilidad
    for (size_t i = 0; i < todosLosGrupos.size(); ++i) {
        for (size_t j = i + 1; j < todosLosGrupos.size(); ++j) {
            if (sonIncompatibles(todosLosGrupos[i], todosLosGrupos[j])) {
                grafoGrupos.insertarArista(Arista<Grupo*>(todosLosGrupos[i], todosLosGrupos[j]));
            }
        }
    }

    return true;
}

// --------- Restricciones ---------
bool Sistema::sonIncompatibles(Grupo* g1, Grupo* g2) {
    if (!g1 || !g2) return true;

    auto pref = [](const std::string& id) {
        auto pos = id.find('-');
        return pos == std::string::npos ? id : id.substr(0, pos);
    };
    const auto c1 = pref(g1->getIdGrupo());
    const auto c2 = pref(g2->getIdGrupo());

    // 1. Mismo curso (teoría-laboratorio son compatibles)
    if (c1 == c2) {
        if (g1->esLab() != g2->esLab()) return false;
        return true;
    }

    // 2. Choque de horario o aula
    for (auto& h1 : g1->getHoras()) {
        for (auto& h2 : g2->getHoras()) {
            if (h1.getDia() == h2.getDia()) {
                bool overlap = !(h1.getFin() <= h2.getInicio() ||
                                 h1.getInicio() >= h2.getFin());
                if (overlap) return true; // choque de horario
                if (overlap && h1.getAula() == h2.getAula()) return true; // y aula
            }
        }
    }

    // 3. Docente sobrecargado
    if (g1->getDocente() == g2->getDocente()) {
        int totalVac = g1->getVacantes() + g2->getVacantes();
        int cupo = g1->getCupoDocente();
        if (totalVac > cupo) return true;
    }

    return false;
}

// ---- Métodos de acceso ----
Curso* Sistema::obtenerCurso(const std::string& codigo) {
    auto it = cursos.find(codigo);
    return it == cursos.end() ? nullptr : &it->second;
}

Grupo* Sistema::obtenerGrupo(const std::string& idGrupo) {
    for (auto& kv : cursos) {
        for (auto& g : kv.second.getGrupos())
            if (g.getIdGrupo() == idGrupo)
                return const_cast<Grupo*>(&g);
    }
    return nullptr;
}

std::vector<Grupo*> Sistema::obtenerGruposDeCurso(const std::string& codigo) {
    std::vector<Grupo*> res;
    if (auto* c = obtenerCurso(codigo)) {
        for (auto& g : c->getGrupos())
            res.push_back(const_cast<Grupo*>(&g));
    }
    return res;
}
