cmake_minimum_required(VERSION 3.10)
project(PSGraphScheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluye los headers en include y subcarpetas
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Recolectar fuentes principales (excluyendo tests)
file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Ejecutable principal
add_executable(psgraph_main ${SRC_FILES})

# ---- TESTS ----
enable_testing()
# Buscar archivos de test (pueden tener main propio)
file(GLOB TEST_SRC
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)
if(TEST_SRC)
    add_executable(psgraph_tests ${TEST_SRC})
    add_test(NAME run_psgraph_tests COMMAND psgraph_tests)
endif()
