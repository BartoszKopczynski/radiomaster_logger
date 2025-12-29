cmake_minimum_required(VERSION 3.10)
project(boxer_stick_logger LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Silence OpenGL policy warning (optional but recommended)
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# Dependencies
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Executable
add_executable(boxer_logger
    src/main.cpp
    src/JoystickReader.cpp
    src/CSVLogger.cpp
    src/BinaryLogger.cpp

    # ImGui core
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp

    # ImGui backends
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp

    # GLAD
    glad/src/glad.c
)

# Include paths
target_include_directories(boxer_logger PRIVATE
    include
    imgui
    imgui/backends
    glad/include
)

# Compile definitions
target_compile_definitions(boxer_logger PRIVATE
    GLFW_INCLUDE_NONE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
    GLFW_EXPOSE_NATIVE_X11
    GLFW_EXPOSE_NATIVE_GLX
)




# Link libraries
target_link_libraries(boxer_logger PRIVATE
    Threads::Threads
    OpenGL::GL
    glfw
    dl
)
