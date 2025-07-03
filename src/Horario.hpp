#pragma once
#include <string>

using namespace std;

class Horario {
private:
    int dia;             // 0 = Lunes ... 5 = Sábado
    int horaInicio;      // En minutos desde 00:00
    int horaFin;
    string aula;
    string tipo;         // "TEO" o "LAB"

public:
    Horario(int d, int hi, int hf, string a, string t)
        : dia(d), horaInicio(hi), horaFin(hf), aula(a), tipo(t) {}

    int getDia() const { return dia; }
    int getInicio() const { return horaInicio; }
    int getFin() const { return horaFin; }
    string getAula() const { return aula; }
    string getTipo() const { return tipo; }

    bool seCruzaCon(const Horario& otro) const {
        return dia == otro.dia &&
               !(horaFin <= otro.horaInicio || horaInicio >= otro.horaFin);
    }
};
