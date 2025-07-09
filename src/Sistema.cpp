#include "Sistema.hpp"
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>

// Constructor
Sistema::Sistema() {}

void Sistema::cargarGrafo() {
    // Reiniciar grafo (no dirigido)
    grafoGrupos = Grafo<Grupo*>(false);

    // Recorrer todos los cursos cargados
    for (auto& [codigo, curso] : cursos) {
        const auto& grupos = curso.getGrupos();

        // Insertar cada grupo en el grafo
        for (const Grupo& grupo : grupos) {
            Grupo* ptrGrupo = const_cast<Grupo*>(&grupo);

            grafoGrupos.insertarVertice(ptrGrupo);

            // Verificar compatibilidad con los grupos ya insertados
            for (Grupo* nodoExistente : grafoGrupos.obtenerVertices()) {
                if (nodoExistente == ptrGrupo) continue;

                if (sonCompatibles(nodoExistente, ptrGrupo)) {
                    grafoGrupos.insertarArista(Arista<Grupo*>(nodoExistente, ptrGrupo, false));
                }
            }
        }
    }
}

void Sistema::imprimirGrafo() const {
    std::cout << "=== Grafo de Grupos y sus vecinos compatibles ===\n";
    std::cout << "Total de nodos (grupos): " << grafoGrupos.obtenerVertices().size() << "\n";
    for (auto v : grafoGrupos.obtenerVertices()) {
        std::cout << "Grupo: " << v->getIdGrupo()
                  << " | Curso: " << v->getCurso()->getCodigo() << "\nVecinos: ";

        std::set<std::string> vecinosUnicos;
        for (auto vecino : grafoGrupos.obtenerVecinos(v)) {
            std::string idUnico = vecino->getCurso()->getCodigo() + ":" + vecino->getIdGrupo();
            vecinosUnicos.insert(idUnico);
        }

        for (const auto& vecinoId : vecinosUnicos) {
            std::cout << vecinoId << " ";
        }
        std::cout << "\n\n";
    }
}

void Sistema::imprimirDFS(Grupo* v, std::map<Grupo*, bool>& visitados) const {
    visitados[v] = true;
    std::cout << "Grupo: " << v->getIdGrupo()
              << " | Curso: " << v->getCurso()->getCodigo() << "\nVecinos: ";

    for (auto vecino : grafoGrupos.obtenerVecinos(v)) {
        std::cout << vecino->getIdGrupo() << " ";
    }
    std::cout << "\n\n";

    for (auto vecino : grafoGrupos.obtenerVecinos(v)) {
        if (!visitados[vecino]) {
            imprimirDFS(vecino, visitados);
        }
    }
}

void Sistema::imprimirGrafoDFS() const {
    std::map<Grupo*, bool> visitados;
    for (auto v : grafoGrupos.obtenerVertices()) {
        visitados[v] = false;
    }

    std::cout << "=== Recorrido DFS Completo del Grafo ===\n";
    for (auto v : grafoGrupos.obtenerVertices()) {
        if (!visitados[v]) {
            imprimirDFS(v, visitados);
        }
    }
}

void Sistema::imprimirCursos() const {
    std::cout << "\n===== Cursos Cargados =====\n";
    for (const auto& [codigo, curso] : cursos) {
        std::cout << "Curso [" << codigo << "]: " << curso.getNombre()
                  << " | Tipo: " << curso.getTipo()
                  << " | Créditos: " << curso.getCreditos()
                  << " | Ciclo: " << curso.getCiclo()
                  << " | Horas Teóricas: " << curso.getHorasTeoricas()
                  << " | Horas Prácticas: " << curso.getHorasPracticas()
                  << " | Horas Laboratorio: " << curso.getHorasLaboratorio();
        
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
            
            // Leer todos los campos de la línea
            while (std::getline(ss, campo, ',')) {
                campos.push_back(campo);
            }

            // Verificar que tenga al menos 10 campos (los 7 básicos + 3 de horas)
            if (campos.size() < 10) {
                std::cerr << "Línea incompleta: " << linea << std::endl;
                continue;
            }

            // Parsear datos básicos
            std::string codigo = campos[0];
            std::string tipo = campos[1];
            std::string nombre = campos[2];
            int creditos = std::stoi(campos[3]);
            int ciclo = campos[4].empty() ? 0 : std::stoi(campos[4]);
            std::string prq1 = campos[5];
            std::string prq2 = campos[6];
            
            // Parsear horas (campos 7, 8, 9)
            int horasTeo = campos[7].empty() ? 0 : std::stoi(campos[7]);
            int horasPrac = campos[8].empty() ? 0 : std::stoi(campos[8]);
            int horasLab = campos[9].empty() ? 0 : std::stoi(campos[9]);

            // Crear curso con todos los datos
            Curso curso(codigo, tipo, nombre, creditos, ciclo, prq1, prq2, 
                      horasTeo, horasPrac, horasLab);
            
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

bool Sistema::sonCompatibles(const Grupo* g1, const Grupo* g2) const {
    // Mismo curso: solo permitir teoría + lab
    if (g1->getCurso() == g2->getCurso()) {
        return g1->esLab() != g2->esLab();
    }

    // Verificar choque de horarios
    for (const Hora& h1 : g1->getHoras()) {
        for (const Hora& h2 : g2->getHoras()) {
            if (h1.seCruzaCon(h2)) {
                return false;
            }
        }
    }
    return true;
}

void Sistema::generarHorarios() {
    // 1. Selecciona solo cursos con grupos
    vector<Curso*> cursosASeleccionar;
    for (auto& [codigo, curso] : cursos)
        if (curso.getGrupos().size() > 0)
            cursosASeleccionar.push_back(&curso);

    vector<Grupo*> seleccionados;

    // 2. Función recursiva (backtracking usando el grafo)
    function<void(int)> backtrack = [&](int idx) {
        if (idx == cursosASeleccionar.size()) {
            horarios.emplace_back(seleccionados);
            return;
        }
        Curso* curso = cursosASeleccionar[idx];

        // Probar todos los grupos teóricos
        for (Grupo* teorico : curso->getGruposTeoricos()) {
            bool ok = true;
            for (Grupo* g : seleccionados) {
                // Usar el grafo: debe haber arista (compatibilidad)
                if (!grafoGrupos.contieneArista(Arista<Grupo*>(g, teorico, false))) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            // Si hay laboratorio, igual pero usando grafo también
            if (curso->tieneLaboratorio()) {
                for (Grupo* lab : curso->getGruposLaboratorio()) {
                    ok = true;
                    for (Grupo* g : seleccionados) {
                        if (!grafoGrupos.contieneArista(Arista<Grupo*>(g, lab, false))) {
                            ok = false;
                            break;
                        }
                    }
                    // Verificar que teoría y lab también sean vecinos en grafo
                    if (!grafoGrupos.contieneArista(Arista<Grupo*>(teorico, lab, false))) ok = false;
                    if (!ok) continue;

                    seleccionados.push_back(teorico);
                    seleccionados.push_back(lab);
                    backtrack(idx + 1);
                    seleccionados.pop_back();
                    seleccionados.pop_back();
                }
            } else {
                seleccionados.push_back(teorico);
                backtrack(idx + 1);
                seleccionados.pop_back();
            }
        }
    };

    // 3. Llama la recursión inicial
    backtrack(0);
}

void Sistema::verHorarios() const {
    std::cout << "\n======= Horarios Generados =======\n";
    if (horarios.empty()) {
        std::cout << "No se han generado horarios.\n";
        return;
    }
    int num = 1;
    for (const Horario& horario : horarios) {
        std::cout << "Horario #" << num++ << ":\n";
        for (Grupo* grupo : horario.getGrupos()) {
            std::cout << "  Curso: " << grupo->getCurso()->getCodigo()
                      << " | Nombre: " << grupo->getCurso()->getNombre()
                      << " | Grupo: " << grupo->getIdGrupo()
                      << " | Tipo: " << (grupo->esLab() ? "Lab" : "Teorico")
                      << " | Docente: " << grupo->getDocente()
                      << "\n";
        }
        std::cout << "----------------------------\n";
    }
}

void Sistema::crearRegistro() const {
    std::ofstream fout("../data/output/horarios.csv");
    if (!fout.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir: ./data/output/horarios.csv\n";
        return;
    }

    fout << "horainicio,horafin,dia,curso,grupo,tipo,codigo,profesor,codigo_horario\n";

    // Días de la semana
    const std::string diasSemana[] = {"", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};

    int codigo_horario = 1;
    for (const auto& horario : horarios) {
        for (Grupo* grupo : horario.getGrupos()) {
            for (const Hora& hora : grupo->getHoras()) {
                auto minutosAString = [](int m) {
                    std::ostringstream oss;
                    oss << std::setw(2) << std::setfill('0') << (m/60)
                        << ":" << std::setw(2) << std::setfill('0') << (m%60);
                    return oss.str();
                };

                fout
                    << minutosAString(hora.getInicio()) << ","
                    << minutosAString(hora.getFin()) << ","
                    << diasSemana[hora.getDia()] << ","
                    << grupo->getCurso()->getNombreAbreviado() << ","
                    << grupo->getIdGrupo() << ","
                    << (grupo->esLab() ? "Lab" : "Teo") << ","
                    << grupo->getCurso()->getCodigo() << ","
                    << grupo->getDocente() << ","
                    << codigo_horario << "\n";
            }
        }
        ++codigo_horario;
    }

    fout.close();
    std::cout << "Archivo generado correctamente: ./data/output/horarios.csv" << std::endl;
}