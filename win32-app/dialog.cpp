#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <string>
#include "resource.h"
#include "common.h"

INT_PTR CALLBACK CourseDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
        {
            // Configurar el combo box de tipo
            HWND hComboTipo = GetDlgItem(hDlg, IDC_COMBO_TIPO);
            SendMessage(hComboTipo, CB_ADDSTRING, 0, (LPARAM)L"TEORIA");
            SendMessage(hComboTipo, CB_ADDSTRING, 0, (LPARAM)L"LABORATORIO");
            SendMessage(hComboTipo, CB_ADDSTRING, 0, (LPARAM)L"PRACTICA");
            SendMessage(hComboTipo, CB_SETCURSEL, 0, 0);
            
            // Si estamos editando, cargar los datos
            if (g_editingIndex >= 0) {
                LoadCourseData(hDlg);
                SetWindowText(hDlg, L"Editar Curso");
            } else {
                SetWindowText(hDlg, L"Agregar Curso");
            }
            
            return TRUE;
        }
        
        case WM_COMMAND:
        {
            switch (LOWORD(wParam)) {
                case IDC_BTN_SAVE:
                    SaveCourseData(hDlg);
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                    
                case IDC_BTN_CANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            break;
        }
        
        case WM_CLOSE:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
    }
    return FALSE;
}

void SaveCourseData(HWND hDlg) {
    wchar_t buffer[256];
    
    // Obtener datos del diálogo
    CursoData curso;
    
    GetDlgItemText(hDlg, IDC_EDIT_CURSO, buffer, 256);
    curso.curso = WStringToString(buffer);
    
    GetDlgItemText(hDlg, IDC_EDIT_GRUPO_ID, buffer, 256);
    curso.grupo_id = WStringToString(buffer);
    
    HWND hComboTipo = GetDlgItem(hDlg, IDC_COMBO_TIPO);
    int tipoIndex = SendMessage(hComboTipo, CB_GETCURSEL, 0, 0);
    SendMessage(hComboTipo, CB_GETLBTEXT, tipoIndex, (LPARAM)buffer);
    curso.tipo = WStringToString(buffer);
    
    GetDlgItemText(hDlg, IDC_EDIT_AULA, buffer, 256);
    curso.aula = WStringToString(buffer);
    
    GetDlgItemText(hDlg, IDC_EDIT_HORAS, buffer, 256);
    curso.horas = WStringToString(buffer);
    
    GetDlgItemText(hDlg, IDC_EDIT_DOCENTE, buffer, 256);
    curso.docente = WStringToString(buffer);
    
    GetDlgItemText(hDlg, IDC_EDIT_CUPOS, buffer, 256);
    curso.cupos = _wtoi(buffer);
    
    curso.seleccionado = false;
    
    // Validar datos
    if (curso.curso.empty() || curso.grupo_id.empty() || curso.aula.empty() || 
        curso.horas.empty() || curso.docente.empty() || curso.cupos <= 0) {
        MessageBox(hDlg, L"Por favor complete todos los campos correctamente", L"Error", MB_OK | MB_ICONERROR);
        return;
    }
    
    // Guardar o actualizar curso
    if (g_editingIndex >= 0) {
        g_cursos[g_editingIndex] = curso;
    } else {
        g_cursos.push_back(curso);
    }
    
    PopulateListView();
}

void LoadCourseData(HWND hDlg) {
    if (g_editingIndex < 0 || g_editingIndex >= g_cursos.size()) return;
    
    const CursoData& curso = g_cursos[g_editingIndex];
    
    SetDlgItemText(hDlg, IDC_EDIT_CURSO, StringToWString(curso.curso).c_str());
    SetDlgItemText(hDlg, IDC_EDIT_GRUPO_ID, StringToWString(curso.grupo_id).c_str());
    SetDlgItemText(hDlg, IDC_EDIT_AULA, StringToWString(curso.aula).c_str());
    SetDlgItemText(hDlg, IDC_EDIT_HORAS, StringToWString(curso.horas).c_str());
    SetDlgItemText(hDlg, IDC_EDIT_DOCENTE, StringToWString(curso.docente).c_str());
    SetDlgItemText(hDlg, IDC_EDIT_CUPOS, std::to_wstring(curso.cupos).c_str());
    
    HWND hComboTipo = GetDlgItem(hDlg, IDC_COMBO_TIPO);
    if (curso.tipo == "TEORIA") {
        SendMessage(hComboTipo, CB_SETCURSEL, 0, 0);
    } else if (curso.tipo == "LABORATORIO") {
        SendMessage(hComboTipo, CB_SETCURSEL, 1, 0);
    } else if (curso.tipo == "PRACTICA") {
        SendMessage(hComboTipo, CB_SETCURSEL, 2, 0);
    }
}
