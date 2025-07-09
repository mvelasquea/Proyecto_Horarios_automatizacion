#pragma once
#include <vector>
#include "Grupo.hpp"

using namespace std;

class Horario {
private:
    vector<Grupo*> gruposSeleccionados; // Un grupo por curso
    int horasHueco = 0;
    int diasLibres = 0;

public:
    // Constructor por defecto
    Horario() = default;

    // Constructor con vector de grupos
    Horario(const vector<Grupo*>& grupos)
        : gruposSeleccionados(grupos) {}

    // Getter del vector (const y no const)
    const vector<Grupo*>& getGrupos() const { return gruposSeleccionados; }
    vector<Grupo*>& getGrupos() { return gruposSeleccionados; }

    // Setter del vector
    void setGrupos(const vector<Grupo*>& grupos) { gruposSeleccionados = grupos; }

    // Agregar grupo
    void agregarGrupo(Grupo* grupo) { gruposSeleccionados.push_back(grupo); }

    // Getters de métricas
    int getHorasHueco() const { return horasHueco; }
    int getDiasLibres() const { return diasLibres; }

    // Setters de métricas
    void setHorasHueco(int val) { horasHueco = val; }
    void setDiasLibres(int val) { diasLibres = val; }
};
