#include <windows.h>
#include <commctrl.h>
#include "curso_manager.h"
#include "resource.h"

// Incluir sistema principal
#include "../include/Sistema.hpp"
#include "../include/InterfazWinAPI.hpp"

// Variables globales
HINSTANCE hInst;
CursoManager* pCursoManager = nullptr;
Sistema* pSistema = nullptr;
InterfazWinAPI* pInterfazWinAPI = nullptr;

// Declaraciones de funciones
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    // Inicializar controles comunes
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);
    
    hInst = hInstance;
    
    MyRegisterClass(hInstance);
    
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }
    
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;
    
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"SistemaHorarios";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    
    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    HWND hWnd = CreateWindow(L"SistemaHorarios", L"Sistema de Gestión de Horarios - Checklist de Cursos",
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, 0, 850, 600,
                            nullptr, nullptr, hInstance, nullptr);
    
    if (!hWnd) {
        return FALSE;
    }
    
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            // Inicializar sistema principal
            pSistema = new Sistema();
            pInterfazWinAPI = new InterfazWinAPI(pSistema);
            pInterfazWinAPI->inicializar();
            
            // Inicializar curso manager con integración al sistema
            pCursoManager = new CursoManager(hWnd, pInterfazWinAPI);
            break;
            
        case WM_COMMAND:
            if (pCursoManager) {
                pCursoManager->HandleCommand(LOWORD(wParam));
            }
            break;
            
        case WM_NOTIFY:
            if (pCursoManager) {
                pCursoManager->HandleNotify((LPNMHDR)lParam);
            }
            break;
            
        case WM_SIZE:
            if (pCursoManager) {
                // Redimensionar ListView cuando cambie el tamaño de la ventana
                HWND hListView = pCursoManager->GetListViewHandle();
                if (hListView) {
                    MoveWindow(hListView, 10, 60, LOWORD(lParam) - 20, HIWORD(lParam) - 80, TRUE);
                }
            }
            break;
            
        case WM_DESTROY:
            if (pCursoManager) {
                delete pCursoManager;
                pCursoManager = nullptr;
            }
            if (pInterfazWinAPI) {
                delete pInterfazWinAPI;
                pInterfazWinAPI = nullptr;
            }
            if (pSistema) {
                delete pSistema;
                pSistema = nullptr;
            }
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
