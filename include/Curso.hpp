#pragma once
#include <string>
#include <vector>
#include "Grupo.hpp"

using namespace std;

class Curso {
private:
    string codigo;
    string tipo;           // D, F, E, G
    string nombre;
    int creditos;
    int ciclo;
    string prerequisito1;  // PRQ1
    string prerequisito2;  // PRQ2
    vector<Grupo> grupos;

public:
    Curso(string cod, string t, string nom, int cred, int cic, 
          string prq1 = "", string prq2 = "")
        : codigo(cod), tipo(t), nombre(nom), creditos(cred), ciclo(cic), 
          prerequisito1(prq1), prerequisito2(prq2) {}

    string getCodigo() const { return codigo; }
    string getTipo() const { return tipo; }
    string getNombre() const { return nombre; }
    int getCreditos() const { return creditos; }
    int getCiclo() const { return ciclo; }
    string getPrerequisito1() const { return prerequisito1; }
    string getPrerequisito2() const { return prerequisito2; }
    const vector<Grupo>& getGrupos() const { return grupos; }

    void setPrerequisito1(const string& codCurso) { prerequisito1 = codCurso; }
    void setPrerequisito2(const string& codCurso) { prerequisito2 = codCurso; }

    void agregarGrupo(const Grupo& grupo) { grupos.push_back(grupo); }
};
