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

Curso* Sistema::obtenerCurso(const std::string& codigo) {
    auto it = cursos.find(codigo);
    return it == cursos.end() ? nullptr : &it->second;
}
