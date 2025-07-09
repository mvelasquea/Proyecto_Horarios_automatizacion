#!/bin/bash

# Script de compilación y ejecución para el Sistema de Planificación de Horarios
# Autor: GitHub Copilot
# Fecha: Julio 2025

echo "=== Sistema de Planificación de Horarios (PSGraph) ==="
echo ""

# Verificar que estamos en el directorio correcto
if [[ ! -f "src/main.cpp" ]]; then
    echo "Error: No se encuentra src/main.cpp"
    echo "Ejecuta este script desde el directorio raíz del proyecto"
    exit 1
fi

# Crear directorio bin si no existe
mkdir -p bin

# Compilar el proyecto
echo "Compilando el proyecto..."
/usr/bin/g++-13 -std=c++17 -Iinclude -Wall src/main.cpp src/Sistema.cpp src/Curso.cpp -o bin/planificador

# Verificar si la compilación fue exitosa
if [[ $? -eq 0 ]]; then
    echo "✅ Compilación exitosa"
    echo ""
    
    # Ejecutar el programa
    echo "Ejecutando el programa..."
    echo "========================"
    ./bin/planificador
    
    # Verificar si la ejecución fue exitosa
    if [[ $? -eq 0 ]]; then
        echo ""
        echo "✅ Ejecución completada exitosamente"
    else
        echo ""
        echo "❌ Error durante la ejecución"
        exit 1
    fi
else
    echo "❌ Error de compilación"
    exit 1
fi

echo ""
echo "=== Fin del programa ==="
