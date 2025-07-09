# Makefile para la aplicación Win32 de Gestor de Cursos
# Compilador y flags
CXX ?= x86_64-w64-mingw32-g++
WINDRES ?= x86_64-w64-mingw32-windres
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -DUNICODE -D_UNICODE -I../include
LDFLAGS = -mwindows -static-libgcc -static-libstdc++

# Librerías necesarias
LIBS = -lcomctl32 -lcomdlg32 -luser32 -lkernel32 -lgdi32 -lshell32

# Archivos fuente y objeto
SOURCES = main_winapi.cpp curso_manager.cpp
SYSTEM_SOURCES = ../src/InterfazWinAPI.cpp ../src/Sistema.cpp ../src/Curso.cpp ../src/Exportador.cpp
OBJECTS = $(SOURCES:.cpp=.o) $(SYSTEM_SOURCES:.cpp=.o)
RESOURCE_OBJ = resource.o
HEADERS = curso_manager.h curso_data.h resource.h ../include/InterfazWinAPI.hpp

# Ejecutable de salida
TARGET = SistemaHorarios.exe

# Regla principal
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJECTS) $(RESOURCE_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compilar archivos fuente del directorio actual
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar archivos fuente del sistema principal
../src/%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar recursos
$(RESOURCE_OBJ): resource.rc resource.h
	$(WINDRES) resource.rc -o $(RESOURCE_OBJ)

# Limpiar archivos temporales
clean:
	rm -f $(OBJECTS) $(RESOURCE_OBJ) $(TARGET) ../src/*.o

# Instalar (copiar a directorio de salida)
install: $(TARGET)
	cp $(TARGET) ../bin/

# Ejecutar la aplicación
run: $(TARGET)
	./$(TARGET)

# Compilar versión de debug
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Reglas especiales
.PHONY: all clean install run debug
