#!/bin/bash

# Script para compilar la aplicación Win32 desde Linux
# Requiere MinGW-w64 instalado

echo "=== Compilando Sistema de Horarios Win32 ==="

# Verificar que MinGW-w64 esté instalado
if ! command -v x86_64-w64-mingw32-g++ &> /dev/null; then
    echo "Error: MinGW-w64 no está instalado"
    echo "Instalar con: sudo apt install gcc-mingw-w64"
    exit 1
fi

# Crear directorio de salida
mkdir -p ../bin

# Limpiar archivos anteriores
make clean

# Compilar la aplicación
echo "Compilando..."
make

if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa"
    echo "Ejecutable: SistemaHorarios.exe"
    
    # Verificar que el archivo se creó
    if [ -f "SistemaHorarios.exe" ]; then
        echo "📁 Archivo creado: $(ls -lh SistemaHorarios.exe)"
        
        # Copiar a bin
        cp SistemaHorarios.exe ../bin/
        echo "📦 Copiado a ../bin/"
        
        echo ""
        echo "🎉 Para ejecutar en Windows:"
        echo "   - Copiar SistemaHorarios.exe a una máquina Windows"
        echo "   - Ejecutar directamente (no requiere instalación)"
        echo "   - Funciona en Windows 7, 8, 10, 11"
    else
        echo "❌ Error: No se encontró el ejecutable"
        exit 1
    fi
else
    echo "❌ Error en la compilación"
    exit 1
fi
