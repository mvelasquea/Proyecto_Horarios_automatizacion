#pragma once
#include <string>
#include <vector>
#include "Hora.hpp"

using namespace std;

class Grupo {
private:
    string idGrupo;
    bool esLaboratorio;         // false = TEO, true = LAB
    vector<Hora> horas;
    string docente;
    int vacantes;
    string aula;
    int cupoDocente;

public:
    Grupo(string id, bool esLab, const string& doc, int vac, const string& aula_, int cupo)
        : idGrupo(id), esLaboratorio(esLab), docente(doc), vacantes(vac), aula(aula_), cupoDocente(cupo) {}

    string getIdGrupo() const { return idGrupo; }
    bool getTipo() const { return esLaboratorio; }
    bool esLab() const { return esLaboratorio; }
    string getDocente() const { return docente; }
    int getVacantes() const { return vacantes; }
    string getAula() const { return aula; }
    int getCupoDocente() const { return cupoDocente; }
    const vector<Hora>& getHoras() const { return horas; }

    void agregarHora(const Hora& h) {
        horas.push_back(h);
    }
};
