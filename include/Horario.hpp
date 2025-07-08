#pragma once
#include <vector>
#include "Grupo.hpp"

using namespace std;

class Horario {
private:
    vector<Grupo*> gruposSeleccionados; // Un grupo por curso
    int horasHueco;                    // Total de horas vacías entre clases
    int diasLibres;                    // Número de días sin clases
    int maxCreditosPorDia;             // Máximo crédito en un solo día
    int costoTotal;                    // Valor para evaluar preferencia general

public:
    // Constructor por defecto
    Horario() : horasHueco(0), diasLibres(0), maxCreditosPorDia(0), costoTotal(0) {}
    
    // Constructor con grupos - CORREGIDO
    Horario(const vector<Grupo*>& grupos) : gruposSeleccionados(grupos), 
                                          horasHueco(0), 
                                          diasLibres(0), 
                                          maxCreditosPorDia(0), 
                                          costoTotal(0) {}
    
    // Métodos para manipulación de grupos
    void agregarGrupo(Grupo* grupo) {
        gruposSeleccionados.push_back(grupo);
    }

    // Getters
    const vector<Grupo*>& getGrupos() const {
        return gruposSeleccionados;
    }
    
    vector<Grupo*>& getGrupos() {
        return gruposSeleccionados;
    }

    // Métodos para calcular métricas
    void calcularHorasHueco();
    void calcularDiasLibres();
    void calcularMaxCreditosPorDia();
    void calcularCostoTotal();

    // Getters para métricas
    int getHorasHueco() const { return horasHueco; }
    int getDiasLibres() const { return diasLibres; }
    int getMaxCreditosPorDia() const { return maxCreditosPorDia; }
    int getCostoTotal() const { return costoTotal; }
};