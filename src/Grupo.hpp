#pragma once
#include <string>
#include <vector>
#include "Horario.hpp"

using namespace std;

class Grupo {
private:
    string idGrupo;
    vector<Horario> horarios;
    string docente;
    int vacantes;
    bool disponible;
    bool esLaboratorio;
    string vinculadoA;  // ID del grupo TEO asociado, si es LAB

public:
    Grupo(string id, string doc, int vac, bool dispo, bool esLab, string vinc = "")
        : idGrupo(id), docente(doc), vacantes(vac), disponible(dispo), esLaboratorio(esLab), vinculadoA(vinc) {}

    string getIdGrupo() const { return idGrupo; }
    string getDocente() const { return docente; }
    int getVacantes() const { return vacantes; }
    bool estaDisponible() const { return disponible; }
    bool esLab() const { return esLaboratorio; }
    string getGrupoVinculado() const { return vinculadoA; }
    const vector<Horario>& getHorarios() const { return horarios; }

    void agregarHorario(const Horario& h) {
        horarios.push_back(h);
    }
};
