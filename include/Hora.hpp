#pragma once
#include <string>

using namespace std;

class Hora {
private:
    int dia;             // 1 = Lunes ... 5 = Viernes
    int horaInicio;      // minutos desde 00:00
    int horaFin;
    string tipo;         // "TEO" o "LAB"
    string aula;

public:
    Hora(int d, int hi, int hf, string aula, string tipo)
            : dia(d), horaInicio(hi), horaFin(hf), aula(aula), tipo(tipo) {}
    int getDia() const { return dia; }
    int getInicio() const { return horaInicio; }
    int getFin() const { return horaFin; }
    string getTipo() const { return tipo; }
    string getAula() const { return aula; }
    bool seCruzaCon(const Hora& otro) const {
        return dia == otro.dia &&
               !(horaFin <= otro.horaInicio || horaInicio >= otro.horaFin);
    }
};
