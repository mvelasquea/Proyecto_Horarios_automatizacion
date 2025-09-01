# Sistema de Gestión de Horarios - Integración Win API

## Resumen de Cambios

Se ha integrado exitosamente la funcionalidad Win API con el sistema principal manteniendo la funcionalidad completa del gestor de cursos y grupos del `index.html`.

## Funcionalidades Integradas

### 1. **Interfaz Web (index.html)**
- **Funcionalidad mantenida**: Gestor de cursos y grupos completo
- **Nuevas características**:
  - Puente automático con Win API cuando está disponible
  - Fallback a funcionalidad web pura
  - Sincronización automática de datos

### 2. **Aplicación Win32**
- **Interfaz nativa de Windows**: Usando Win32 API
- **Funcionalidad completa**:
  - Gestión de cursos y grupos
  - Selección múltiple con checkboxes
  - Exportación a CSV con diálogo nativo
  - Agregar/editar/eliminar cursos
  - Validación de datos
  - Integración con sistema principal

### 3. **Sistema Principal**
- **Clase InterfazWinAPI**: Puente entre Win API y sistema core
- **Sincronización de datos**: Bidireccional entre web y Win32
- **Validación unificada**: Mismas reglas en ambas interfaces

## Estructura del Proyecto

```
sys-horario/
├── include/
│   ├── InterfazWinAPI.hpp     # Nuevo: Puente Win API
│   └── ...existing headers...
├── src/
│   ├── InterfazWinAPI.cpp     # Nuevo: Implementación puente
│   └── ...existing sources...
├── web/
│   ├── index.html             # Modificado: Incluye puente Win API
│   ├── winapi_bridge.js       # Nuevo: Puente JavaScript
│   └── ...existing web files...
├── win32-app/
│   ├── main_winapi.cpp        # Modificado: Integración con sistema
│   ├── curso_manager.h        # Modificado: Soporte sistema principal
│   ├── curso_manager.cpp      # Modificado: Funciones integradas
│   ├── build_windows.sh       # Nuevo: Script compilación
│   └── Makefile               # Modificado: Compilación integrada
└── .vscode/
    └── tasks.json             # Nuevo: Tareas automatizadas
```

## Compilación

### Requisitos
- **Linux**: Para desarrollo principal
- **MinGW-w64**: Para compilación Win32
- **VS Code**: Para desarrollo integrado

### Instalación de dependencias
```bash
# Ubuntu/Debian
sudo apt install gcc-mingw-w64

# Fedora/CentOS
sudo dnf install mingw64-gcc-c++
```

### Compilar todo el sistema
```bash
# Opción 1: Desde VS Code
Ctrl+Shift+P > Tasks: Run Task > "Compilar Todo"

# Opción 2: Desde terminal
make                           # Sistema principal
cd win32-app && ./build_windows.sh  # Aplicación Win32
```

## Uso

### 1. **Interfaz Web**
```bash
# Iniciar servidor web
cd web
python3 -m http.server 8000

# Abrir navegador
http://localhost:8000
```

**Características**:
- Funcionalidad completa mantenida
- Detección automática de Win API
- Sincronización transparente

### 2. **Aplicación Win32**
```bash
# Ejecutar en Windows
./win32-app/SistemaHorarios.exe
```

**Características**:
- Interfaz nativa de Windows
- Diálogos nativos para archivos
- Rendimiento optimizado
- Integración con sistema principal

## Funcionalidades Compartidas

### Gestión de Cursos
- ✅ Agregar nuevos cursos
- ✅ Editar cursos existentes
- ✅ Eliminar cursos
- ✅ Validación de datos
- ✅ Selección múltiple

### Exportación
- ✅ Exportar cursos seleccionados a CSV
- ✅ Formato estándar compatible
- ✅ Validación de selección
- ✅ Manejo de errores

### Datos Soportados
- **Curso**: Código del curso (ej: 1703133)
- **Nombre**: Nombre completo del curso
- **Grupo ID**: Identificador del grupo
- **Tipo**: TEORIA, LABORATORIO, PRACTICA
- **Aula**: Salón asignado
- **Horas**: Horario (formato: L:08-10, M:14-16)
- **Docente**: Nombre del profesor
- **Cupos**: Número de estudiantes

## Integración Técnica

### Puente Web-WinAPI
```javascript
// Detección automática
if (window.external && window.external.invokeWinAPI) {
    // Usar funcionalidad Win API
    window.external.invokeWinAPI('exportToCSV', data);
} else {
    // Usar funcionalidad web
    downloadCSV(data);
}
```

### Sincronización de Datos
```cpp
// En InterfazWinAPI
void sincronizarConSistema() {
    auto cursos = convertirACursos(cursosWinAPI);
    // Sincronizar con sistema principal
}
```

## Archivos Importantes

### Nuevos Archivos
- `include/InterfazWinAPI.hpp` - Interfaz para integración Win API
- `src/InterfazWinAPI.cpp` - Implementación de integración
- `web/winapi_bridge.js` - Puente JavaScript
- `win32-app/build_windows.sh` - Script de compilación
- `.vscode/tasks.json` - Tareas automatizadas

### Archivos Modificados
- `web/index.html` - Incluye puente Win API
- `win32-app/main_winapi.cpp` - Integración con sistema
- `win32-app/curso_manager.h` - Soporte sistema principal
- `win32-app/curso_manager.cpp` - Funciones integradas
- `win32-app/Makefile` - Compilación integrada

## Tareas VS Code

- **Compilar Sistema Principal**: Compila el sistema core
- **Compilar Win32 App**: Compila la aplicación Windows
- **Compilar Todo**: Compila ambos sistemas
- **Ejecutar Tests**: Ejecuta pruebas unitarias
- **Iniciar Servidor Web**: Inicia servidor de desarrollo
- **Limpiar Compilaciones**: Limpia archivos temporales

## Notas Técnicas

### Compatibilidad
- **Web**: Funciona en todos los navegadores modernos
- **Win32**: Compatible con Windows 7, 8, 10, 11
- **Integración**: Automática y transparente

### Rendimiento
- **Web**: Optimizado para interactividad
- **Win32**: Rendimiento nativo de Windows
- **Datos**: Sincronización eficiente

### Mantenimiento
- **Funcionalidad web**: Completamente preservada
- **Código nuevo**: Bien documentado y modular
- **Pruebas**: Compatibles con ambos sistemas

## Conclusión

La integración Win API ha sido exitosa manteniendo:
- ✅ **Funcionalidad completa** del index.html
- ✅ **Compatibilidad** con sistemas existentes
- ✅ **Rendimiento** optimizado
- ✅ **Experiencia de usuario** mejorada
- ✅ **Mantenibilidad** del código

El sistema ahora ofrece tanto la flexibilidad de la interfaz web como el rendimiento y funcionalidad nativa de Windows.
