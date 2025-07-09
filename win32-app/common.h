#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <string>
#include <vector>

// Estructura para los datos del curso
struct CursoData {
    std::string curso;
    std::string grupo_id;
    std::string tipo;
    std::string aula;
    std::string horas;
    std::string docente;
    int cupos;
    bool seleccionado;
};

// Variables globales
extern HINSTANCE g_hInst;
extern HWND g_hMainWnd;
extern HWND g_hListView;
extern std::vector<CursoData> g_cursos;
extern int g_editingIndex;

// Prototipos de funciones compartidas
std::string WStringToString(const std::wstring& wstr);
std::wstring StringToWString(const std::string& str);
void PopulateListView();

// Prototipos de funciones del diálogo
INT_PTR CALLBACK CourseDialogProc(HWND, UINT, WPARAM, LPARAM);
void SaveCourseData(HWND hDlg);
void LoadCourseData(HWND hDlg);

#endif // COMMON_H
