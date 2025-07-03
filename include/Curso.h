#ifndef CURSO_H
#define CURSO_H

#include <string>
#include <vector>

struct HorarioCurso {
    std::string dia;
    std::string franja;
    std::string tipo;
};

class Curso {
private:
    std::string codigo;
    std::string nombre;
    int creditos;
    std::string grupo;
    std::vector<HorarioCurso> horarios;

public:
    Curso();
    Curso(std::string codigo, std::string nombre, int creditos, std::string grupo);

    void agregarHorario(const HorarioCurso& horario);
    const std::vector<HorarioCurso>& obtenerHorarios() const;

    std::string obtenerCodigoGrupo() const;
    std::string obtenerCodigo() const;
    std::string obtenerGrupo() const;
    std::string obtenerNombre() const;
    int obtenerCreditos() const;
};

#endif
