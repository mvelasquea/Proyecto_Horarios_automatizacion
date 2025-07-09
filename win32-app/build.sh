#!/bin/bash
# Script de compilación para la aplicación Win32 en Linux usando MinGW

echo "=== Compilador de Gestor de Cursos Win32 ==="
echo "Verificando dependencias..."

# Verificar que MinGW esté instalado
if ! command -v x86_64-w64-mingw32-g++ &> /dev/null; then
    echo "Error: MinGW-w64 no está instalado."
    echo "Para instalar en Ubuntu/Debian: sudo apt install mingw-w64"
    echo "Para instalar en Fedora: sudo dnf install mingw64-gcc-c++"
    exit 1
fi

if ! command -v x86_64-w64-mingw32-windres &> /dev/null; then
    echo "Error: windres de MinGW no está disponible."
    exit 1
fi

echo "Dependencias verificadas ✓"

# Configurar variables
export CXX="x86_64-w64-mingw32-g++"
export WINDRES="x86_64-w64-mingw32-windres"

# Compilar usando make con variables de entorno
echo "Compilando aplicación Win32..."
make CXX="$CXX" WINDRES="$WINDRES"

if [ $? -eq 0 ]; then
    echo "=== Compilación exitosa ==="
    echo "Ejecutable generado: CursoManager.exe"
    echo "Para ejecutar en Windows, transfiera el archivo .exe"
    echo "Para probar con Wine (si está instalado): wine CursoManager.exe"
else
    echo "=== Error en la compilación ==="
    exit 1
fi
