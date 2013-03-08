cmake_minimum_required(VERSION 2.8)
project (c-xml-parser)

add_subdirectory(libroxml)
include_directories(libroxml/inc)
link_directories(${PROJECT_BINARY_DIR}/libroxml)
add_executable(c-xml-parser main.c)
target_link_libraries(c-xml-parser roxml-static)
