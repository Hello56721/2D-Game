cmake_minimum_required(VERSION 3.16)

project("2d-game")

# use c++-17
set(CMAKE_CXX_STANDARD 17)

# find all of the libraries
find_path(GLFW_INCLUDE_DIR NAMES "GLFW/glfw3.h")
find_path(GLFW_BINARY_DIR NAMES "libglfw3.a")
find_path(GLAD_INCLUDE_DIR NAMES "glad/glad.h")
find_path(GLAD_SOURCE_DIR NAMES "glad.c")
find_path(GLM_INCLUDE_DIR NAMES"glm/glm.hpp")

include_directories("${GLFW_INCLUDE_DIR}" "${GLAD_INCLUDE_DIR}" "${GLM_INCLUDE_DIR}" "include")

link_directories("${GLFW_BINARY_DIR}")

if (UNIX AND NOT APPLE)
    link_libraries("glfw3" "dl" "X11" "Xi" "pthread" "GL")
endif()
if (WIN32)
    link_libraries("glfw3" "gdi32" "opengl32")
endif()

if (NOT MSVC)
    add_compile_options("-Wall" "-g3")
endif()

add_executable(
    "2d-game"
    "src/2d-game/main.cpp"
    "src/2d-game/Display.cpp"
    "${GLAD_SOURCE_DIR}/glad.c"
)
add_executable(
    "test"
    "test/fileutils.cpp"
)
add_library(
    "EngineGraphics" SHARED
    "src/EngineGraphics/Utils.cpp"
    "src/EngineGraphics/Shader.cpp"
    "src/EngineGraphics/Mesh.cpp"
    "${GLAD_SOURCE_DIR}/glad.c"
)
add_library(
    "EngineUtils" SHARED
    "src/EngineUtils/FileUtils.cpp"
)

target_link_libraries("2d-game" "EngineGraphics" "EngineUtils")
target_link_libraries("EngineGraphics" "EngineUtils")

target_link_libraries("test" "EngineUtils")