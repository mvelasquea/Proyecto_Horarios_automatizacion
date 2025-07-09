#ifndef CURSO_MANAGER_H
#define CURSO_MANAGER_H

#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "curso_data.h"

// Incluir sistema principal
#include "../include/InterfazWinAPI.hpp"

// IDs de controles
#define IDC_LISTVIEW        1001
#define IDC_BTN_SELECT_ALL  1002
#define IDC_BTN_DESELECT_ALL 1003
#define IDC_BTN_ADD_COURSE  1004
#define IDC_BTN_EDIT_COURSE 1005
#define IDC_BTN_DELETE_COURSE 1006
#define IDC_BTN_EXPORT_CSV  1007

// IDs del diálogo
#define IDD_CURSO_DIALOG    2001
#define IDC_EDIT_CURSO      2002
#define IDC_EDIT_NOMBRE     2003
#define IDC_EDIT_GRUPO_ID   2004
#define IDC_COMBO_TIPO      2005
#define IDC_EDIT_AULA       2006
#define IDC_EDIT_HORAS      2007
#define IDC_EDIT_DOCENTE    2008
#define IDC_EDIT_CUPOS      2009
#define IDC_BTN_OK          2010
#define IDC_BTN_CANCEL      2011

class CursoManager {
private:
    HWND hWnd;
    HWND hListView;
    std::vector<CursoData> cursos;
    int selectedIndex;
    InterfazWinAPI* interfazWinAPI;
    
    // Funciones privadas
    void InitializeListView();
    void PopulateListView();
    void UpdateListView();
    void SelectAllItems(bool select);
    void AddCourse();
    void EditCourse();
    void DeleteCourse();
    void ExportToCSV();
    void SyncWithSystem();
    void LoadFromSystem();
    std::string GetSelectedItemText(int item, int subItem);
    int GetSelectedItemIndex();
    
    // Diálogo
    static INT_PTR CALLBACK CourseDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
    bool ShowCourseDialog(CursoData* curso = nullptr);
    
public:
    CursoManager(HWND parentHwnd, InterfazWinAPI* interfaz = nullptr);
    ~CursoManager();
    
    void HandleCommand(WORD id);
    void HandleNotify(LPNMHDR pnmh);
    HWND GetListViewHandle() { return hListView; }
    
    // Métodos de integración con sistema principal
    void SetInterfazWinAPI(InterfazWinAPI* interfaz) { interfazWinAPI = interfaz; }
    void RefreshFromSystem();
};

#endif // CURSO_MANAGER_H
