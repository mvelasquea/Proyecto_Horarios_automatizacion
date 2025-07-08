#pragma once
#include <string>
#include <vector>
#include "Hora.hpp"
#include "Curso.hpp"

using namespace std;

class Grupo {
private:
    Curso* curso;
    string grupo_id;      // ID del grupo
    bool tipo;            // false = Teórico, true = Laboratorio
    vector<Hora> horas;
    string docente;
    int cupos;

public:
    Grupo(string id, bool esLab, const string& doc, int vac)
        : grupo_id(id), tipo(esLab), docente(doc), cupos(vac) {}

    // Getters
    string getIdGrupo() const { return grupo_id; }
    bool getTipo() const { return tipo; }
    bool esLab() const { return tipo; }
    string getDocente() const { return docente; }
    int getVacantes() const { return cupos; }
    const vector<Hora>& getHoras() const { return horas; }

    // Métodos
    void agregarHora(const Hora& h) {
        horas.push_back(h);
    }

    void setCurso(Curso* c) {
        curso = c;
    }

    Curso* getCurso() const {
        return curso;
    }
};
