#!/bin/bash

# Script de compilación para la aplicación WinAPI
# Sistema de Gestión de Horarios - Checklist de Cursos

echo "========================================="
echo "Compilando Sistema de Horarios - WinAPI"
echo "========================================="

# Verificar que estamos en el directorio correcto
if [ ! -f "main_winapi.cpp" ]; then
    echo "Error: No se encontró main_winapi.cpp"
    echo "Asegúrate de ejecutar este script desde el directorio win32-app"
    exit 1
fi

# Verificar que g++ está disponible
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ no está instalado"
    echo "Instala MinGW-w64 para compilar aplicaciones Windows"
    exit 1
fi

# Verificar que windres está disponible
if ! command -v windres &> /dev/null; then
    echo "Error: windres no está disponible"
    echo "Instala MinGW-w64 con las herramientas de recursos"
    exit 1
fi

# Limpiar archivos anteriores
echo "Limpiando archivos anteriores..."
rm -f *.o sistema_horarios_winapi.exe

# Compilar recursos
echo "Compilando recursos..."
windres -i resource.rc -o resource.o
if [ $? -ne 0 ]; then
    echo "Error al compilar recursos"
    exit 1
fi

# Compilar archivos fuente
echo "Compilando archivos fuente..."
g++ -std=c++17 -Wall -Wextra -O2 -DUNICODE -D_UNICODE -c main_winapi.cpp -o main_winapi.o
if [ $? -ne 0 ]; then
    echo "Error al compilar main_winapi.cpp"
    exit 1
fi

g++ -std=c++17 -Wall -Wextra -O2 -DUNICODE -D_UNICODE -c curso_manager.cpp -o curso_manager.o
if [ $? -ne 0 ]; then
    echo "Error al compilar curso_manager.cpp"
    exit 1
fi

# Enlazar el ejecutable
echo "Enlazando ejecutable..."
g++ -static-libgcc -static-libstdc++ -mwindows -o sistema_horarios_winapi.exe main_winapi.o curso_manager.o resource.o -lcomctl32 -lcomdlg32 -lshell32 -lole32 -luuid
if [ $? -ne 0 ]; then
    echo "Error al enlazar el ejecutable"
    exit 1
fi

echo "========================================="
echo "Compilación exitosa!"
echo "Ejecutable: sistema_horarios_winapi.exe"
echo "========================================="

# Verificar que el ejecutable existe
if [ -f "sistema_horarios_winapi.exe" ]; then
    echo "Tamaño del ejecutable: $(ls -lh sistema_horarios_winapi.exe | awk '{print $5}')"
    echo ""
    echo "Para ejecutar la aplicación:"
    echo "./sistema_horarios_winapi.exe"
    echo ""
    echo "o usando Wine en Linux:"
    echo "wine ./sistema_horarios_winapi.exe"
else
    echo "Error: El ejecutable no fue creado"
    exit 1
fi
