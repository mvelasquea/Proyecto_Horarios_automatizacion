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

    void backtrackingHorarios(std::vector<Grupo*>& seleccionados, size_t index);
public:
    Sistema();
    //generacion de horarios
    const std::vector<Horario>& getHorarios() const { return horarios; }

    // Carga cursos desde CSV
    void cargarCursos(const std::string& rutaCSV);
    void cargarGrupos(const std::string& rutaCSV);
    Hora parsearHora(const std::string& strHora, const std::string& aula);
    void cargarGrafo();

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
    void generarHorarios();
    void verHorarios() const;
    void crearRegistro() const;
};
