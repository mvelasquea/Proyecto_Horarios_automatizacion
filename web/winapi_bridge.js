// Puente entre interfaz web y Win API
// Este archivo maneja la comunicación entre el frontend web y el backend Win API

class WebWinAPIBridge {
    constructor() {
        this.cursosData = [];
        this.isWinAPIAvailable = this.checkWinAPIAvailability();
        this.initializeEventHandlers();
    }

    checkWinAPIAvailability() {
        // Verificar si estamos ejecutándose en un contexto Win API
        return typeof window !== 'undefined' && 
               window.external && 
               window.external.invokeWinAPI;
    }

    initializeEventHandlers() {
        // Mantener los event handlers existentes del index.html
        document.addEventListener('DOMContentLoaded', () => {
            console.log('WebWinAPIBridge initialized');
            this.setupEventHandlers();
        });
    }

    setupEventHandlers() {
        // Seleccionar todos los cursos
        const btnSelectAll = document.getElementById('select-all');
        if (btnSelectAll) {
            btnSelectAll.addEventListener('click', () => {
                this.selectAllCourses(true);
            });
        }

        // Deseleccionar todos los cursos
        const btnDeselectAll = document.getElementById('deselect-all');
        if (btnDeselectAll) {
            btnDeselectAll.addEventListener('click', () => {
                this.selectAllCourses(false);
            });
        }

        // Exportar a CSV
        const btnExportCSV = document.getElementById('export-csv');
        if (btnExportCSV) {
            btnExportCSV.addEventListener('click', () => {
                this.exportToCSV();
            });
        }

        // Agregar curso
        const btnAddCourse = document.getElementById('add-course');
        if (btnAddCourse) {
            btnAddCourse.addEventListener('click', () => {
                this.openCourseModal();
            });
        }
    }

    selectAllCourses(selected) {
        // Si Win API está disponible, usar la funcionalidad nativa
        if (this.isWinAPIAvailable) {
            try {
                window.external.invokeWinAPI('selectAllCourses', selected);
            } catch (error) {
                console.error('Error calling Win API:', error);
            }
        }
        
        // Mantener funcionalidad web
        const checkboxes = document.querySelectorAll('.course-checkbox');
        checkboxes.forEach(checkbox => {
            checkbox.checked = selected;
        });
        
        // Actualizar datos locales
        this.cursosData.forEach(curso => {
            curso.seleccionado = selected;
        });
    }

    exportToCSV() {
        const selectedCourses = this.getSelectedCourses();
        
        if (selectedCourses.length === 0) {
            alert('No hay cursos seleccionados para exportar');
            return;
        }

        // Si Win API está disponible, usar diálogo nativo
        if (this.isWinAPIAvailable) {
            try {
                window.external.invokeWinAPI('exportToCSV', selectedCourses);
                return;
            } catch (error) {
                console.error('Error calling Win API:', error);
            }
        }

        // Funcionalidad web de respaldo
        this.downloadCSV(selectedCourses);
    }

    getSelectedCourses() {
        return this.cursosData.filter(curso => curso.seleccionado);
    }

    downloadCSV(courses) {
        // Crear contenido CSV
        let csvContent = 'curso,nombre,grupo_id,tipo,aula,horas,docente,cupos\n';
        
        courses.forEach(curso => {
            csvContent += `${curso.curso},"${curso.nombre}",${curso.grupo_id},${curso.tipo},${curso.aula},"${curso.horas}","${curso.docente}",${curso.cupos}\n`;
        });

        // Crear y descargar archivo
        const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' });
        const link = document.createElement('a');
        const url = URL.createObjectURL(blob);
        
        link.setAttribute('href', url);
        link.setAttribute('download', 'cursos_seleccionados.csv');
        link.style.visibility = 'hidden';
        
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
    }

    openCourseModal() {
        // Si Win API está disponible, usar diálogo nativo
        if (this.isWinAPIAvailable) {
            try {
                window.external.invokeWinAPI('openCourseDialog');
                return;
            } catch (error) {
                console.error('Error calling Win API:', error);
            }
        }

        // Funcionalidad web de respaldo
        const modal = document.getElementById('course-modal');
        if (modal) {
            modal.style.display = 'block';
        }
    }

    // Métodos para sincronizar con Win API
    syncWithWinAPI() {
        if (!this.isWinAPIAvailable) return;
        
        try {
            window.external.invokeWinAPI('syncData', this.cursosData);
        } catch (error) {
            console.error('Error syncing with Win API:', error);
        }
    }

    loadFromWinAPI() {
        if (!this.isWinAPIAvailable) return;
        
        try {
            const data = window.external.invokeWinAPI('loadData');
            if (data) {
                this.cursosData = JSON.parse(data);
                this.renderTable();
            }
        } catch (error) {
            console.error('Error loading from Win API:', error);
        }
    }

    renderTable() {
        const tbody = document.getElementById('courses-tbody');
        if (!tbody) return;

        tbody.innerHTML = '';
        
        this.cursosData.forEach((curso, index) => {
            const row = document.createElement('tr');
            row.innerHTML = `
                <td>
                    <input type="checkbox" class="course-checkbox" data-index="${index}" ${curso.seleccionado ? 'checked' : ''}>
                </td>
                <td>
                    <div class="course-info">
                        <strong>${curso.curso}</strong>
                        <br>
                        <small>${curso.nombre}</small>
                    </div>
                </td>
                <td><span class="badge">${curso.grupo_id}</span></td>
                <td><span class="badge badge-${curso.tipo.toLowerCase()}">${curso.tipo}</span></td>
                <td>${curso.aula}</td>
                <td>${curso.horas}</td>
                <td>${curso.docente}</td>
                <td><span class="cupos">${curso.cupos}</span></td>
                <td>
                    <button class="btn btn-sm btn-edit" onclick="editCourse(${index})">Editar</button>
                    <button class="btn btn-sm btn-delete" onclick="deleteCourse(${index})">Eliminar</button>
                </td>
            `;
            tbody.appendChild(row);
        });

        // Agregar event listeners a los checkboxes
        const checkboxes = document.querySelectorAll('.course-checkbox');
        checkboxes.forEach(checkbox => {
            checkbox.addEventListener('change', (e) => {
                const index = parseInt(e.target.dataset.index);
                this.cursosData[index].seleccionado = e.target.checked;
                this.syncWithWinAPI();
            });
        });
    }
}

// Inicializar el puente Web-WinAPI
const webWinAPIBridge = new WebWinAPIBridge();

// Funciones globales para mantener compatibilidad
function editCourse(index) {
    // Implementar edición de curso
    console.log('Editing course:', index);
}

function deleteCourse(index) {
    // Implementar eliminación de curso
    if (confirm('¿Está seguro de eliminar este curso?')) {
        webWinAPIBridge.cursosData.splice(index, 1);
        webWinAPIBridge.renderTable();
        webWinAPIBridge.syncWithWinAPI();
    }
}

// Cerrar modal
function closeModal() {
    const modal = document.getElementById('course-modal');
    if (modal) {
        modal.style.display = 'none';
    }
}
