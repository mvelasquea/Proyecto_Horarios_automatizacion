#pragma once
#include <string>
#include <sstream>
#include <iomanip>

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

    string toString() const {
        auto minutosAString = [](int minutos) -> string {
            int h = minutos / 60;
            int m = minutos % 60;
            std::ostringstream oss;
            oss << std::setw(2) << std::setfill('0') << h << ":"
                << std::setw(2) << std::setfill('0') << m;
            return oss.str();
        };

        return std::to_string(dia) + "_" + minutosAString(horaInicio) + "-" + minutosAString(horaFin);
    }
};
