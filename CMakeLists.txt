# Detects whether this is a top-level project
get_directory_property(LIBIGL_PARENT_DIR PARENT_DIRECTORY)
if(NOT LIBIGL_PARENT_DIR)
    set(LIBIGL_TOPLEVEL_PROJECT ON)
else()
    set(LIBIGL_TOPLEVEL_PROJECT OFF)
endif()

# Check required CMake version
set(REQUIRED_CMAKE_VERSION "3.16.0")
if(LIBIGL_TOPLEVEL_PROJECT)
    cmake_minimum_required(VERSION ${REQUIRED_CMAKE_VERSION})
else()
    # Don't use cmake_minimum_required here to avoid implicitly overriding parent policies
    if(${CMAKE_VERSION} VERSION_LESS ${REQUIRED_CMAKE_VERSION})
        message(FATAL_ERROR "CMake required version to build Libigl is ${REQUIRED_CMAKE_VERSION}")
    endif()
endif()

# Include user-provided default options if available. We do that before the main
# `project()` so that we can define the C/C++ compilers from the option file.
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/LibiglOptions.cmake)
    message(STATUS "Using local options file: ${CMAKE_CURRENT_SOURCE_DIR}/LibiglOptions.cmake")
    include(${CMAKE_CURRENT_SOURCE_DIR}/LibiglOptions.cmake)
endif()

# If this option is enabled, this will setup the Hunter package manager.
option(HUNTER_ENABLED "Enable Hunter package manager support" OFF)
if(HUNTER_ENABLED)
    include("cmake/misc/HunterGate.cmake")
    HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.24.8.tar.gz"
        SHA1 "ca7838dded9a1811b04ffd56175f629e0af82d3d"
    )
endif()

################################################################################

project(mesh_viewer VERSION 1.0.0)

# CMake module path
list(PREPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/cmake/
    ${CMAKE_CURRENT_LIST_DIR}/cmake/igl
    ${CMAKE_CURRENT_LIST_DIR}/cmake/find
    ${CMAKE_CURRENT_LIST_DIR}/cmake/recipes/external
)

if(HUNTER_ENABLED)
    list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/recipes/hunter)
else()
    list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/recipes/external)
endif()

set_property(GLOBAL PROPERTY __igl_module_path ${CMAKE_MODULE_PATH})

set(LIBIGL_DEFAULT_CGAL ${LIBIGL_TOPLEVEL_PROJECT})

option(LIBIGL_INSTALL               "Enable installation of libigl targets"         ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_USE_STATIC_LIBRARY    "Use libigl as static library"                  ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_EMBREE                "Build target igl::embree"                      OFF)
option(LIBIGL_GLFW                  "Build target igl::glfw"                        ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_IMGUI                 "Build target igl::imgui"                       ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_OPENGL                "Build target igl::opengl"                      ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_PNG                   "Build target igl::png"                         ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_PREDICATES            "Build target igl::predicates"                  OFF)
option(LIBIGL_XML                   "Build target igl::xml"                         OFF)
option(LIBIGL_COPYLEFT_CORE         "Build target igl_copyleft::core"               ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_COPYLEFT_CGAL         "Build target igl_copyleft::cgal"               ${LIBIGL_TOPLEVEL_PROJECT})
option(LIBIGL_COPYLEFT_COMISO       "Build target igl_copyleft::comiso"             OFF)
option(LIBIGL_COPYLEFT_TETGEN       "Build target igl_copyleft::tetgen"             OFF)
option(LIBIGL_RESTRICTED_MATLAB     "Build target igl_restricted::matlab"           OFF)
option(LIBIGL_RESTRICTED_MOSEK      "Build target igl_restricted::mosek"            OFF)
option(LIBIGL_RESTRICTED_TRIANGLE   "Build target igl_restricted::triangle"         OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Include CMake helper functions
include(igl_add_library)
include(igl_add_test)
include(igl_copy_dll)
include(igl_include)
include(igl_install)
include(igl_target_sources)

# Defines CMake targets for selected libigl modules
include(libigl)

add_executable(${PROJECT_NAME}
    src/viewer/glfw/background_window.cpp
    src/viewer/glfw/map_texture.cpp
    src/viewer/glfw/Viewer.cpp
    src/viewer/glfw/imgui/ImGuiMenu.cpp
    src/viewer/glfw/imgui/ImGuiPlugin.cpp
    src/viewer/glfw/imgui/ImGuizmoWidget.cpp
    src/viewer/glfw/imgui/SelectionWidget.cpp

    src/functions/boundingBox.cpp
    src/functions/subdivide.cpp
    src/functions/curvatures.cpp

    src/workers/exit.cpp
    src/workers/file.cpp
    src/workers/plotter.cpp
    src/workers/processing.cpp
    src/workers/snapshot.cpp
    src/workers/viewport.cpp
    src/workers/workspace.cpp

    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} igl::core igl::imgui igl::png)
