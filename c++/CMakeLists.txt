# cmake -DCMAKE_BUILD_TYPE=Release ..  → will build with optimization enabled
# cmake -DCMAKE_BUILD_TYPE=Debug .. → will build with optimization disabled
# add options manually: cmake -DCMAKE_CXX_FLAGS="-flto -O0" ..

##############################################################################
# Configuration

cmake_minimum_required (VERSION 3.0)
project (example CXX)
set(PROJECT_DESCRIPTION "Binary tree")

add_compile_options(
    -Wall -Wextra -Wcast-align -Wcast-qual -Wold-style-cast -Wconversion -Wshadow
)

##############################################################################
# Targets

add_executable(tree
    src/main.cpp
)
target_compile_options(tree PRIVATE -std=c++17)
target_include_directories(tree PRIVATE include)

add_executable(map_benchmark src/map_benchmark.cpp)
add_executable(random utilities/random_number_generator/random.cpp)

##############################################################################
# Documentation

find_package(Doxygen)
if (DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
                ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E tar "czf" "docs.tgz" docs
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation"
    )
endif (DOXYGEN_FOUND)
