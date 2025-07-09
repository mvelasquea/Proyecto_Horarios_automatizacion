#pragma once
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include "Grupo.hpp"

using namespace std;

class Horario {
private:
    vector<Grupo*> gruposSeleccionados; // Un grupo por curso

    // MÉTRICAS CALCULADAS
    int horasHueco = 0;
    int diasLibres = 0;
    int bloquesManana = 0, bloquesTarde = 0, bloquesNoche = 0;
    int primerBloque = 24*60, ultimoBloque = 0;
    int maxClasesContinuas = 0;
    int maxClasesPorDia = 0;
    int totalDiasConClase = 0;
    int diasConUnaSolaClase = 0;
    int creditosTotales = 0;
    int cantidadCursos = 0;
    int minutosTotalesEnAula = 0;
    int minutosTotalesEnHuecos = 0;

public:
    // Constructor por defecto
    Horario() = default;

    // Constructor con vector de grupos
    Horario(const vector<Grupo*>& grupos)
        : gruposSeleccionados(grupos) {
        calcularMetricas();
    }

    // Getter del vector (const y no const)
    const vector<Grupo*>& getGrupos() const { return gruposSeleccionados; }
    vector<Grupo*>& getGrupos() { return gruposSeleccionados; }

    void setGrupos(const vector<Grupo*>& grupos) {
        gruposSeleccionados = grupos;
        calcularMetricas();
    }
    void agregarGrupo(Grupo* grupo) {
        gruposSeleccionados.push_back(grupo);
        calcularMetricas();
    }

    // =========== MÉTRICAS ==============
    void calcularMetricas() {
        // Map: dia (1-7) -> lista de (inicio, fin)
        map<int, vector<pair<int, int>>> clasesPorDia;
        set<string> codigosCurso;
        creditosTotales = 0;
        minutosTotalesEnAula = 0;

        for (Grupo* grupo : gruposSeleccionados) {
            codigosCurso.insert(grupo->getCurso()->getCodigo());
            creditosTotales += grupo->getCurso()->getCreditos();
            for (const Hora& h : grupo->getHoras()) {
                clasesPorDia[h.getDia()].push_back({h.getInicio(), h.getFin()});
                minutosTotalesEnAula += h.getFin() - h.getInicio();
            }
        }
        cantidadCursos = codigosCurso.size();

        horasHueco = 0;
        minutosTotalesEnHuecos = 0;
        diasLibres = 0;
        bloquesManana = bloquesTarde = bloquesNoche = 0;
        primerBloque = 24*60; ultimoBloque = 0;
        maxClasesContinuas = 0;
        maxClasesPorDia = 0;
        totalDiasConClase = 0;
        diasConUnaSolaClase = 0;

        for (int dia = 1; dia <= 7; ++dia) {
            auto& bloques = clasesPorDia[dia];
            if (bloques.empty()) {
                ++diasLibres;
                continue;
            }
            ++totalDiasConClase;
            if (bloques.size() == 1) ++diasConUnaSolaClase;
            maxClasesPorDia = max<int>(maxClasesPorDia, bloques.size());
            // Ordenar por hora de inicio
            sort(bloques.begin(), bloques.end());
            // Bloques por franja
            for (const auto& bl : bloques) {
                if (bl.first < primerBloque) primerBloque = bl.first;
                if (bl.second > ultimoBloque) ultimoBloque = bl.second;
                if (bl.first < 12*60) ++bloquesManana;
                else if (bl.first < 18*60) ++bloquesTarde;
                else ++bloquesNoche;
            }
            // Calcular huecos y continuidad
            int continuidad = 1;
            for (size_t i = 1; i < bloques.size(); ++i) {
                int hueco = bloques[i].first - bloques[i-1].second;
                if (hueco > 0) {
                    horasHueco += hueco / 60;
                    minutosTotalesEnHuecos += hueco;
                    continuidad = 1;
                } else {
                    continuidad++;
                    maxClasesContinuas = max(maxClasesContinuas, continuidad);
                }
            }
            // Si solo hay una clase, la continuidad es 1
            maxClasesContinuas = max(maxClasesContinuas, 1);
        }
    }

    // ======= GETTERS DE MÉTRICAS ======
    int getHorasHueco() const { return horasHueco; }
    int getDiasLibres() const { return diasLibres; }
    int getBloquesManana() const { return bloquesManana; }
    int getBloquesTarde() const { return bloquesTarde; }
    int getBloquesNoche() const { return bloquesNoche; }
    int getPrimerBloque() const { return primerBloque; }
    int getUltimoBloque() const { return ultimoBloque; }
    int getMaxClasesContinuas() const { return maxClasesContinuas; }
    int getMaxClasesPorDia() const { return maxClasesPorDia; }
    int getTotalDiasConClase() const { return totalDiasConClase; }
    int getDiasConUnaSolaClase() const { return diasConUnaSolaClase; }
    int getCreditosTotales() const { return creditosTotales; }
    int getCantidadCursos() const { return cantidadCursos; }
    int getMinutosTotalesEnAula() const { return minutosTotalesEnAula; }
    int getMinutosTotalesEnHuecos() const { return minutosTotalesEnHuecos; }
};

