#pragma once
#include <string>

using namespace std;

class Hora {
private:
    int dia;             // 1 = Lunes ... 5 = Viernes
    int horaInicio;      // minutos desde 00:00
    int horaFin;         // minutos desde 00:00
    string aula;

public:
    Hora(int d, int hi, int hf, const string& aula_)
        : dia(d), horaInicio(hi), horaFin(hf), aula(aula_) {}

    int getDia() const { return dia; }
    int getInicio() const { return horaInicio; }
    int getFin() const { return horaFin; }
    string getAula() const { return aula; }

    bool seCruzaCon(const Hora& otro) const {
        return dia == otro.dia &&
               !(horaFin <= otro.horaInicio || horaInicio >= otro.horaFin);
    }
};
