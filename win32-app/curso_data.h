#ifndef CURSO_DATA_H
#define CURSO_DATA_H

#include <string>
#include <vector>

struct CursoData {
    std::string curso;
    std::string nombre;
    std::string grupo_id;
    std::string tipo;
    std::string aula;
    std::string horas;
    std::string docente;
    int cupos;
    bool seleccionado;
    
    CursoData(const std::string& c, const std::string& n, const std::string& g, 
              const std::string& t, const std::string& a, const std::string& h, 
              const std::string& d, int cu, bool sel = false)
        : curso(c), nombre(n), grupo_id(g), tipo(t), aula(a), horas(h), docente(d), cupos(cu), seleccionado(sel) {}
};

// Datos de ejemplo con el formato especificado
inline std::vector<CursoData> getCursosData() {
    return {
        CursoData("1703133", "ALGORITMOS Y PROGRAMACION", "1", "F", "B201", "1_08:00-09:40 3_08:00-09:40", "María López", 25),
        CursoData("1703133", "ALGORITMOS Y PROGRAMACION", "2", "F", "B202", "1_08:30-10:10 3_08:30-10:10", "Carlos Sánchez", 28),
        CursoData("1703133", "ALGORITMOS Y PROGRAMACION", "101", "L", "Lab1", "2_10:00-11:40", "Juan Pérez", 18),
        CursoData("1703134", "ESTRUCTURAS DE DATOS", "1", "F", "C105", "1_08:00-09:40 3_08:00-09:40", "Laura Méndez", 22),
        CursoData("1703134", "ESTRUCTURAS DE DATOS", "2", "F", "C106", "1_09:00-10:40 3_09:00-10:40", "Diego Castillo", 21),
        CursoData("1703134", "ESTRUCTURAS DE DATOS", "101", "L", "Lab5", "2_10:00-11:40", "Andrés López", 19),
        CursoData("1703135", "INGENIERIA Y PROCESOS DE SOFTWARE", "1", "F", "D303", "1_10:00-11:40 3_10:00-11:40", "Ana Martínez", 18),
        CursoData("1703135", "INGENIERIA Y PROCESOS DE SOFTWARE", "2", "F", "D304", "1_10:30-12:10 3_10:30-12:10", "Ricardo Torres", 19),
        CursoData("1703135", "INGENIERIA Y PROCESOS DE SOFTWARE", "101", "L", "Lab9", "2_14:00-15:40", "Claudia Ruiz", 15),
        CursoData("1701212", "PROGRAMACION WEB 1", "1", "F", "D401", "1_16:00-18:00 2_08:00-10:00", "Ing. Sandra Vega", 25),
        CursoData("1701212", "PROGRAMACION WEB 1", "101", "L", "Lab2", "4_08:00-12:00", "Ing. Miguel Flores", 15)
    };
}

#endif // CURSO_DATA_H
