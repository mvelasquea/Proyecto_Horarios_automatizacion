#pragma once
#include <string>

using namespace std;

class Hora {
private:
    int dia;             // 1 = Lunes ... 5 = Viernes
    int horaInicio;      // minutos desde 00:00
    int horaFin;
    string tipo;         // "TEO" o "LAB"

public:
    Hora(int d, int hi, int hf, string t)
        : dia(d), horaInicio(hi), horaFin(hf), tipo(t) {}

    int getDia() const { return dia; }
    int getInicio() const { return horaInicio; }
    int getFin() const { return horaFin; }
    string getTipo() const { return tipo; }

    bool seCruzaCon(const Hora& otro) const {
        return dia == otro.dia &&
               !(horaFin <= otro.horaInicio || horaInicio >= otro.horaFin);
    }
};
