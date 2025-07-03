#include "Curso.h"

Curso::Curso() : codigo(""), nombre(""), creditos(0), grupo("") {}

Curso::Curso(std::string c, std::string n, int cred, std::string g)
    : codigo(c), nombre(n), creditos(cred), grupo(g) {}

void Curso::agregarHorario(const HorarioCurso& horario) {
    horarios.push_back(horario);
}

const std::vector<HorarioCurso>& Curso::obtenerHorarios() const {
    return horarios;
}

std::string Curso::obtenerCodigoGrupo() const {
    return codigo + "-" + grupo;
}

std::string Curso::obtenerCodigo() const {
    return codigo;
}

std::string Curso::obtenerGrupo() const {
    return grupo;
}

std::string Curso::obtenerNombre() const {
    return nombre;
}

int Curso::obtenerCreditos() const {
    return creditos;
}
