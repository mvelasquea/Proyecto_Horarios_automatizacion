#pragma once
#include <string>
#include <vector>
#include "Grupo.hpp"

using namespace std;

class Curso {
private:
    string codigo;
    string tipo;           // D, F, E, G
    string nombre;
    int creditos;
    int ciclo;
    string prerequisito1;  // PRQ1
    string prerequisito2;  // PRQ2
    int horasTeoricas;
    int horasPracticas;
    int horasLaboratorio;
    vector<Grupo> grupos;

public:
    // Constructor completo con parámetros opcionales
    Curso(string cod, string t, string nom, int cred, int cic,
          string prq1 = "", string prq2 = "",
          int hTeo = 0, int hPrac = 0, int hLab = 0) :
        codigo(cod), tipo(t), nombre(nom), 
        creditos(cred), ciclo(cic),
        prerequisito1(prq1), prerequisito2(prq2),
        horasTeoricas(hTeo), horasPracticas(hPrac), 
        horasLaboratorio(hLab) {}

    // --- Getters ---
    string getCodigo() const { return codigo; }
    string getTipo() const { return tipo; }
    string getNombre() const { return nombre; }
    int getCreditos() const { return creditos; }
    int getCiclo() const { return ciclo; }
    string getPrerequisito1() const { return prerequisito1; }
    string getPrerequisito2() const { return prerequisito2; }
    int getHorasTeoricas() const { return horasTeoricas; }
    int getHorasPracticas() const { return horasPracticas; }
    int getHorasLaboratorio() const { return horasLaboratorio; }
    const vector<Grupo>& getGrupos() const { return grupos; }
    vector<Grupo>& getGrupos() { return grupos; }

    // --- Setters ---
    void setPrerequisito1(const string& codCurso) { prerequisito1 = codCurso; }
    void setPrerequisito2(const string& codCurso) { prerequisito2 = codCurso; }
    void setHorasTeoricas(int h) { horasTeoricas = h; }
    void setHorasPracticas(int h) { horasPracticas = h; }
    void setHorasLaboratorio(int h) { horasLaboratorio = h; }

    // --- Manejo de grupos ---
    void agregarGrupo(const Grupo& grupo) { grupos.push_back(grupo); }

    // --- Laboratorios ---
    bool tieneLaboratorio() const {
        for (const auto& g : grupos) {
            if (g.esLab()) return true;
        }
        return false;
    }
    bool requiereLaboratorio() const { return horasLaboratorio > 0; }

    // --- Filtrado de grupos ---
    vector<Grupo*> getGruposTeoricos() {
        vector<Grupo*> teoricos;
        for (auto& g : grupos) {
            if (!g.esLab()) teoricos.push_back(&g);
        }
        return teoricos;
    }

    vector<const Grupo*> getGruposTeoricos() const {
        vector<const Grupo*> teoricos;
        for (const auto& g : grupos) {
            if (!g.esLab()) teoricos.push_back(&g);
        }
        return teoricos;
    }

    vector<Grupo*> getGruposLaboratorio() {
        vector<Grupo*> labs;
        for (auto& g : grupos) {
            if (g.esLab()) labs.push_back(&g);
        }
        return labs;
    }

    vector<const Grupo*> getGruposLaboratorio() const {
        vector<const Grupo*> labs;
        for (const auto& g : grupos) {
            if (g.esLab()) labs.push_back(&g);
        }
        return labs;
    }

    // --- Verificación ---
    bool contieneGrupo(const Grupo* grupo) const {
        for (const auto& g : grupos) {
            if (&g == grupo) return true;
        }
        return false;
    }

    string getNombreAbreviado() const {
        static const std::unordered_map<std::string, std::string> abreviaturas = {
            {"1701102", "Raz. Log. Mat."},
            {"1701103", "Mat. Básica"},
            {"1701104", "Est. Discretas I"},
            {"1701105", "Intro. Comput."},
            {"1701106", "Fund. Prog. 1"},
            {"1701114", "Met. Trab. Int."},
            {"1701145", "Rel. Humanas SW"},
            {"1701210", "Cálculo 1 Var."},
            {"1701211", "Est. Discretas II"},
            {"1701212", "Prog. Web 1"},
            {"1701213", "Fund. Prog. 2"},
            {"1701216", "Com. Integral"},
            {"1701217", "Realidad Nal."},
            {"1702118", "Tall. Psicología"},
            {"1702119", "Cálculo Var."},
            {"1702120", "Tall. Liderazgo"},
            {"1702121", "Innov. Creatividad"},
            {"1702122", "Prog. Web 2"},
            {"1702123", "Red. Art. Inf."},
            {"1702124", "EDA"},
            {"1702125", "Ciudadanía Inter."},
            {"1702226", "Estad. Prob. Empír."},
            {"1702227", "Arq. Computadoras"},
            {"1702228", "Met. Inv. Redacc."},
            {"1702229", "Inter. Hum-Comp."},
            {"1702230", "Enf. Empresarial"},
            {"1702231", "Análisis y Diseño Alg."},
            {"1702278", "Eco. Cons. Ambiental"},
            {"1703133", "Base de Datos"},
            {"1703134", "Prog. Sistemas"},
            {"1703135", "Ing. y Proc. SW"},
            {"1703136", "Teoría Computación"},
            {"1703137", "Org. y Métodos"},
            {"1703138", "Inv. Operaciones"},
            {"1703239", "Redes y Com. Datos"},
            {"1703240", "Tecn. de Objetos"},
            {"1703241", "Sist. Operativos"},
            {"1703242", "Fund. Sist. Info."},
            {"1703243", "Constr. Software"},
            {"1703244", "Métodos Numéricos"},
            {"1704146", "Física Computacional"},
            {"1704147", "Tecn. Información"},
            {"1704148", "Inteligencia Artificial"},
            {"1704149", "Ing. Requerimientos"},
            {"1704150", "Sist. Distribuidos"},
            {"1704151", "Pruebas de SW"},
            {"1704153", "Inglés"},
            {"1704252", "Gest. Proy. SW"},
            {"1704254", "Calidad SW"},
            {"1704255", "Aud. Sistemas"},
            {"1704256", "Diseño y Arq. SW"},
            {"1705161", "Proy. Ing. SW 1"},
            {"1705162", "Seminario Tesis 1"},
            {"1705163", "Gest. Emprendimiento SW"},
            {"1705164", "Seguridad Informática"},
            {"1705165", "Mant. Conf. Evol. SW"},
            {"1705166", "Ética Gral. y Prof."},
            {"1705277", "Proy. Integrador II"},
            {"1705278", "Práct. Preprof."},
            {"1705279", "Trabajo Invest."},
            {"1705280", "Arq. Empresarial"},
            {"1705281", "Tóp. Avanz. Videojuegos"},
            {"1705282", "Des. Apps Nube FS"},
            {"1705283", "Aud. Digital Forense"},
            {"1705284", "Aspectos Legales SI"},
            {"1705285", "Deep Learning"},
            {"1705286", "Minería de Datos"},
            {"1705287", "Tall. DevOps"},
        };
        auto it = abreviaturas.find(codigo);
        return (it != abreviaturas.end()) ? it->second : nombre;
    }
};