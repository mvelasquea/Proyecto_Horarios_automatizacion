#pragma once
#include <string>
#include <vector>
#include "Grupo.hpp"

using namespace std;

class Curso {
private:
    string codigo;
    string nombre;
    int creditos;
    string tipo; // "TEO", "LAB", "MIXTO"
    int ciclo;
    vector<string> prerequisitos;
    bool esElectivo;
    string area;
    vector<Grupo> grupos;

public:
    Curso(string cod, string nom, int cred, string t, int c, bool elect, string ar)
        : codigo(cod), nombre(nom), creditos(cred), tipo(t), ciclo(c), esElectivo(elect), area(ar) {}

    string getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    int getCreditos() const { return creditos; }
    string getTipo() const { return tipo; }
    int getCiclo() const { return ciclo; }
    bool getEsElectivo() const { return esElectivo; }
    string getArea() const { return area; }

    const vector<string>& getPrerequisitos() const { return prerequisitos; }
    const vector<Grupo>& getGrupos() const { return grupos; }

    void agregarPrerequisito(const string& codCurso) {
        prerequisitos.push_back(codCurso);
    }

    void agregarGrupo(const Grupo& grupo) {
        grupos.push_back(grupo);
    }
};
