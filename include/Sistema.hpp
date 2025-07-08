#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Curso.hpp"
#include "Grupo.hpp"
#include "PSGraph/Grafo.hpp"
#include "Hora.hpp"
#include "Horario.hpp"

class Sistema {
private:
    bool incluirLabs;
    std::unordered_map<std::string, Curso> cursos; // curso_codigo -> Curso
    Grafo<Grupo*> grafoGrupos; 
    std::vector<Horario> horarios;
    std::vector<Grupo*> gruposParaBacktracking;

    void backtrackingHorarios(std::vector<Grupo*>& seleccionados, size_t index);
public:
    Sistema();
    //generacion de horarios
    void backtrackingHorarios(vector<Grupo*>& seleccionados, size_t index,
                                 unordered_map<string, bool>& cursoConTeorico,
                                 unordered_map<string, bool>& cursoConLab);
    void prepararGruposParaBacktracking();
    const std::vector<Horario>& getHorarios() const { return horarios; }
    void generarHorarios(bool incluirLaboratorios);

    // Carga cursos desde CSV
    void cargarCursos(const std::string& rutaCSV);
    void cargarGrupos(const std::string& rutaCSV);
    Hora parsearHora(const std::string& strHora, const std::string& aula);
    void cargarGrafo();
    void verificarDatosCargados() const;

    // Acceso
    Curso* obtenerCurso(const std::string& codigo);
    const std::unordered_map<std::string, Curso>& getCursos() const { return cursos; }

    // Extra
    bool sonCompatibles(const Grupo* g1, const Grupo* g2) const;
    string limpiarCampo(const std::string& campo);
    void imprimirCursos() const;
    void imprimirGrupos() const;
    void imprimirGrafo() const;
    void imprimirDFS(Grupo* v, std::map<Grupo*, bool>& visitados) const;
    void imprimirGrafoDFS() const;
    void verHorarios() const;
};
