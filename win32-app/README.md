# Gestor de Cursos y Grupos - Aplicación Win32

Esta aplicación de escritorio permite gestionar cursos y grupos académicos, con funcionalidad para seleccionar y exportar datos a archivos CSV.

## Características

- **Interfaz nativa de Windows**: Utiliza la Win32 API para una experiencia nativa
- **Gestión de cursos**: Agregar, editar y eliminar cursos y grupos
- **Selección múltiple**: Checkboxes para seleccionar cursos específicos
- **Exportación a CSV**: Exportar cursos seleccionados a archivos CSV
- **Validación de datos**: Verificación de campos obligatorios
- **Interfaz intuitiva**: Botones y controles fáciles de usar

## Campos de datos

Cada curso contiene los siguientes campos:
- **Curso**: Código del curso (ej: 1703133)
- **Grupo ID**: Identificador del grupo (ej: 1, 2, 101)
- **Tipo**: Tipo de clase (TEORIA, LABORATORIO, PRACTICA)
- **Aula**: Salón donde se imparte la clase (ej: B201, Lab1)
- **Horas**: Horario de la clase (ej: L:08-10, M:14-16)
- **Docente**: Nombre del profesor
- **Cupos**: Número de estudiantes permitidos

## Compilación

### Requisitos
- MinGW-w64 o compilador compatible con Win32
- Windows SDK (para las librerías Win32)

### Compilar la aplicación
```bash
cd win32-app
make
```

### Limpiar archivos temporales
```bash
make clean
```

### Ejecutar la aplicación
```bash
make run
```

## Uso de la aplicación

### Ventana principal
1. **Lista de cursos**: Muestra todos los cursos con checkboxes para seleccionar
2. **Botones de control**:
   - **Seleccionar Todo**: Marca todos los cursos
   - **Deseleccionar Todo**: Desmarca todos los cursos
   - **Agregar Curso**: Abre el diálogo para agregar un nuevo curso
   - **Editar Curso**: Edita el curso seleccionado
   - **Eliminar Curso**: Elimina el curso seleccionado
   - **Exportar a CSV**: Exporta los cursos seleccionados a un archivo CSV

### Agregar/Editar cursos
1. Hacer clic en "Agregar Curso" o seleccionar un curso y hacer clic en "Editar Curso"
2. Completar todos los campos en el diálogo
3. Hacer clic en "Guardar" para confirmar los cambios

### Exportar a CSV
1. Seleccionar los cursos deseados marcando los checkboxes
2. Hacer clic en "Exportar a CSV"
3. Elegir la ubicación y nombre del archivo
4. El archivo se guardará con las columnas: Curso, Grupo ID, Tipo, Aula, Horas, Docente, Cupos

## Estructura del código

- **main.cpp**: Función principal y manejo de la ventana principal
- **dialog.cpp**: Funciones para el diálogo de agregar/editar cursos
- **resource.rc**: Definición del diálogo en formato de recursos
- **resource.h**: Constantes para los controles de la interfaz
- **Makefile**: Script de compilación

## Notas técnicas

- La aplicación usa controles nativos de Windows (ListView, ComboBox, EditText)
- Los datos se almacenan en memoria durante la ejecución
- La exportación CSV utiliza codificación UTF-8
- Los checkboxes están integrados en el ListView para facilitar la selección

## Datos de ejemplo

La aplicación incluye datos de ejemplo para demostrar su funcionalidad:
- Cursos 1703133, 1703134, 1703135
- Diferentes tipos de grupos (TEORIA, LABORATORIO)
- Horarios y aulas variadas
- Docentes y cupos asignados
