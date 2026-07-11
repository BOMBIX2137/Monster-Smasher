cmake_minimum_required(VERSION 3.20)

project(MonsterSmasher
    VERSION 1.0
    LANGUAGES CXX
)

# ==========================================================
# C++
# ==========================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

# ==========================================================
# Vulkan
# ==========================================================

find_package(Vulkan REQUIRED)

# ==========================================================
# GLFW
# ==========================================================

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

# ==========================================================
# GLM
# ==========================================================

set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glm)

# ==========================================================
# ImGui
# ==========================================================

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp

    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(imgui
    PUBLIC
        glfw
        Vulkan::Vulkan
)

# ==========================================================
# stb_image
# ==========================================================

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE
    external/stb
)

# ==========================================================
# Vulkan Memory Allocator
# ==========================================================

add_library(vma INTERFACE)

target_include_directories(vma INTERFACE
    external/VMA/include
)

# ==========================================================
# tinyobjloader
# ==========================================================

add_library(tinyobjloader STATIC
    external/tinyobjloader/tiny_obj_loader.h
    src/tinyobjloader.cpp
)

target_include_directories(tinyobjloader PUBLIC
    external/tinyobjloader
)

# ==========================================================
# Project sources
# ==========================================================

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

list(REMOVE_ITEM SOURCES
    ${CMAKE_SOURCE_DIR}/src/tinyobjloader.cpp
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    include/*.hpp
    include/*.h
)

add_executable(MonsterSmasher
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(MonsterSmasher PRIVATE
    include
)

target_link_libraries(MonsterSmasher PRIVATE
    Vulkan::Vulkan
    glfw
    glm
    imgui
    stb
    vma
    tinyobjloader
)

# ==========================================================
# Compiler warnings
# ==========================================================

if(MSVC)

    target_compile_options(MonsterSmasher PRIVATE
        /W4
        /permissive-
    )

else()

    target_compile_options(MonsterSmasher PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()

# ==========================================================
# Assets
# ==========================================================

add_custom_command(TARGET MonsterSmasher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:MonsterSmasher>/assets
)

# ==========================================================
# Shader compilation
# ==========================================================

find_program(GLSLC glslc)

if(GLSLC)

    file(GLOB SHADERS
        shaders/*.vert
        shaders/*.frag
        shaders/*.comp
    )

    set(SPIRV_BINARY_FILES)

    foreach(SHADER ${SHADERS})

        get_filename_component(FILE_NAME ${SHADER} NAME)

        set(SPIRV
            ${CMAKE_BINARY_DIR}/shaders/${FILE_NAME}.spv
        )

        add_custom_command(
            OUTPUT ${SPIRV}

            COMMAND ${CMAKE_COMMAND} -E make_directory
                ${CMAKE_BINARY_DIR}/shaders

            COMMAND ${GLSLC}
                ${SHADER}
                -o
                ${SPIRV}

            DEPENDS ${SHADER}
        )

        list(APPEND SPIRV_BINARY_FILES ${SPIRV})

    endforeach()

    add_custom_target(Shaders ALL
        DEPENDS ${SPIRV_BINARY_FILES}
    )

    add_dependencies(MonsterSmasher Shaders)

endif()

# ==========================================================
# Startup project (Visual Studio)
# ==========================================================

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT MonsterSmasher)