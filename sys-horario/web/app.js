// Gestor de Cursos - Interfaz de Checklist
document.addEventListener('DOMContentLoaded', function() {
    console.log('Iniciando Sistema de Checklist...');
    
    // Datos de ejemplo
    let cursosData = [
        {
            id: 1,
            curso: "1701102",
            nombre: "RAZONAMIENTO LOGICO MATEMATICO",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "A101",
            horas: "L:08-10, M:14-16",
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
            horas: "L:10-12, M:16-18",
            docente: "Dra. María García",
            cupos: 35,
            seleccionado: false
        },
        {
            id: 3,
            curso: "1701103",
            nombre: "MATEMATICA BASICA",
            grupo_id: "101",
            tipo: "PRACTICA",
            aula: "A103",
            horas: "V:08-10",
            docente: "Ing. Carlos López",
            cupos: 20,
            seleccionado: false
        },
        {
            id: 4,
            curso: "1701104",
            nombre: "ESTRUCTURAS DISCRETAS 1",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "B201",
            horas: "Ma:08-10, J:14-16",
            docente: "Dr. Ana Rodríguez",
            cupos: 25,
            seleccionado: false
        },
        {
            id: 5,
            curso: "1701105",
            nombre: "INTRODUCCION A LA COMPUTACION",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "C301",
            horas: "L:14-16, V:10-12",
            docente: "Ing. Pedro Sánchez",
            cupos: 40,
            seleccionado: false
        },
        {
            id: 6,
            curso: "1701106",
            nombre: "FUNDAMENTOS DE LA PROGRAMACION 1",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "C302",
            horas: "Ma:10-12, J:16-18",
            docente: "Dra. Laura Martínez",
            cupos: 30,
            seleccionado: false
        },
        {
            id: 7,
            curso: "1701106",
            nombre: "FUNDAMENTOS DE LA PROGRAMACION 1",
            grupo_id: "101",
            tipo: "LABORATORIO",
            aula: "Lab1",
            horas: "V:14-18",
            docente: "Ing. Roberto Torres",
            cupos: 20,
            seleccionado: false
        },
        {
            id: 8,
            curso: "1701212",
            nombre: "PROGRAMACION WEB 1",
            grupo_id: "1",
            tipo: "TEORIA",
            aula: "D401",
            horas: "L:16-18, M:08-10",
            docente: "Ing. Sandra Vega",
            cupos: 25,
            seleccionado: false
        },
        {
            id: 9,
            curso: "1701212",
            nombre: "PROGRAMACION WEB 1",
            grupo_id: "101",
            tipo: "LABORATORIO",
            aula: "Lab2",
            horas: "J:08-12",
            docente: "Ing. Miguel Flores",
            cupos: 15,
            seleccionado: false
        }
    ];
    
    let editingIndex = -1;
    
    // Función para renderizar la tabla
    function renderTable() {
        const tbody = document.getElementById('courses-tbody');
        if (!tbody) {
            console.error('No se encontró el elemento courses-tbody');
            return;
        }
        
        tbody.innerHTML = '';
        
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
            tbody.appendChild(row);
        });
        
        // Agregar listeners a los checkboxes
        document.querySelectorAll('.course-checkbox').forEach(checkbox => {
            checkbox.addEventListener('change', function() {
                const index = parseInt(this.dataset.index);
                cursosData[index].seleccionado = this.checked;
                updateSelectAllCheckbox();
            });
        });
        
        updateSelectAllCheckbox();
    }
    
    // Función para actualizar el checkbox principal
    function updateSelectAllCheckbox() {
        const selectAllCheckbox = document.getElementById('select-all-checkbox');
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
    
    // Event listeners para botones
    const btnSelectAll = document.getElementById('select-all');
    if (btnSelectAll) {
        btnSelectAll.addEventListener('click', function() {
            cursosData.forEach(curso => curso.seleccionado = true);
            renderTable();
        });
    }
    
    const btnDeselectAll = document.getElementById('deselect-all');
    if (btnDeselectAll) {
        btnDeselectAll.addEventListener('click', function() {
            cursosData.forEach(curso => curso.seleccionado = false);
            renderTable();
        });
    }
    
    const btnAddCourse = document.getElementById('add-course');
    if (btnAddCourse) {
        btnAddCourse.addEventListener('click', function() {
            editingIndex = -1;
            const modal = document.getElementById('course-modal');
            const modalTitle = document.getElementById('modal-title');
            const form = document.getElementById('course-form');
            
            if (modalTitle) modalTitle.textContent = 'Agregar Nuevo Curso';
            if (form) form.reset();
            if (modal) modal.style.display = 'block';
        });
    }
    
    const btnExportCSV = document.getElementById('export-csv');
    if (btnExportCSV) {
        btnExportCSV.addEventListener('click', function() {
            const selectedCourses = cursosData.filter(curso => curso.seleccionado);
            
            if (selectedCourses.length === 0) {
                alert('No hay cursos seleccionados para exportar');
                return;
            }
            
            const csvContent = generateCSV(selectedCourses);
            downloadCSV(csvContent, 'cursos_seleccionados.csv');
            
            alert(`${selectedCourses.length} cursos exportados exitosamente`);
        });
    }
    
    // Checkbox principal
    const selectAllCheckbox = document.getElementById('select-all-checkbox');
    if (selectAllCheckbox) {
        selectAllCheckbox.addEventListener('change', function() {
            const shouldCheck = this.checked;
            cursosData.forEach(curso => curso.seleccionado = shouldCheck);
            renderTable();
        });
    }
    
    // Cerrar modal
    const closeModal = document.querySelector('.close');
    if (closeModal) {
        closeModal.addEventListener('click', function() {
            const modal = document.getElementById('course-modal');
            if (modal) modal.style.display = 'none';
        });
    }
    
    // Cerrar modal al hacer clic fuera
    window.addEventListener('click', function(event) {
        const modal = document.getElementById('course-modal');
        if (event.target === modal) {
            modal.style.display = 'none';
        }
    });
    
    // Formulario de curso
    const courseForm = document.getElementById('course-form');
    if (courseForm) {
        courseForm.addEventListener('submit', function(e) {
            e.preventDefault();
            
            const cursoSelect = document.getElementById('curso-name');
            const courseData = {
                curso: cursoSelect ? cursoSelect.value : '',
                nombre: cursoSelect ? cursoSelect.options[cursoSelect.selectedIndex].text.split(' - ')[1] || cursoSelect.options[cursoSelect.selectedIndex].text : '',
                grupo_id: document.getElementById('grupo-id') ? document.getElementById('grupo-id').value : '',
                tipo: document.getElementById('tipo') ? document.getElementById('tipo').value : '',
                aula: document.getElementById('aula') ? document.getElementById('aula').value : '',
                horas: document.getElementById('horas') ? document.getElementById('horas').value : '',
                docente: document.getElementById('docente') ? document.getElementById('docente').value : '',
                cupos: document.getElementById('cupos') ? parseInt(document.getElementById('cupos').value) : 0,
                seleccionado: false
            };
            
            if (editingIndex >= 0) {
                courseData.id = cursosData[editingIndex].id;
                cursosData[editingIndex] = courseData;
                alert('Curso actualizado exitosamente');
            } else {
                courseData.id = Date.now();
                cursosData.push(courseData);
                alert('Curso agregado exitosamente');
            }
            
            renderTable();
            const modal = document.getElementById('course-modal');
            if (modal) modal.style.display = 'none';
        });
    }
    
    // Funciones globales
    window.editCourse = function(index) {
        editingIndex = index;
        const curso = cursosData[index];
        
        const modal = document.getElementById('course-modal');
        const modalTitle = document.getElementById('modal-title');
        
        if (modalTitle) modalTitle.textContent = 'Editar Curso';
        
        // Llenar formulario
        const cursoSelect = document.getElementById('curso-name');
        const grupoId = document.getElementById('grupo-id');
        const tipo = document.getElementById('tipo');
        const aula = document.getElementById('aula');
        const horas = document.getElementById('horas');
        const docente = document.getElementById('docente');
        const cupos = document.getElementById('cupos');
        
        if (cursoSelect) cursoSelect.value = curso.curso;
        if (grupoId) grupoId.value = curso.grupo_id;
        if (tipo) tipo.value = curso.tipo;
        if (aula) aula.value = curso.aula;
        if (horas) horas.value = curso.horas;
        if (docente) docente.value = curso.docente;
        if (cupos) cupos.value = curso.cupos;
        
        if (modal) modal.style.display = 'block';
    };
    
    window.deleteCourse = function(index) {
        const curso = cursosData[index];
        if (confirm(`¿Está seguro de eliminar el curso ${curso.curso} - Grupo ${curso.grupo_id}?`)) {
            cursosData.splice(index, 1);
            renderTable();
            alert('Curso eliminado exitosamente');
        }
    };
    
    // Función para generar CSV
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
    
    // Función para descargar CSV
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
    
    // Inicializar la aplicación
    renderTable();
    console.log('Sistema de Checklist iniciado correctamente');
});
