#pragma once
#include <vector>
#include "Grupo.hpp"

using namespace std;

class Horario {
private:
    vector<Grupo*> gruposSeleccionados; // Un grupo por curso
    int horasHueco;                     // Total de horas vacías entre clases
    int diasLibres;                    // Número de días sin clases
    int maxCreditosPorDia;             // Máximo crédito en un solo día
    int costoTotal;                    // Valor para evaluar preferencia general

public:
    Horario() : horasHueco(0), diasLibres(0), maxCreditosPorDia(0), costoTotal(0) {}

    void agregarGrupo(Grupo* grupo) {
        gruposSeleccionados.push_back(grupo);
    }

    const vector<Grupo*>& getGrupos() const {
        return gruposSeleccionados;
    }

    // Métodos para calcular métricas
    void calcularHorasHueco();
    void calcularDiasLibres();
    void calcularMaxCreditosPorDia();
    void calcularCostoTotal();

    int getHorasHueco() const { return horasHueco; }
    int getDiasLibres() const { return diasLibres; }
    int getMaxCreditosPorDia() const { return maxCreditosPorDia; }
    int getCostoTotal() const { return costoTotal; }
};
