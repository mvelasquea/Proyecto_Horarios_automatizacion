#!/bin/bash

# Script para ejecutar las pruebas del Sistema de Planificación de Horarios
# Autor: GitHub Copilot
# Fecha: Julio 2025

echo "=== Ejecutando Pruebas del Sistema PSGraph ==="
echo ""

# Verificar que estamos en el directorio correcto
if [[ ! -f "tests/test_grafo.cpp" ]]; then
    echo "Error: No se encuentra tests/test_grafo.cpp"
    echo "Ejecuta este script desde el directorio raíz del proyecto"
    exit 1
fi

# Crear directorio bin si no existe
mkdir -p bin

# Compilar las pruebas
echo "Compilando pruebas..."
/usr/bin/g++-13 -std=c++17 -Iinclude -Wall tests/test_grafo.cpp -o bin/test_grafo

# Verificar si la compilación fue exitosa
if [[ $? -eq 0 ]]; then
    echo "✅ Compilación de pruebas exitosa"
    echo ""
    
    # Ejecutar las pruebas
    echo "Ejecutando pruebas del grafo..."
    echo "==============================="
    ./bin/test_grafo
    
    # Verificar si la ejecución fue exitosa
    if [[ $? -eq 0 ]]; then
        echo ""
        echo "✅ Todas las pruebas completadas exitosamente"
    else
        echo ""
        echo "❌ Error durante la ejecución de las pruebas"
        exit 1
    fi
else
    echo "❌ Error de compilación de las pruebas"
    exit 1
fi

echo ""
echo "=== Fin de las pruebas ==="
