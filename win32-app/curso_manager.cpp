#include "curso_manager.h"
#include <commdlg.h>
#include <algorithm>

CursoManager::CursoManager(HWND parentHwnd, InterfazWinAPI* interfaz) 
    : hWnd(parentHwnd), selectedIndex(-1), interfazWinAPI(interfaz) {
    
    // Cargar datos iniciales
    if (interfazWinAPI) {
        LoadFromSystem();
    } else {
        cursos = getCursosData();
    }
    
    // Inicializar controles comunes
    InitCommonControls();
    
    // Crear ListView
    hListView = CreateWindow(WC_LISTVIEW, L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
        10, 60, 780, 400,
        hWnd, (HMENU)IDC_LISTVIEW, GetModuleHandle(NULL), NULL);
    
    InitializeListView();
    PopulateListView();
    
    // Crear botones
    CreateWindow(L"BUTTON", L"Seleccionar Todo",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 10, 120, 30,
        hWnd, (HMENU)IDC_BTN_SELECT_ALL, GetModuleHandle(NULL), NULL);
    
    CreateWindow(L"BUTTON", L"Deseleccionar Todo",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        140, 10, 120, 30,
        hWnd, (HMENU)IDC_BTN_DESELECT_ALL, GetModuleHandle(NULL), NULL);
    
    CreateWindow(L"BUTTON", L"Agregar Curso",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        270, 10, 100, 30,
        hWnd, (HMENU)IDC_BTN_ADD_COURSE, GetModuleHandle(NULL), NULL);
    
    CreateWindow(L"BUTTON", L"Editar Curso",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        380, 10, 100, 30,
        hWnd, (HMENU)IDC_BTN_EDIT_COURSE, GetModuleHandle(NULL), NULL);
    
    CreateWindow(L"BUTTON", L"Eliminar Curso",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        490, 10, 100, 30,
        hWnd, (HMENU)IDC_BTN_DELETE_COURSE, GetModuleHandle(NULL), NULL);
    
    CreateWindow(L"BUTTON", L"Exportar CSV",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        600, 10, 100, 30,
        hWnd, (HMENU)IDC_BTN_EXPORT_CSV, GetModuleHandle(NULL), NULL);
}

CursoManager::~CursoManager() {
    // Limpiar recursos si es necesario
}

void CursoManager::InitializeListView() {
    // Configurar ListView con checkboxes
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    
    // Crear columnas
    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    
    // Columna 0: Curso
    lvc.iSubItem = 0;
    lvc.pszText = L"Curso";
    lvc.cx = 80;
    ListView_InsertColumn(hListView, 0, &lvc);
    
    // Columna 1: Nombre
    lvc.iSubItem = 1;
    lvc.pszText = L"Nombre";
    lvc.cx = 180;
    ListView_InsertColumn(hListView, 1, &lvc);
    
    // Columna 2: Grupo ID
    lvc.iSubItem = 2;
    lvc.pszText = L"Grupo";
    lvc.cx = 60;
    ListView_InsertColumn(hListView, 2, &lvc);
    
    // Columna 3: Tipo
    lvc.iSubItem = 3;
    lvc.pszText = L"Tipo";
    lvc.cx = 50;
    ListView_InsertColumn(hListView, 3, &lvc);
    
    // Columna 4: Aula
    lvc.iSubItem = 4;
    lvc.pszText = L"Aula";
    lvc.cx = 70;
    ListView_InsertColumn(hListView, 4, &lvc);
    
    // Columna 5: Horas
    lvc.iSubItem = 5;
    lvc.pszText = L"Horas";
    lvc.cx = 150;
    ListView_InsertColumn(hListView, 5, &lvc);
    
    // Columna 6: Docente
    lvc.iSubItem = 6;
    lvc.pszText = L"Docente";
    lvc.cx = 120;
    ListView_InsertColumn(hListView, 6, &lvc);
    
    // Columna 7: Cupos
    lvc.iSubItem = 7;
    lvc.pszText = L"Cupos";
    lvc.cx = 60;
    ListView_InsertColumn(hListView, 7, &lvc);
}

void CursoManager::PopulateListView() {
    ListView_DeleteAllItems(hListView);
    
    for (size_t i = 0; i < cursos.size(); ++i) {
        LVITEM lvi;
        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.iItem = i;
        lvi.iSubItem = 0;
        lvi.lParam = i;
        
        // Convertir strings a wide strings
        std::wstring wCurso(cursos[i].curso.begin(), cursos[i].curso.end());
        lvi.pszText = const_cast<LPWSTR>(wCurso.c_str());
        
        int itemIndex = ListView_InsertItem(hListView, &lvi);
        
        // Configurar checkbox
        ListView_SetCheckState(hListView, itemIndex, cursos[i].seleccionado);
        
        // Agregar subitems
        std::wstring wNombre(cursos[i].nombre.begin(), cursos[i].nombre.end());
        ListView_SetItemText(hListView, itemIndex, 1, const_cast<LPWSTR>(wNombre.c_str()));
        
        std::wstring wGrupo(cursos[i].grupo_id.begin(), cursos[i].grupo_id.end());
        ListView_SetItemText(hListView, itemIndex, 2, const_cast<LPWSTR>(wGrupo.c_str()));
        
        std::wstring wTipo(cursos[i].tipo.begin(), cursos[i].tipo.end());
        ListView_SetItemText(hListView, itemIndex, 3, const_cast<LPWSTR>(wTipo.c_str()));
        
        std::wstring wAula(cursos[i].aula.begin(), cursos[i].aula.end());
        ListView_SetItemText(hListView, itemIndex, 4, const_cast<LPWSTR>(wAula.c_str()));
        
        std::wstring wHoras(cursos[i].horas.begin(), cursos[i].horas.end());
        ListView_SetItemText(hListView, itemIndex, 5, const_cast<LPWSTR>(wHoras.c_str()));
        
        std::wstring wDocente(cursos[i].docente.begin(), cursos[i].docente.end());
        ListView_SetItemText(hListView, itemIndex, 6, const_cast<LPWSTR>(wDocente.c_str()));
        
        std::wstring wCupos = std::to_wstring(cursos[i].cupos);
        ListView_SetItemText(hListView, itemIndex, 7, const_cast<LPWSTR>(wCupos.c_str()));
    }
}

void CursoManager::UpdateListView() {
    int itemCount = ListView_GetItemCount(hListView);
    for (int i = 0; i < itemCount; ++i) {
        LVITEM lvi;
        lvi.mask = LVIF_PARAM;
        lvi.iItem = i;
        lvi.iSubItem = 0;
        ListView_GetItem(hListView, &lvi);
        
        size_t dataIndex = lvi.lParam;
        if (dataIndex < cursos.size()) {
            cursos[dataIndex].seleccionado = ListView_GetCheckState(hListView, i);
        }
    }
}

void CursoManager::SelectAllItems(bool select) {
    int itemCount = ListView_GetItemCount(hListView);
    for (int i = 0; i < itemCount; ++i) {
        ListView_SetCheckState(hListView, i, select);
    }
    
    for (auto& curso : cursos) {
        curso.seleccionado = select;
    }
}

void CursoManager::HandleCommand(WORD id) {
    switch (id) {
        case IDC_BTN_SELECT_ALL:
            SelectAllItems(true);
            break;
        case IDC_BTN_DESELECT_ALL:
            SelectAllItems(false);
            break;
        case IDC_BTN_ADD_COURSE:
            AddCourse();
            break;
        case IDC_BTN_EDIT_COURSE:
            EditCourse();
            break;
        case IDC_BTN_DELETE_COURSE:
            DeleteCourse();
            break;
        case IDC_BTN_EXPORT_CSV:
            ExportToCSV();
            break;
        case IDC_BTN_EDIT_COURSE:
            EditCourse();
            break;
        case IDC_BTN_DELETE_COURSE:
            DeleteCourse();
            break;
    }
}

void CursoManager::HandleNotify(LPNMHDR pnmh) {
    if (pnmh->hwndFrom == hListView) {
        switch (pnmh->code) {
            case LVN_ITEMCHANGED:
                {
                    LPNMLISTVIEW pnmlv = (LPNMLISTVIEW)pnmh;
                    if (pnmlv->uChanged & LVIF_STATE) {
                        if ((pnmlv->uOldState & LVIS_STATEIMAGEMASK) != (pnmlv->uNewState & LVIS_STATEIMAGEMASK)) {
                            UpdateListView();
                        }
                    }
                }
                break;
        }
    }
}

void CursoManager::AddCourse() {
    CursoData nuevoCurso("", "", "", "", "", "", "", 0);
    if (ShowCourseDialog(&nuevoCurso)) {
        cursos.push_back(nuevoCurso);
        PopulateListView();
        MessageBox(hWnd, L"Curso agregado exitosamente", L"Éxito", MB_OK | MB_ICONINFORMATION);
    }
}

void CursoManager::EditCourse() {
    int selectedItem = GetSelectedItemIndex();
    if (selectedItem == -1) {
        MessageBox(hWnd, L"Seleccione un curso para editar", L"Advertencia", MB_OK | MB_ICONWARNING);
        return;
    }
    
    LVITEM lvi;
    lvi.mask = LVIF_PARAM;
    lvi.iItem = selectedItem;
    lvi.iSubItem = 0;
    ListView_GetItem(hListView, &lvi);
    
    size_t dataIndex = lvi.lParam;
    if (dataIndex < cursos.size()) {
        if (ShowCourseDialog(&cursos[dataIndex])) {
            PopulateListView();
            MessageBox(hWnd, L"Curso actualizado exitosamente", L"Éxito", MB_OK | MB_ICONINFORMATION);
        }
    }
}

void CursoManager::DeleteCourse() {
    int selectedItem = GetSelectedItemIndex();
    if (selectedItem == -1) {
        MessageBox(hWnd, L"Seleccione un curso para eliminar", L"Advertencia", MB_OK | MB_ICONWARNING);
        return;
    }
    
    if (MessageBox(hWnd, L"¿Está seguro de eliminar este curso?", L"Confirmar", MB_YESNO | MB_ICONQUESTION) == IDYES) {
        LVITEM lvi;
        lvi.mask = LVIF_PARAM;
        lvi.iItem = selectedItem;
        lvi.iSubItem = 0;
        ListView_GetItem(hListView, &lvi);
        
        size_t dataIndex = lvi.lParam;
        if (dataIndex < cursos.size()) {
            cursos.erase(cursos.begin() + dataIndex);
            PopulateListView();
            MessageBox(hWnd, L"Curso eliminado exitosamente", L"Éxito", MB_OK | MB_ICONINFORMATION);
        }
    }
}

void CursoManager::ExportToCSV() {
    // Actualizar estados de selección
    UpdateListView();
    
    // Contar cursos seleccionados
    std::vector<CursoData> selectedCourses;
    for (const auto& curso : cursos) {
        if (curso.seleccionado) {
            selectedCourses.push_back(curso);
        }
    }
    
    if (selectedCourses.empty()) {
        MessageBox(hWnd, L"No hay cursos seleccionados", L"Advertencia", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // Mostrar diálogo de guardar archivo
    OPENFILENAME ofn;
    wchar_t szFile[260] = L"cursos_seleccionados.csv";
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"CSV Files\0*.csv\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    
    if (GetSaveFileName(&ofn)) {
        // Convertir wide string a string
        std::string filename;
        int size = WideCharToMultiByte(CP_UTF8, 0, szFile, -1, NULL, 0, NULL, NULL);
        filename.resize(size);
        WideCharToMultiByte(CP_UTF8, 0, szFile, -1, &filename[0], size, NULL, NULL);
        filename.resize(size - 1); // Quitar null terminator
        
        // Crear archivo CSV
        std::ofstream file(filename);
        if (file.is_open()) {
            // Escribir encabezados
            file << "curso,nombre,grupo_id,tipo,aula,horas,docente,cupos\n";
            
            // Escribir datos
            for (const auto& curso : selectedCourses) {
                file << curso.curso << ","
                     << "\"" << curso.nombre << "\","
                     << curso.grupo_id << ","
                     << curso.tipo << ","
                     << curso.aula << ","
                     << "\"" << curso.horas << "\","
                     << "\"" << curso.docente << "\","
                     << curso.cupos << "\n";
            }
            
            file.close();
            
            std::wstring mensaje = L"Exportados " + std::to_wstring(selectedCourses.size()) + L" cursos a CSV";
            MessageBox(hWnd, mensaje.c_str(), L"Éxito", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(hWnd, L"Error al crear el archivo", L"Error", MB_OK | MB_ICONERROR);
        }
    }
}

int CursoManager::GetSelectedItemIndex() {
    return ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
}

bool CursoManager::ShowCourseDialog(CursoData* curso) {
    selectedIndex = -1;
    if (curso) {
        // Buscar el índice del curso en el vector
        for (size_t i = 0; i < cursos.size(); ++i) {
            if (&cursos[i] == curso) {
                selectedIndex = i;
                break;
            }
        }
    }
    
    INT_PTR result = DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CURSO_DIALOG), 
                                   hWnd, CourseDialogProc, (LPARAM)this);
    
    return (result == IDOK);
}

INT_PTR CALLBACK CursoManager::CourseDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    static CursoManager* pThis = nullptr;
    
    switch (message) {
        case WM_INITDIALOG:
            {
                pThis = (CursoManager*)lParam;
                
                // Llenar combo de tipo
                HWND hComboTipo = GetDlgItem(hDlg, IDC_COMBO_TIPO);
                SendMessage(hComboTipo, CB_ADDSTRING, 0, (LPARAM)L"F");
                SendMessage(hComboTipo, CB_ADDSTRING, 0, (LPARAM)L"L");
                SendMessage(hComboTipo, CB_SETCURSEL, 0, 0);
                
                // Si estamos editando, llenar los campos
                if (pThis->selectedIndex >= 0) {
                    const CursoData& curso = pThis->cursos[pThis->selectedIndex];
                    
                    SetDlgItemTextA(hDlg, IDC_EDIT_CURSO, curso.curso.c_str());
                    SetDlgItemTextA(hDlg, IDC_EDIT_NOMBRE, curso.nombre.c_str());
                    SetDlgItemTextA(hDlg, IDC_EDIT_GRUPO_ID, curso.grupo_id.c_str());
                    SetDlgItemTextA(hDlg, IDC_EDIT_AULA, curso.aula.c_str());
                    SetDlgItemTextA(hDlg, IDC_EDIT_HORAS, curso.horas.c_str());
                    SetDlgItemTextA(hDlg, IDC_EDIT_DOCENTE, curso.docente.c_str());
                    SetDlgItemInt(hDlg, IDC_EDIT_CUPOS, curso.cupos, FALSE);
                    
                    // Seleccionar tipo
                    if (curso.tipo == "F") {
                        SendMessage(hComboTipo, CB_SETCURSEL, 0, 0);
                    } else if (curso.tipo == "L") {
                        SendMessage(hComboTipo, CB_SETCURSEL, 1, 0);
                    }
                }
                
                return TRUE;
            }
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_BTN_OK:
                    {
                        // Obtener datos del formulario
                        char buffer[256];
                        
                        GetDlgItemTextA(hDlg, IDC_EDIT_CURSO, buffer, sizeof(buffer));
                        std::string curso(buffer);
                        
                        GetDlgItemTextA(hDlg, IDC_EDIT_NOMBRE, buffer, sizeof(buffer));
                        std::string nombre(buffer);
                        
                        GetDlgItemTextA(hDlg, IDC_EDIT_GRUPO_ID, buffer, sizeof(buffer));
                        std::string grupo_id(buffer);
                        
                        GetDlgItemTextA(hDlg, IDC_EDIT_AULA, buffer, sizeof(buffer));
                        std::string aula(buffer);
                        
                        GetDlgItemTextA(hDlg, IDC_EDIT_HORAS, buffer, sizeof(buffer));
                        std::string horas(buffer);
                        
                        GetDlgItemTextA(hDlg, IDC_EDIT_DOCENTE, buffer, sizeof(buffer));
                        std::string docente(buffer);
                        
                        int cupos = GetDlgItemInt(hDlg, IDC_EDIT_CUPOS, NULL, FALSE);
                        
                        // Obtener tipo del combo
                        HWND hComboTipo = GetDlgItem(hDlg, IDC_COMBO_TIPO);
                        int tipoIndex = SendMessage(hComboTipo, CB_GETCURSEL, 0, 0);
                        std::string tipo = (tipoIndex == 0) ? "F" : "L";
                        
                        // Validar campos
                        if (curso.empty() || nombre.empty() || grupo_id.empty() || aula.empty() || 
                            horas.empty() || docente.empty() || cupos <= 0) {
                            MessageBox(hDlg, L"Todos los campos son obligatorios", L"Error", MB_OK | MB_ICONERROR);
                            return TRUE;
                        }
                        
                        // Actualizar o crear curso
                        if (pThis->selectedIndex >= 0) {
                            // Editando
                            CursoData& cursoData = pThis->cursos[pThis->selectedIndex];
                            cursoData.curso = curso;
                            cursoData.nombre = nombre;
                            cursoData.grupo_id = grupo_id;
                            cursoData.tipo = tipo;
                            cursoData.aula = aula;
                            cursoData.horas = horas;
                            cursoData.docente = docente;
                            cursoData.cupos = cupos;
                        } else {
                            // Agregando nuevo
                            pThis->cursos.push_back(CursoData(curso, nombre, grupo_id, tipo, aula, horas, docente, cupos));
                        }
                        
                        EndDialog(hDlg, IDOK);
                        return TRUE;
                    }
                    
                case IDC_BTN_CANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            break;
            
        case WM_CLOSE:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
    }
    
    return FALSE;
}

void CursoManager::SyncWithSystem() {
    if (!interfazWinAPI) return;
    
    // Actualizar estados de selección en el sistema
    for (size_t i = 0; i < cursos.size(); ++i) {
        interfazWinAPI->marcarSeleccionado(i, cursos[i].seleccionado);
    }
    
    // Sincronizar con el sistema principal
    interfazWinAPI->sincronizarConSistema();
}

void CursoManager::LoadFromSystem() {
    if (!interfazWinAPI) return;
    
    // Cargar datos del sistema
    const auto& cursosWinAPI = interfazWinAPI->getCursosWinAPI();
    
    cursos.clear();
    for (const auto& cursoWin : cursosWinAPI) {
        cursos.emplace_back(cursoWin.curso, cursoWin.nombre, cursoWin.grupo_id,
                           cursoWin.tipo, cursoWin.aula, cursoWin.horas,
                           cursoWin.docente, cursoWin.cupos, cursoWin.seleccionado);
    }
}

void CursoManager::RefreshFromSystem() {
    LoadFromSystem();
    PopulateListView();
}
