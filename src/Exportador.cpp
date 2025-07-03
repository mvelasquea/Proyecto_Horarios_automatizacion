#include "Exportador.h"
#include <fstream>

void Exportador::exportarCSV(const std::vector<Curso>& cursos, const std::string& ruta) {
    std::ofstream archivo(ruta);
    archivo << "Codigo,Nombre,Creditos,Grupo,Dia,Franja,Tipo\n";
    for (const auto& curso : cursos) {
        for (const auto& h : curso.obtenerHorarios()) {
            archivo << curso.obtenerCodigo() << ","
                    << curso.obtenerNombre() << ","
                    << curso.obtenerCreditos() << ","
                    << curso.obtenerGrupo() << ","
                    << h.dia << ","
                    << h.franja << ","
                    << h.tipo << "\n";
        }
    }
    archivo.close();
}
void Exportador::exportarJSON(const std::vector<Curso>& cursos, const std::string& ruta) {
    std::ofstream archivo(ruta);
    archivo << "[\n";
    for (size_t i = 0; i < cursos.size(); ++i) {
        const auto& curso = cursos[i];
        archivo << "  {\n"
                << "    \"codigo\": \"" << curso.obtenerCodigo() << "\",\n"
                << "    \"nombre\": \"" << curso.obtenerNombre() << "\",\n"
                << "    \"creditos\": " << curso.obtenerCreditos() << ",\n"
                << "    \"grupo\": \"" << curso.obtenerGrupo() << "\",\n"
                << "    \"horarios\": [\n";
        for (size_t j = 0; j < curso.obtenerHorarios().size(); ++j) {
            const auto& h = curso.obtenerHorarios()[j];
            archivo << "      {\n"
                    << "        \"dia\": \"" << h.dia << "\",\n"
                    << "        \"franja\": \"" << h.franja << "\",\n"
                    << "        \"tipo\": \"" << h.tipo << "\"\n"
                    << "      }" 
                    << (j < curso.obtenerHorarios().size() - 1 ? "," : "") 
                    << "\n";
        }
        archivo << "    ]\n"
                << "  }" 
                << (i < cursos.size() - 1 ? "," : "") 
                << "\n";
    }
    archivo << "]\n";
    archivo.close();
}