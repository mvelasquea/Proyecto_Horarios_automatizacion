
std::vector<Curso> Filtros::filtrarPorTurno(const std::vector<Curso>& cursos, const std::string& turno) {
    std::vector<Curso> filtrados;
    for (const auto& curso : cursos) {
        bool coincide = false;
        for (const auto& h : curso.obtenerHorarios()) {
            if ((turno == "mañana" && h.franja < "13:00") ||
                (turno == "tarde" && h.franja >= "13:00" && h.franja < "18:00") ||
                (turno == "noche" && h.franja >= "18:00")) {
                coincide = true;
            }
        }
        if (coincide) filtrados.push_back(curso);
    }
    return filtrados;
}
