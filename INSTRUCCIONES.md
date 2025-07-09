# Instrucciones de Uso - Sistema de Planificación de Horarios

## Resumen del Proyecto

**Sistema de Planificación de Horarios (PSGraph)** es una aplicación en C++ que utiliza teoría de grafos para gestionar horarios académicos. El sistema detecta conflictos horarios entre grupos de cursos y genera horarios compatibles.

## Análisis del Código

### Arquitectura del Sistema

1. **Clases Principales**:
   - `Sistema`: Clase principal que coordina toda la funcionalidad
   - `Curso`: Representa un curso académico con sus datos básicos
   - `Grupo`: Representa un grupo específico de un curso con horario y docente
   - `Hora`: Representa una franja horaria específica (día, hora inicio, hora fin)
   - `Horario`: Representa una combinación de grupos compatibles
   - `Grafo<T>`: Implementación genérica de grafo con plantillas

2. **Funcionalidades Implementadas**:
   - Carga de datos desde archivos CSV
   - Construcción automática de grafo de compatibilidad
   - Detección de conflictos horarios
   - Generación de horarios válidos (implementación parcial)

### Archivos de Datos

El sistema utiliza dos archivos CSV principales:

1. **`data/ESPIS-cursos-2017.csv`**: Datos de cursos
   - Código, tipo, nombre, créditos, ciclo, prerrequisitos, horas
   
2. **`data/h2.csv`**: Datos de grupos y horarios
   - Curso, grupo_id, tipo, aula, horas, docente, cupos

### Flujo de Ejecución

1. **Carga de Cursos**: Lee el archivo CSV y crea objetos `Curso`
2. **Carga de Grupos**: Lee horarios y crea objetos `Grupo` asociados a cursos
3. **Construcción del Grafo**: Crea conexiones entre grupos compatibles
4. **Visualización**: Muestra el grafo de compatibilidad
5. **Generación de Horarios**: (Funcionalidad comentada en el código actual)

## Métodos de Ejecución

### Método 1: Script Automático (Recomendado)

```bash
# Ejecutar programa principal
./run.sh

# Ejecutar pruebas
./run_tests.sh
```

### Método 2: Compilación Manual

```bash
# Compilar programa principal
/usr/bin/g++-13 -std=c++17 -Iinclude -Wall src/main.cpp src/Sistema.cpp src/Curso.cpp -o bin/planificador

# Ejecutar
./bin/planificador

# Compilar pruebas
/usr/bin/g++-13 -std=c++17 -Iinclude -Wall tests/test_grafo.cpp -o bin/test_grafo

# Ejecutar pruebas
./bin/test_grafo
```

### Método 3: Usando CMake

```bash
mkdir -p build
cd build
cmake ..
make
./psgraph_main
```

### Método 4: Usando Makefile

```bash
make clean
make
./bin/planificador
```

## Salida del Programa

El programa actual muestra:

```
=== Grafo de Grupos y sus vecinos compatibles ===
Grupo: 1 | Curso: 1703133
Vecinos: 1703133:101 1703134:101 1703135:1 1703135:101 1703135:2 

Grupo: 2 | Curso: 1703133
Vecinos: 1703133:101 1703134:101 1703135:101 1703135:2 

[... más grupos ...]

Datos cargados correctamente.
```

## Características Técnicas

### Algoritmos Implementados

1. **Detección de Conflictos**: Compara franjas horarias para detectar solapamientos
2. **Grafo de Compatibilidad**: Crea conexiones entre grupos que no tienen conflictos
3. **Backtracking**: Algoritmo para generar combinaciones válidas (parcialmente implementado)

### Estructuras de Datos

- **Vector**: Para almacenar colecciones de objetos
- **Map/Unordered_map**: Para búsquedas rápidas por código
- **Grafo**: Implementación propia con lista de adyacencia

### Características del Grafo

- **Tipo**: No dirigido
- **Representación**: Lista de adyacencia
- **Plantillas**: Soporta cualquier tipo de dato como nodo
- **Algoritmos**: Detección de ciclos, componentes conexas, caminos

## Extensiones Posibles

### Funcionalidades Comentadas

En el código actual hay funcionalidades implementadas pero comentadas:

```cpp
//sistema.imprimirCursos();
//sistema.imprimirGrupos();
//sistema.generarHorarios(true);
//sistema.verHorarios();
```

### Para Activar Funcionalidades Adicionales

1. **Mostrar Cursos Cargados**:
   ```cpp
   sistema.imprimirCursos();
   ```

2. **Mostrar Grupos Cargados**:
   ```cpp
   sistema.imprimirGrupos();
   ```

3. **Generar Horarios Completos**:
   ```cpp
   sistema.generarHorarios(true);
   sistema.verHorarios();
   ```

## Solución de Problemas

### Errores Comunes

1. **"No se encuentra g++"**: Instalar compilador
   ```bash
   sudo apt install g++ build-essential
   ```

2. **"Error al abrir archivo"**: Verificar rutas de archivos CSV

3. **"Advertencias de compilación"**: Son normales, no afectan la funcionalidad

### Depuración

Para depurar el código:

```bash
/usr/bin/g++-13 -std=c++17 -Iinclude -Wall -g src/main.cpp src/Sistema.cpp src/Curso.cpp -o bin/planificador_debug
gdb ./bin/planificador_debug
```

## Datos de Prueba

El sistema incluye datos de prueba con:
- 3 cursos diferentes
- 9 grupos en total (3 por curso)
- Horarios con conflictos intencionados para probar la detección

## Próximos Pasos

1. **Activar generación de horarios completos**
2. **Implementar exportación de resultados**
3. **Agregar interfaz de usuario**
4. **Optimizar algoritmos de búsqueda**
5. **Agregar más validaciones de datos**

## Contacto

Este sistema fue desarrollado como parte del curso de Programación de Sistemas.
