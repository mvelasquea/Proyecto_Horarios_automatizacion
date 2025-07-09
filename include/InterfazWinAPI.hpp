#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Sistema.hpp"
#include "Curso.hpp"  // Usar la clase Curso del sistema principal

#ifdef _WIN32
#include <windows.h>
#include <commctrl.h>
#endif

// Estructura para horarios específica para Win API
struct HorarioWinAPI {
    std::string dia;
    std::string franja;
    std::string tipo;
};

class InterfazWinAPI {
private:
    Sistema* sistema;
    std::string rutaDataDir;
    
    struct CursoWinAPI {
        std::string curso;
        std::string nombre;
        std::string grupo_id;
        std::string tipo;
        std::string aula;
        std::string horas;
        std::string docente;
        int cupos;
        bool seleccionado;
        
        CursoWinAPI(const std::string& c, const std::string& n, const std::string& g, 
                   const std::string& t, const std::string& a, const std::string& h, 
                   const std::string& d, int cu, bool sel = false)
            : curso(c), nombre(n), grupo_id(g), tipo(t), aula(a), horas(h), 
              docente(d), cupos(cu), seleccionado(sel) {}
    };
    
    std::vector<CursoWinAPI> cursosWinAPI;
    
public:
    InterfazWinAPI(Sistema* sys, const std::string& dataDir = "data/");
    
    // Métodos principales
    void inicializar();
    void cargarDatosDesdeCSV(const std::string& rutaCSV);
    void sincronizarConSistema();
    void exportarSeleccionados(const std::string& rutaDestino);
    
    // Conversión de datos
    std::vector<Curso> convertirACursos(const std::vector<CursoWinAPI>& cursosWin);
    std::vector<CursoWinAPI> convertirDeCursos(const std::vector<Curso>& cursos);
    
    // Utilidades
    void marcarSeleccionado(int index, bool seleccionado);
    void seleccionarTodos(bool seleccionar);
    std::vector<CursoWinAPI> obtenerSeleccionados() const;
    
    // Validación
    bool validarDatos(const CursoWinAPI& curso) const;
    bool validarHorario(const std::string& horario) const;
    
    // Getters
    const std::vector<CursoWinAPI>& getCursosWinAPI() const { return cursosWinAPI; }
    size_t getCantidadCursos() const { return cursosWinAPI.size(); }
    
    // Destructor
    ~InterfazWinAPI();
};