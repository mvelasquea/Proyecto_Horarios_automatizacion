#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "resource.h"
#include "common.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "comdlg32.lib")

// Constantes para los controles
#define IDC_LISTVIEW_COURSES    1001
#define IDC_BTN_SELECT_ALL      1002
#define IDC_BTN_DESELECT_ALL    1003
#define IDC_BTN_ADD_COURSE      1004
#define IDC_BTN_EXPORT_CSV      1005
#define IDC_BTN_EDIT_COURSE     1006
#define IDC_BTN_DELETE_COURSE   1007

// Controles del diálogo de curso
#define IDC_EDIT_CURSO          2001
#define IDC_EDIT_GRUPO_ID       2002
#define IDC_COMBO_TIPO          2003
#define IDC_EDIT_AULA           2004
#define IDC_EDIT_HORAS          2005
#define IDC_EDIT_DOCENTE        2006
#define IDC_EDIT_CUPOS          2007
#define IDC_BTN_SAVE            2008
#define IDC_BTN_CANCEL          2009

// Diálogo de agregar/editar curso
#define IDD_COURSE_DIALOG       3001

// Variables globales
HINSTANCE g_hInst;
HWND g_hMainWnd;
HWND g_hListView;
std::vector<CursoData> g_cursos;
int g_editingIndex = -1;

// Prototipos de funciones
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitializeListView(HWND hListView);
void AddCourseToListView(const CursoData& curso, int index);
void OnSelectAll();
void OnDeselectAll();
void OnAddCourse();
void OnEditCourse();
void OnDeleteCourse();
void OnExportCSV();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    g_hInst = hInstance;
    
    // Inicializar Common Controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);
    
    // Registrar clase de ventana
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"CursoManagerApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    
    RegisterClass(&wc);
    
    // Crear ventana principal
    g_hMainWnd = CreateWindowEx(
        0,
        L"CursoManagerApp",
        L"Gestor de Cursos y Grupos - Exportador CSV",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1000, 700,
        NULL, NULL, hInstance, NULL
    );
    
    if (!g_hMainWnd) {
        return 0;
    }
    
    ShowWindow(g_hMainWnd, nCmdShow);
    UpdateWindow(g_hMainWnd);
    
    // Bucle de mensajes
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
        {
            // Crear controles
            CreateWindow(L"STATIC", L"Seleccione los cursos y grupos para exportar a CSV",
                WS_VISIBLE | WS_CHILD, 20, 20, 600, 25, hWnd, NULL, g_hInst, NULL);
            
            // Botones
            CreateWindow(L"BUTTON", L"Seleccionar Todo",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                20, 60, 120, 30, hWnd, (HMENU)IDC_BTN_SELECT_ALL, g_hInst, NULL);
            
            CreateWindow(L"BUTTON", L"Deseleccionar Todo",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                150, 60, 120, 30, hWnd, (HMENU)IDC_BTN_DESELECT_ALL, g_hInst, NULL);
            
            CreateWindow(L"BUTTON", L"Agregar Curso",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                280, 60, 120, 30, hWnd, (HMENU)IDC_BTN_ADD_COURSE, g_hInst, NULL);
            
            CreateWindow(L"BUTTON", L"Editar Curso",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                410, 60, 120, 30, hWnd, (HMENU)IDC_BTN_EDIT_COURSE, g_hInst, NULL);
            
            CreateWindow(L"BUTTON", L"Eliminar Curso",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                540, 60, 120, 30, hWnd, (HMENU)IDC_BTN_DELETE_COURSE, g_hInst, NULL);
            
            CreateWindow(L"BUTTON", L"Exportar a CSV",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                670, 60, 120, 30, hWnd, (HMENU)IDC_BTN_EXPORT_CSV, g_hInst, NULL);
            
            // ListView para mostrar cursos
            g_hListView = CreateWindow(WC_LISTVIEW, L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
                20, 100, 940, 520, hWnd, (HMENU)IDC_LISTVIEW_COURSES, g_hInst, NULL);
            
            InitializeListView(g_hListView);
            
            // Agregar algunos datos de ejemplo
            g_cursos.push_back({"1703133", "1", "TEORIA", "B201", "L:08-10, M:14-16", "María López", 25, false});
            g_cursos.push_back({"1703133", "2", "TEORIA", "B202", "L:08-10, M:14-16", "Carlos Sánchez", 28, false});
            g_cursos.push_back({"1703133", "101", "LABORATORIO", "Lab1", "M:10-12", "Juan Pérez", 18, false});
            g_cursos.push_back({"1703134", "1", "TEORIA", "C105", "L:08-10, M:14-16", "Laura Méndez", 22, false});
            g_cursos.push_back({"1703134", "2", "TEORIA", "C106", "L:09-11, M:15-17", "Diego Castillo", 21, false});
            g_cursos.push_back({"1703135", "1", "TEORIA", "D303", "L:10-12, M:16-18", "Ana Martínez", 18, false});
            
            PopulateListView();
            break;
        }
        
        case WM_COMMAND:
        {
            switch (LOWORD(wParam)) {
                case IDC_BTN_SELECT_ALL:
                    OnSelectAll();
                    break;
                case IDC_BTN_DESELECT_ALL:
                    OnDeselectAll();
                    break;
                case IDC_BTN_ADD_COURSE:
                    OnAddCourse();
                    break;
                case IDC_BTN_EDIT_COURSE:
                    OnEditCourse();
                    break;
                case IDC_BTN_DELETE_COURSE:
                    OnDeleteCourse();
                    break;
                case IDC_BTN_EXPORT_CSV:
                    OnExportCSV();
                    break;
            }
            break;
        }
        
        case WM_NOTIFY:
        {
            LPNMHDR pnmh = (LPNMHDR)lParam;
            if (pnmh->hwndFrom == g_hListView) {
                switch (pnmh->code) {
                    case NM_CLICK:
                    {
                        LPNMITEMACTIVATE pnmia = (LPNMITEMACTIVATE)lParam;
                        if (pnmia->iItem >= 0 && pnmia->iSubItem == 0) {
                            // Toggle checkbox
                            g_cursos[pnmia->iItem].seleccionado = !g_cursos[pnmia->iItem].seleccionado;
                            ListView_SetCheckState(g_hListView, pnmia->iItem, g_cursos[pnmia->iItem].seleccionado);
                        }
                        break;
                    }
                }
            }
            break;
        }
        
        case WM_SIZE:
        {
            // Redimensionar controles cuando cambie el tamaño de la ventana
            RECT rect;
            GetClientRect(hWnd, &rect);
            SetWindowPos(g_hListView, NULL, 20, 100, rect.right - 40, rect.bottom - 120, SWP_NOZORDER);
            break;
        }
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void InitializeListView(HWND hListView) {
    // Habilitar checkboxes
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    
    // Agregar columnas
    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    
    lvc.pszText = L"Curso";
    lvc.cx = 100;
    lvc.iSubItem = 0;
    ListView_InsertColumn(hListView, 0, &lvc);
    
    lvc.pszText = L"Grupo ID";
    lvc.cx = 80;
    lvc.iSubItem = 1;
    ListView_InsertColumn(hListView, 1, &lvc);
    
    lvc.pszText = L"Tipo";
    lvc.cx = 100;
    lvc.iSubItem = 2;
    ListView_InsertColumn(hListView, 2, &lvc);
    
    lvc.pszText = L"Aula";
    lvc.cx = 80;
    lvc.iSubItem = 3;
    ListView_InsertColumn(hListView, 3, &lvc);
    
    lvc.pszText = L"Horas";
    lvc.cx = 150;
    lvc.iSubItem = 4;
    ListView_InsertColumn(hListView, 4, &lvc);
    
    lvc.pszText = L"Docente";
    lvc.cx = 150;
    lvc.iSubItem = 5;
    ListView_InsertColumn(hListView, 5, &lvc);
    
    lvc.pszText = L"Cupos";
    lvc.cx = 60;
    lvc.iSubItem = 6;
    ListView_InsertColumn(hListView, 6, &lvc);
}

void PopulateListView() {
    ListView_DeleteAllItems(g_hListView);
    
    for (size_t i = 0; i < g_cursos.size(); ++i) {
        AddCourseToListView(g_cursos[i], i);
    }
}

void AddCourseToListView(const CursoData& curso, int index) {
    LVITEM lvi;
    lvi.mask = LVIF_TEXT | LVIF_PARAM;
    lvi.iItem = index;
    lvi.iSubItem = 0;
    lvi.lParam = index;
    
    std::wstring wCurso = StringToWString(curso.curso);
    lvi.pszText = (LPWSTR)wCurso.c_str();
    ListView_InsertItem(g_hListView, &lvi);
    
    std::wstring wGrupoId = StringToWString(curso.grupo_id);
    ListView_SetItemText(g_hListView, index, 1, (LPWSTR)wGrupoId.c_str());
    
    std::wstring wTipo = StringToWString(curso.tipo);
    ListView_SetItemText(g_hListView, index, 2, (LPWSTR)wTipo.c_str());
    
    std::wstring wAula = StringToWString(curso.aula);
    ListView_SetItemText(g_hListView, index, 3, (LPWSTR)wAula.c_str());
    
    std::wstring wHoras = StringToWString(curso.horas);
    ListView_SetItemText(g_hListView, index, 4, (LPWSTR)wHoras.c_str());
    
    std::wstring wDocente = StringToWString(curso.docente);
    ListView_SetItemText(g_hListView, index, 5, (LPWSTR)wDocente.c_str());
    
    std::wstring wCupos = std::to_wstring(curso.cupos);
    ListView_SetItemText(g_hListView, index, 6, (LPWSTR)wCupos.c_str());
    
    ListView_SetCheckState(g_hListView, index, curso.seleccionado);
}

void OnSelectAll() {
    for (size_t i = 0; i < g_cursos.size(); ++i) {
        g_cursos[i].seleccionado = true;
        ListView_SetCheckState(g_hListView, i, TRUE);
    }
}

void OnDeselectAll() {
    for (size_t i = 0; i < g_cursos.size(); ++i) {
        g_cursos[i].seleccionado = false;
        ListView_SetCheckState(g_hListView, i, FALSE);
    }
}

void OnAddCourse() {
    g_editingIndex = -1;
    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_COURSE_DIALOG), g_hMainWnd, CourseDialogProc);
}

void OnEditCourse() {
    int selectedItem = ListView_GetNextItem(g_hListView, -1, LVNI_SELECTED);
    if (selectedItem >= 0) {
        g_editingIndex = selectedItem;
        DialogBox(g_hInst, MAKEINTRESOURCE(IDD_COURSE_DIALOG), g_hMainWnd, CourseDialogProc);
    } else {
        MessageBox(g_hMainWnd, L"Seleccione un curso para editar", L"Aviso", MB_OK | MB_ICONINFORMATION);
    }
}

void OnDeleteCourse() {
    int selectedItem = ListView_GetNextItem(g_hListView, -1, LVNI_SELECTED);
    if (selectedItem >= 0) {
        int result = MessageBox(g_hMainWnd, L"¿Está seguro de que desea eliminar este curso?", 
                               L"Confirmar eliminación", MB_YESNO | MB_ICONQUESTION);
        if (result == IDYES) {
            g_cursos.erase(g_cursos.begin() + selectedItem);
            PopulateListView();
        }
    } else {
        MessageBox(g_hMainWnd, L"Seleccione un curso para eliminar", L"Aviso", MB_OK | MB_ICONINFORMATION);
    }
}

void OnExportCSV() {
    // Filtrar cursos seleccionados
    std::vector<CursoData> cursosSeleccionados;
    for (size_t i = 0; i < g_cursos.size(); ++i) {
        if (ListView_GetCheckState(g_hListView, i)) {
            cursosSeleccionados.push_back(g_cursos[i]);
        }
    }
    
    if (cursosSeleccionados.empty()) {
        MessageBox(g_hMainWnd, L"No hay cursos seleccionados para exportar", L"Aviso", MB_OK | MB_ICONINFORMATION);
        return;
    }
    
    // Diálogo para guardar archivo
    OPENFILENAME ofn;
    wchar_t szFile[260] = L"cursos_seleccionados.csv";
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_hMainWnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Archivos CSV\0*.csv\0Todos los archivos\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    
    if (GetSaveFileName(&ofn)) {
        std::string fileName = WStringToString(szFile);
        std::ofstream file(fileName);
        
        if (file.is_open()) {
            // Escribir cabecera
            file << "Curso,Grupo ID,Tipo,Aula,Horas,Docente,Cupos\n";
            
            // Escribir datos
            for (const auto& curso : cursosSeleccionados) {
                file << curso.curso << "," << curso.grupo_id << "," << curso.tipo << ","
                     << curso.aula << "," << curso.horas << "," << curso.docente << ","
                     << curso.cupos << "\n";
            }
            
            file.close();
            MessageBox(g_hMainWnd, L"Archivo CSV exportado exitosamente", L"Éxito", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(g_hMainWnd, L"Error al crear el archivo CSV", L"Error", MB_OK | MB_ICONERROR);
        }
    }
}

std::string WStringToString(const std::wstring& wstr) {
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, nullptr, nullptr);
    return str;
}

std::wstring StringToWString(const std::string& str) {
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size);
    return wstr;
}
