cmake_minimum_required(VERSION 3.16)

project("2d-game")

# find all of the libraries
find_path(GLFW_INCLUDE_DIR "GLFW/glfw3.h")
find_path(GLFW_BINARY_DIR "libglfw3.a")
find_path(GLAD_INCLUDE_DIR "glad/glad.h")
find_path(GLAD_SOURCE_DIR "glad.c")

include_directories("${GLFW_INCLUDE_DIR}" "${GLAD_INCLUDE_DIR}" "include")

link_directories("${GLFW_BINARY_DIR}")

link_libraries("glfw3" "dl" "X11" "Xi" "pthread" "GL" )

add_executable(
    "2d-game"
    "src/2d-game/main.cpp"
    "${GLAD_SOURCE_DIR}/glad.c"
)
