#!/bin/bash

# Script de compilación para el Sistema de Planificación de Horarios con Interfaz Web
# Autor: GitHub Copilot
# Fecha: Julio 2025

echo "=== Sistema de Planificación de Horarios con Interfaz Web ==="
echo ""

# Verificar que estamos en el directorio correcto
if [[ ! -f "src/main_interface.cpp" ]]; then
    echo "Error: No se encuentra src/main_interface.cpp"
    echo "Ejecuta este script desde el directorio raíz del proyecto"
    exit 1
fi

# Crear directorio bin si no existe
mkdir -p bin

echo "Compilando el sistema completo con interfaz web..."

# Compilar el programa principal con interfaz web
/usr/bin/g++-13 -std=c++17 -Iinclude -Wall \
    src/main_interface.cpp \
    src/Sistema.cpp \
    src/Curso.cpp \
    src/InterfazWeb.cpp \
    -o bin/planificador_web

# Verificar si la compilación fue exitosa
if [[ $? -eq 0 ]]; then
    echo "✅ Compilación exitosa"
    echo ""
    
    # Crear directorio web si no existe
    mkdir -p web
    
    # Verificar archivos de interfaz web
    if [[ -f "web/index.html" && -f "web/styles.css" && -f "web/script.js" ]]; then
        echo "✅ Archivos de interfaz web encontrados"
    else
        echo "⚠️  Algunos archivos de interfaz web no se encontraron"
        echo "Verifica que existan:"
        echo "  - web/index.html"
        echo "  - web/styles.css"
        echo "  - web/script.js"
    fi
    
    # Crear directorio data si no existe
    mkdir -p data
    
    echo ""
    echo "=== INSTRUCCIONES DE USO ==="
    echo ""
    echo "Para ejecutar el sistema:"
    echo "  ./bin/planificador_web"
    echo ""
    echo "El sistema ofrece dos modos:"
    echo "  1. Sistema básico (consola) - Usa archivos CSV existentes"
    echo "  2. Interfaz web - Permite ingresar datos manualmente"
    echo ""
    echo "=== ARCHIVOS NECESARIOS ==="
    echo ""
    echo "Para el sistema básico:"
    echo "  - data/ESPIS-cursos-2017.csv"
    echo "  - data/h2.csv"
    echo ""
    echo "Para la interfaz web:"
    echo "  - web/index.html"
    echo "  - web/styles.css"
    echo "  - web/script.js"
    echo ""
    echo "=== ARCHIVOS GENERADOS ==="
    echo ""
    echo "La interfaz web generará:"
    echo "  - data/grupos_horarios.csv (datos de grupos)"
    echo "  - data/preferencias_usuario.json (preferencias del usuario)"
    echo "  - data/resultados_horarios.txt (resultados de horarios)"
    echo ""
    
    # Ejecutar el programa
    echo "¿Desea ejecutar el programa ahora? (s/n): "
    read -r respuesta
    
    if [[ "$respuesta" == "s" || "$respuesta" == "S" ]]; then
        echo ""
        echo "Ejecutando el programa..."
        echo "========================"
        ./bin/planificador_web
    fi
    
else
    echo "❌ Error de compilación"
    echo ""
    echo "Posibles soluciones:"
    echo "1. Verificar que g++-13 esté instalado"
    echo "2. Verificar que todos los archivos fuente existan"
    echo "3. Revisar errores de sintaxis en el código"
    exit 1
fi

echo ""
echo "=== Fin del script ==="
