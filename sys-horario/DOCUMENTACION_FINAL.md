# Interfaz de Gestión de Cursos - Documentación Final

## Resumen del Proyecto

Se ha implementado una interfaz completa para ingresar, gestionar y exportar datos de cursos y grupos académicos, con las siguientes características principales:

### 1. Interfaz Web (HTML/CSS/JavaScript)
- **Ubicación**: `/home/miku/Proyecto Psis Horarios/sys-horario/web/`
- **Funcionalidades**:
  - Formulario modal para agregar/editar cursos
  - Tabla con checkboxes para seleccionar cursos
  - Botones para seleccionar/deseleccionar todos
  - Exportación directa a CSV desde el navegador

### 2. Aplicación Win32 (C++)
- **Ubicación**: `/home/miku/Proyecto Psis Horarios/sys-horario/win32-app/`
- **Funcionalidades**:
  - Interfaz nativa de Windows usando Win32 API
  - ListView con checkboxes integrados
  - Diálogo modal para agregar/editar cursos
  - Exportación a CSV con diálogo de guardado

### 3. Versión de Consola (C++)
- **Ubicación**: `/home/miku/Proyecto Psis Horarios/sys-horario/win32-app/console_version.cpp`
- **Funcionalidades**:
  - Interfaz de texto interactiva
  - Menú principal con todas las opciones
  - Funcionalidad completa de gestión y exportación

## Campos de Datos Implementados

Cada curso/grupo contiene los siguientes campos requeridos:
- **Curso**: Código del curso (ej: 1703133)
- **Grupo ID**: Identificador del grupo (ej: 1, 2, 101)
- **Tipo**: Tipo de clase (TEORIA, LABORATORIO, PRACTICA)
- **Aula**: Salón donde se imparte la clase (ej: B201, Lab1)
- **Horas**: Horario de la clase (ej: L:08-10, M:14-16)
- **Docente**: Nombre del profesor
- **Cupos**: Número de estudiantes permitidos

## Funcionalidades Implementadas

### ✅ Gestión de Datos
- [x] Agregar nuevos cursos/grupos
- [x] Editar cursos existentes
- [x] Eliminar cursos
- [x] Validación de campos obligatorios

### ✅ Selección y Checklist
- [x] Checkboxes para cada curso/grupo
- [x] Seleccionar todos los cursos
- [x] Deseleccionar todos los cursos
- [x] Selección individual

### ✅ Exportación
- [x] Exportar cursos seleccionados a CSV
- [x] Incluir cabeceras en el archivo CSV
- [x] Formato CSV estándar con comillas para texto

### ✅ Interfaz de Usuario
- [x] Interfaz web moderna y responsiva
- [x] Aplicación nativa de Windows
- [x] Versión de consola para Linux
- [x] Validación de entrada de datos

## Archivos Creados

### Interfaz Web
- `web/index.html` - Página principal
- `web/styles.css` - Estilos CSS
- `web/script.js` - Lógica JavaScript

### Aplicación Win32
- `win32-app/main.cpp` - Función principal y ventana
- `win32-app/dialog.cpp` - Diálogo de agregar/editar
- `win32-app/resource.rc` - Recursos de la interfaz
- `win32-app/resource.h` - Constantes de controles
- `win32-app/common.h` - Definiciones compartidas
- `win32-app/Makefile` - Script de compilación
- `win32-app/build.sh` - Script de compilación para Linux
- `win32-app/README.md` - Documentación detallada

### Versión de Consola
- `win32-app/console_version.cpp` - Versión de consola completa
- `win32-app/Makefile.console` - Compilación para consola

## Instrucciones de Uso

### Interfaz Web
1. Abrir `web/index.html` en un navegador
2. Usar el botón "Agregar Curso" para añadir datos
3. Seleccionar cursos con checkboxes
4. Exportar con "Exportar Seleccionados a CSV"

### Aplicación Win32
1. Compilar con MinGW: `./build.sh` (requiere MinGW-w64)
2. Ejecutar `CursoManager.exe` en Windows
3. Usar la interfaz gráfica nativa

### Versión de Consola
1. Compilar: `make -f Makefile.console`
2. Ejecutar: `./curso_manager_console`
3. Navegar con el menú interactivo

## Datos de Ejemplo

Todas las versiones incluyen datos de ejemplo:
- 6 cursos/grupos diferentes
- Variedad de tipos (TEORIA, LABORATORIO)
- Horarios realistas
- Docentes y aulas asignadas

## Compatibilidad

- **Web**: Cualquier navegador moderno
- **Win32**: Windows 7+ (compilado con MinGW-w64)
- **Consola**: Linux, macOS, Windows (con compilador C++)

## Tecnologías Utilizadas

- **Web**: HTML5, CSS3, JavaScript ES6+
- **Win32**: C++11, Win32 API, Common Controls
- **Consola**: C++11 estándar, STL
- **Herramientas**: Make, MinGW-w64, windres

## Características Destacadas

1. **Validación robusta**: Todos los campos son validados
2. **Interfaz intuitiva**: Fácil de usar en todas las versiones
3. **Exportación estándar**: CSV compatible con Excel y otros
4. **Multiplataforma**: Funciona en diferentes sistemas
5. **Código limpio**: Bien estructurado y documentado

## Próximos Pasos Posibles

- [ ] Persistencia de datos (archivo, base de datos)
- [ ] Importación desde CSV
- [ ] Filtros y búsqueda
- [ ] Reportes más avanzados
- [ ] Integración con el sistema principal de horarios

## Conclusión

Se ha implementado exitosamente una interfaz completa para la gestión de cursos y grupos con exportación a CSV, disponible en tres versiones (web, Win32 y consola) para máxima compatibilidad y usabilidad.
