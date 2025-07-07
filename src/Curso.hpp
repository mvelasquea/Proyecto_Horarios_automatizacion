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
    int ciclo;
    vector<string> prerequisitos;
    vector<Grupo> grupos;

public:
    Curso(string cod, string nom, int cred, int c)
        : codigo(cod), nombre(nom), creditos(cred), ciclo(c) {}

    string getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    int getCreditos() const { return creditos; }
    int getCiclo() const { return ciclo; }
    const vector<string>& getPrerequisitos() const { return prerequisitos; }
    const vector<Grupo>& getGrupos() const { return grupos; }

    void agregarPrerequisito(const string& codCurso) {
        prerequisitos.push_back(codCurso);
    }

    void agregarGrupo(const Grupo& grupo) {
        grupos.push_back(grupo);
    }
};
