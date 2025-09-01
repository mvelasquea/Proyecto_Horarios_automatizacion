#!/bin/bash

# Script de prueba para verificar integración Win API
echo "=== Prueba de Integración Win API ==="
echo "Fecha: $(date)"
echo ""

# Variables de colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Función para mostrar resultados
check_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✅ $2${NC}"
    else
        echo -e "${RED}❌ $2${NC}"
    fi
}

# Función para mostrar información
info() {
    echo -e "${YELLOW}ℹ️  $1${NC}"
}

# 1. Verificar estructura del proyecto
info "Verificando estructura del proyecto..."

# Verificar archivos principales
files_to_check=(
    "include/InterfazWinAPI.hpp"
    "src/InterfazWinAPI.cpp"
    "web/winapi_bridge.js"
    "win32-app/main_winapi.cpp"
    "win32-app/curso_manager.h"
    "win32-app/curso_manager.cpp"
    "win32-app/build_windows.sh"
    ".vscode/tasks.json"
)

for file in "${files_to_check[@]}"; do
    if [ -f "$file" ]; then
        check_result 0 "Archivo $file existe"
    else
        check_result 1 "Archivo $file NO existe"
    fi
done

echo ""

# 2. Verificar dependencias
info "Verificando dependencias..."

# Verificar compilador principal
if command -v g++ &> /dev/null; then
    check_result 0 "g++ está disponible"
else
    check_result 1 "g++ NO está disponible"
fi

# Verificar MinGW-w64
if command -v x86_64-w64-mingw32-g++ &> /dev/null; then
    check_result 0 "MinGW-w64 está disponible"
else
    check_result 1 "MinGW-w64 NO está disponible (sudo apt install gcc-mingw-w64)"
fi

echo ""

# 3. Probar compilación del sistema principal
info "Probando compilación del sistema principal..."

if make clean > /dev/null 2>&1; then
    check_result 0 "Limpieza exitosa"
else
    check_result 1 "Error en limpieza"
fi

if make > /dev/null 2>&1; then
    check_result 0 "Compilación del sistema principal exitosa"
else
    check_result 1 "Error en compilación del sistema principal"
fi

echo ""

# 4. Probar compilación Win32
info "Probando compilación Win32..."

cd win32-app

if [ -f "build_windows.sh" ]; then
    chmod +x build_windows.sh
    if ./build_windows.sh > /dev/null 2>&1; then
        check_result 0 "Compilación Win32 exitosa"
        
        if [ -f "SistemaHorarios.exe" ]; then
            check_result 0 "Ejecutable Win32 creado"
            echo "   📊 Tamaño: $(ls -lh SistemaHorarios.exe | awk '{print $5}')"
        else
            check_result 1 "Ejecutable Win32 NO creado"
        fi
    else
        check_result 1 "Error en compilación Win32"
    fi
else
    check_result 1 "Script build_windows.sh NO encontrado"
fi

cd ..

echo ""

# 5. Verificar interfaz web
info "Verificando interfaz web..."

if [ -f "web/index.html" ]; then
    check_result 0 "index.html existe"
    
    # Verificar que incluye el puente Win API
    if grep -q "winapi_bridge.js" web/index.html; then
        check_result 0 "Puente Win API incluido en index.html"
    else
        check_result 1 "Puente Win API NO incluido en index.html"
    fi
else
    check_result 1 "index.html NO existe"
fi

if [ -f "web/winapi_bridge.js" ]; then
    check_result 0 "winapi_bridge.js existe"
else
    check_result 1 "winapi_bridge.js NO existe"
fi

echo ""

# 6. Verificar configuración VS Code
info "Verificando configuración VS Code..."

if [ -f ".vscode/tasks.json" ]; then
    check_result 0 "tasks.json existe"
    
    # Verificar que incluye tareas Win32
    if grep -q "Compilar Win32 App" .vscode/tasks.json; then
        check_result 0 "Tareas Win32 configuradas"
    else
        check_result 1 "Tareas Win32 NO configuradas"
    fi
else
    check_result 1 "tasks.json NO existe"
fi

echo ""

# 7. Prueba de datos de ejemplo
info "Verificando datos de ejemplo..."

if [ -f "data/cursos.csv" ]; then
    check_result 0 "Archivo de datos existe"
    
    lines=$(wc -l < data/cursos.csv)
    echo "   📊 Líneas en cursos.csv: $lines"
else
    check_result 1 "Archivo de datos NO existe"
fi

echo ""

# 8. Resumen final
info "Resumen de la integración..."

echo ""
echo "🎯 Funcionalidades integradas:"
echo "   • Gestor de cursos y grupos (index.html) - Funcionalidad mantenida"
echo "   • Aplicación Win32 nativa - Nueva funcionalidad"
echo "   • Puente JavaScript Web-WinAPI - Nueva funcionalidad"
echo "   • Sincronización automática de datos - Nueva funcionalidad"
echo "   • Compilación cross-platform - Nueva funcionalidad"
echo "   • Tareas automatizadas VS Code - Nueva funcionalidad"

echo ""
echo "📋 Para usar el sistema:"
echo "   1. Interfaz Web: cd web && python3 -m http.server 8000"
echo "   2. Aplicación Win32: Ejecutar SistemaHorarios.exe en Windows"
echo "   3. VS Code: Ctrl+Shift+P > Tasks: Run Task"

echo ""
echo "🔧 Comandos útiles:"
echo "   • make                    - Compilar sistema principal"
echo "   • ./win32-app/build_windows.sh - Compilar Win32"
echo "   • make clean             - Limpiar compilaciones"
echo "   • make test              - Ejecutar pruebas"

echo ""
if [ -f "win32-app/SistemaHorarios.exe" ]; then
    echo -e "${GREEN}🎉 Integración Win API completada exitosamente!${NC}"
else
    echo -e "${YELLOW}⚠️  Integración parcial - Revisar errores de compilación${NC}"
fi

echo ""
echo "📖 Ver INTEGRACION_WINAPI.md para documentación completa"
