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
    int horasTeoricas;
    int horasPracticas;
    int horasLaboratorio;
    vector<Grupo> grupos;

public:
    // Constructor completo con parámetros opcionales
    Curso(string cod, string t, string nom, int cred, int cic,
          string prq1 = "", string prq2 = "",
          int hTeo = 0, int hPrac = 0, int hLab = 0) :
        codigo(cod), tipo(t), nombre(nom), 
        creditos(cred), ciclo(cic),
        prerequisito1(prq1), prerequisito2(prq2),
        horasTeoricas(hTeo), horasPracticas(hPrac), 
        horasLaboratorio(hLab) {}

    // --- Getters ---
    string getCodigo() const { return codigo; }
    string getTipo() const { return tipo; }
    string getNombre() const { return nombre; }
    int getCreditos() const { return creditos; }
    int getCiclo() const { return ciclo; }
    string getPrerequisito1() const { return prerequisito1; }
    string getPrerequisito2() const { return prerequisito2; }
    int getHorasTeoricas() const { return horasTeoricas; }
    int getHorasPracticas() const { return horasPracticas; }
    int getHorasLaboratorio() const { return horasLaboratorio; }
    const vector<Grupo>& getGrupos() const { return grupos; }
    vector<Grupo>& getGrupos() { return grupos; }

    // --- Setters ---
    void setPrerequisito1(const string& codCurso) { prerequisito1 = codCurso; }
    void setPrerequisito2(const string& codCurso) { prerequisito2 = codCurso; }
    void setHorasTeoricas(int h) { horasTeoricas = h; }
    void setHorasPracticas(int h) { horasPracticas = h; }
    void setHorasLaboratorio(int h) { horasLaboratorio = h; }

    // --- Manejo de grupos ---
    void agregarGrupo(const Grupo& grupo) { grupos.push_back(grupo); }

    // --- Laboratorios ---
    bool tieneLaboratorio() const {
        for (const auto& g : grupos) {
            if (g.esLab()) return true;
        }
        return false;
    }
    bool requiereLaboratorio() const { return horasLaboratorio > 0; }

    // --- Filtrado de grupos ---
    vector<Grupo*> getGruposTeoricos() {
        vector<Grupo*> teoricos;
        for (auto& g : grupos) {
            if (!g.esLab()) teoricos.push_back(&g);
        }
        return teoricos;
    }

    vector<const Grupo*> getGruposTeoricos() const {
        vector<const Grupo*> teoricos;
        for (const auto& g : grupos) {
            if (!g.esLab()) teoricos.push_back(&g);
        }
        return teoricos;
    }

    vector<Grupo*> getGruposLaboratorio() {
        vector<Grupo*> labs;
        for (auto& g : grupos) {
            if (g.esLab()) labs.push_back(&g);
        }
        return labs;
    }

    vector<const Grupo*> getGruposLaboratorio() const {
        vector<const Grupo*> labs;
        for (const auto& g : grupos) {
            if (g.esLab()) labs.push_back(&g);
        }
        return labs;
    }

    // --- Verificación ---
    bool contieneGrupo(const Grupo* grupo) const {
        for (const auto& g : grupos) {
            if (&g == grupo) return true;
        }
        return false;
    }
};