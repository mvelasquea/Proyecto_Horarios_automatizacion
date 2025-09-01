// Gestor de Cursos y Grupos - Sistema de Checklist
document.addEventListener('DOMContentLoaded', function() {
    console.log('Sistema de Checklist iniciado');
    
    // Datos de ejemplo con cursos
    let cursosData = [
        {
            id: 1,
            curso: "1701102",
            nombre: "RAZONAMIENTO LOGICO MATEMATICO",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "A101",
            horas: "1_08:00-10:00 3_14:00-16:00",
            docente: "Dr. José Mendoza",
            cupos: 30,
            seleccionado: false
        },
        {
            id: 2,
            curso: "1701103",
            nombre: "MATEMATICA BASICA",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "A102",
            horas: "1_10:00-12:00 3_16:00-18:00",
            docente: "Dra. María García",
            cupos: 35,
            seleccionado: false
        },
        {
            id: 3,
            curso: "1701104",
            nombre: "ESTRUCTURAS DISCRETAS 1",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "B201",
            horas: "2_08:00-10:00 4_14:00-16:00",
            docente: "Dr. Ana Rodríguez",
            cupos: 25,
            seleccionado: false
        },
        {
            id: 4,
            curso: "1701105",
            nombre: "INTRODUCCION A LA COMPUTACION",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "C301",
            horas: "1_14:00-16:00 5_10:00-12:00",
            docente: "Ing. Pedro Sánchez",
            cupos: 40,
            seleccionado: false
        },
        {
            id: 5,
            curso: "1701106",
            nombre: "FUNDAMENTOS DE LA PROGRAMACION 1",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "C302",
            horas: "2_10:00-12:00 4_16:00-18:00",
            docente: "Dra. Laura Martínez",
            cupos: 30,
            seleccionado: false
        },
        {
            id: 6,
            curso: "1701106",
            nombre: "FUNDAMENTOS DE LA PROGRAMACION 1",
            grupo_id: "101",
            tipo: "LABORATORIO",
            aula: "Lab1",
            horas: "5_14:00-18:00",
            docente: "Ing. Roberto Torres",
            cupos: 20,
            seleccionado: false
        },
        {
            id: 7,
            curso: "1701212",
            nombre: "PROGRAMACION WEB 1",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "D401",
            horas: "1_16:00-18:00 2_08:00-10:00",
            docente: "Ing. Sandra Vega",
            cupos: 25,
            seleccionado: false
        },
        {
            id: 8,
            curso: "1701212",
            nombre: "PROGRAMACION WEB 1",
            grupo_id: "101",
            tipo: "LABORATORIO",
            aula: "Lab2",
            horas: "4_08:00-12:00",
            docente: "Ing. Miguel Flores",
            cupos: 15,
            seleccionado: false
        },
        {
            id: 9,
            curso: "1703133",
            nombre: "ALGORITMOS Y PROGRAMACION",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "B201",
            horas: "1_08:00-09:40 3_08:00-09:40",
            docente: "María López",
            cupos: 25,
            seleccionado: false
        },
        {
            id: 10,
            curso: "1703133",
            nombre: "ALGORITMOS Y PROGRAMACION",
            grupo_id: "2",
            tipo: "TEORIA",
            aula: "B202",
            horas: "1_08:30-10:10 3_08:30-10:10",
            docente: "Carlos Sánchez",
            cupos: 28,
            seleccionado: false
        },
        {
            id: 11,
            curso: "1703133",
            nombre: "ALGORITMOS Y PROGRAMACION",
            grupo_id: "101",
            tipo: "LABORATORIO",
            aula: "Lab1",
            horas: "2_10:00-11:40",
            docente: "Juan Pérez",
            cupos: 18,
            seleccionado: false
        },
        {
            id: 12,
            curso: "1703134",
            nombre: "ESTRUCTURAS DE DATOS",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "C105",
            horas: "1_08:00-09:40 3_08:00-09:40",
            docente: "Laura Méndez",
            cupos: 22,
            seleccionado: false
        },
        {
            id: 13,
            curso: "1703134",
            nombre: "ESTRUCTURAS DE DATOS",
            grupo_id: "2",
            tipo: "TEORIA",
            aula: "C106",
            horas: "1_09:00-10:40 3_09:00-10:40",
            docente: "Diego Castillo",
            cupos: 21,
            seleccionado: false
        },
        {
            id: 14,
            curso: "1703134",
            nombre: "ESTRUCTURAS DE DATOS",
            grupo_id: "101",
            tipo: "LABORATORIO",
            aula: "Lab5",
            horas: "2_10:00-11:40",
            docente: "Andrés López",
            cupos: 19,
            seleccionado: false
        },
        {
            id: 15,
            curso: "1703135",
            nombre: "INGENIERIA Y PROCESOS DE SOFTWARE",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "D303",
            horas: "1_10:00-11:40 3_10:00-11:40",
            docente: "Ana Martínez",
            cupos: 18,
            seleccionado: false
        },
        {
            id: 16,
            curso: "1703135",
            nombre: "INGENIERIA Y PROCESOS DE SOFTWARE",
            grupo_id: "2",
            tipo: "TEORIA",
            aula: "D304",
            horas: "1_10:30-12:10 3_10:30-12:10",
            docente: "Ricardo Torres",
            cupos: 19,
            seleccionado: false
        },
        {
            id: 17,
            curso: "1703135",
            nombre: "INGENIERIA Y PROCESOS DE SOFTWARE",
            grupo_id: "101",
            tipo: "LABORATORIO",
            aula: "Lab9",
            horas: "2_14:00-15:40",
            docente: "Claudia Ruiz",
            cupos: 15,
            seleccionado: false
        }
    ];
    
    // Referencias del DOM
    const coursesTableBody = document.getElementById('courses-tbody');
    const courseModal = document.getElementById('course-modal');
    const courseForm = document.getElementById('course-form');
    const modalTitle = document.getElementById('modal-title');
    const selectAllCheckbox = document.getElementById('select-all-checkbox');
    
    // Botones
    const btnSelectAll = document.getElementById('select-all');
    const btnDeselectAll = document.getElementById('deselect-all');
    const btnAddCourse = document.getElementById('add-course');
    const btnExportCSV = document.getElementById('export-csv');
    const closeModal = document.querySelector('.close');
    
    let editingIndex = -1;
    
    // Función para renderizar la tabla
    function renderTable() {
        console.log('Renderizando tabla con', cursosData.length, 'cursos');
        
        if (!coursesTableBody) {
            console.error('No se encontró el elemento courses-tbody');
            return;
        }
        
        coursesTableBody.innerHTML = '';
        
        cursosData.forEach((curso, index) => {
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
                    <button class="btn btn-sm btn-secondary" onclick="editCourse(${index})">
                        Editar
                    </button>
                    <button class="btn btn-sm btn-danger" onclick="deleteCourse(${index})">
                        Eliminar
                    </button>
                </td>
            `;
            coursesTableBody.appendChild(row);
        });
        
        // Agregar event listeners a los checkboxes
        document.querySelectorAll('.course-checkbox').forEach(checkbox => {
            checkbox.addEventListener('change', function() {
                const index = parseInt(this.dataset.index);
                cursosData[index].seleccionado = this.checked;
                updateSelectAllCheckbox();
            });
        });
        
        updateSelectAllCheckbox();
    }
    
    // Actualizar checkbox principal
    function updateSelectAllCheckbox() {
        if (!selectAllCheckbox) return;
        
        const checkboxes = document.querySelectorAll('.course-checkbox');
        const checkedCount = document.querySelectorAll('.course-checkbox:checked').length;
        
        if (checkedCount === 0) {
            selectAllCheckbox.indeterminate = false;
            selectAllCheckbox.checked = false;
        } else if (checkedCount === checkboxes.length) {
            selectAllCheckbox.indeterminate = false;
            selectAllCheckbox.checked = true;
        } else {
            selectAllCheckbox.indeterminate = true;
            selectAllCheckbox.checked = false;
        }
    }
    
    // Event listeners
    if (selectAllCheckbox) {
        selectAllCheckbox.addEventListener('change', function() {
            const shouldCheck = this.checked;
            cursosData.forEach(curso => {
                curso.seleccionado = shouldCheck;
            });
            renderTable();
        });
    }
    
    if (btnSelectAll) {
        btnSelectAll.addEventListener('click', function() {
            cursosData.forEach(curso => {
                curso.seleccionado = true;
            });
            renderTable();
        });
    }
    
    if (btnDeselectAll) {
        btnDeselectAll.addEventListener('click', function() {
            cursosData.forEach(curso => {
                curso.seleccionado = false;
            });
            renderTable();
        });
    }
    
    if (btnAddCourse) {
        btnAddCourse.addEventListener('click', function() {
            editingIndex = -1;
            if (modalTitle) modalTitle.textContent = 'Agregar Nuevo Curso';
            if (courseForm) courseForm.reset();
            if (courseModal) courseModal.style.display = 'block';
        });
    }
    
    if (closeModal) {
        closeModal.addEventListener('click', function() {
            if (courseModal) courseModal.style.display = 'none';
        });
    }
    
    // Cerrar modal al hacer clic fuera
    window.addEventListener('click', function(event) {
        if (event.target === courseModal) {
            courseModal.style.display = 'none';
        }
    });
    
    // Formulario
    if (courseForm) {
        courseForm.addEventListener('submit', function(e) {
            e.preventDefault();
            
            const cursoSelect = document.getElementById('curso-name');
            const cursoValue = cursoSelect.value;
            const cursoText = cursoSelect.options[cursoSelect.selectedIndex].text;
            
            const courseData = {
                curso: cursoValue,
                nombre: cursoText.split(' - ')[1] || cursoText,
                grupo_id: document.getElementById('grupo-id').value,
                tipo: document.getElementById('tipo').value,
                aula: document.getElementById('aula').value,
                horas: document.getElementById('horas').value,
                docente: document.getElementById('docente').value,
                cupos: parseInt(document.getElementById('cupos').value),
                seleccionado: false
            };
            
            if (editingIndex >= 0) {
                courseData.id = cursosData[editingIndex].id;
                cursosData[editingIndex] = courseData;
            } else {
                courseData.id = Date.now();
                cursosData.push(courseData);
            }
            
            renderTable();
            courseModal.style.display = 'none';
            
            showNotification(editingIndex >= 0 ? 'Curso actualizado' : 'Curso agregado', 'success');
        });
    }
    
    // Exportar CSV
    if (btnExportCSV) {
        btnExportCSV.addEventListener('click', function() {
            const selectedCourses = cursosData.filter(curso => curso.seleccionado);
            
            if (selectedCourses.length === 0) {
                showNotification('No hay cursos seleccionados', 'warning');
                return;
            }
            
            const csvContent = generateCSV(selectedCourses);
            downloadCSV(csvContent, 'cursos_seleccionados.csv');
            
            showNotification(`${selectedCourses.length} cursos exportados`, 'success');
        });
    }
    
    // Funciones globales
    window.editCourse = function(index) {
        editingIndex = index;
        const curso = cursosData[index];
        
        if (modalTitle) modalTitle.textContent = 'Editar Curso';
        if (document.getElementById('curso-name')) document.getElementById('curso-name').value = curso.curso;
        if (document.getElementById('grupo-id')) document.getElementById('grupo-id').value = curso.grupo_id;
        if (document.getElementById('tipo')) document.getElementById('tipo').value = curso.tipo;
        if (document.getElementById('aula')) document.getElementById('aula').value = curso.aula;
        if (document.getElementById('horas')) document.getElementById('horas').value = curso.horas;
        if (document.getElementById('docente')) document.getElementById('docente').value = curso.docente;
        if (document.getElementById('cupos')) document.getElementById('cupos').value = curso.cupos;
        
        if (courseModal) courseModal.style.display = 'block';
    };
    
    window.deleteCourse = function(index) {
        const curso = cursosData[index];
        if (confirm(`¿Eliminar ${curso.curso} - Grupo ${curso.grupo_id}?`)) {
            cursosData.splice(index, 1);
            renderTable();
            showNotification('Curso eliminado', 'success');
        }
    };
    
    window.closeModal = function() {
        if (courseModal) courseModal.style.display = 'none';
    };
    
    // Funciones auxiliares
    function generateCSV(courses) {
        const headers = ['Curso', 'Nombre', 'Grupo ID', 'Tipo', 'Aula', 'Horas', 'Docente', 'Cupos'];
        const csvRows = [headers.join(',')];
        
        courses.forEach(curso => {
            const row = [
                curso.curso,
                `"${curso.nombre}"`,
                curso.grupo_id,
                curso.tipo,
                curso.aula,
                `"${curso.horas}"`,
                `"${curso.docente}"`,
                curso.cupos
            ];
            csvRows.push(row.join(','));
        });
        
        return csvRows.join('\n');
    }
    
    function downloadCSV(content, filename) {
        const blob = new Blob([content], { type: 'text/csv;charset=utf-8;' });
        const link = document.createElement('a');
        const url = URL.createObjectURL(blob);
        
        link.setAttribute('href', url);
        link.setAttribute('download', filename);
        link.style.visibility = 'hidden';
        
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
    }
    
    function showNotification(message, type = 'info') {
        const notification = document.createElement('div');
        notification.className = `notification notification-${type}`;
        notification.textContent = message;
        notification.style.cssText = `
            position: fixed;
            top: 20px;
            right: 20px;
            padding: 15px 20px;
            border-radius: 5px;
            color: white;
            font-weight: bold;
            z-index: 1000;
            transform: translateX(100%);
            transition: transform 0.3s ease;
        `;
        
        if (type === 'success') notification.style.backgroundColor = '#4CAF50';
        else if (type === 'warning') notification.style.backgroundColor = '#FF9800';
        else notification.style.backgroundColor = '#2196F3';
        
        document.body.appendChild(notification);
        
        setTimeout(() => {
            notification.style.transform = 'translateX(0)';
        }, 10);
        
        setTimeout(() => {
            notification.style.transform = 'translateX(100%)';
            setTimeout(() => {
                if (document.body.contains(notification)) {
                    document.body.removeChild(notification);
                }
            }, 300);
        }, 3000);
    }
    
    // Inicializar la aplicación
    console.log('Inicializando tabla...');
    renderTable();
    
    console.log('Sistema de Checklist listo');
});
