#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Sistema.hpp"

class InterfazWeb {
private:
    Sistema* sistema;
    std::string rutaWeb;
    std::string rutaCSV;
    std::string rutaPreferencias;
    
    struct PreferenciasUsuario {
        std::string turnoPreferido;
        int creditosMin;
        int creditosMax;
        bool permitirCruces;
        bool incluirLabs;
        std::string fechaCreacion;
    };
    
    PreferenciasUsuario preferencias;
    
public:
    InterfazWeb(Sistema* sys, const std::string& rutaWebDir = "web/");
    
    // Métodos principales
    void inicializar();
    void iniciarServidor();
    void procesarDatosCSV(const std::string& rutaCSV);
    void cargarPreferencias(const std::string& rutaJSON);
    void generarHorarios();
    void exportarResultados();
    
    // Métodos de utilidad
    std::string leerArchivoHTML(const std::string& archivo);
    void escribirArchivoCSV(const std::string& contenido);
    void escribirResultados(const std::string& resultados);
    
    // Procesamiento de datos
    std::vector<std::string> parsearCSV(const std::string& linea);
    std::string formatearHorarios(const std::vector<Horario>& horarios);
    
    // Getters y setters
    void setRutaCSV(const std::string& ruta) { rutaCSV = ruta; }
    void setRutaPreferencias(const std::string& ruta) { rutaPreferencias = ruta; }
    const PreferenciasUsuario& getPreferencias() const { return preferencias; }
    
    // Métodos de validación
    bool validarDatosCSV(const std::string& rutaCSV);
    bool validarPreferencias(const PreferenciasUsuario& pref);
    
    // Métodos de integración
    void sincronizarConSistema();
    void actualizarInterfaz();
    
    // Destructor
    ~InterfazWeb();
};
