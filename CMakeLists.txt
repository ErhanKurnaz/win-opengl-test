cmake_minimum_required(VERSION 3.22)
project(win_opengl_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(win_opengl_test src/main.cpp src/Renderer/Renderer.cpp src/Renderer/Renderer.h src/VertexBuffer/VertexBuffer.h src/VertexBuffer/VertexBuffer.cpp src/IndexBuffer/IndexBuffer.h src/IndexBuffer/IndexBuffer.cpp src/VertexArray/VertexArray.cpp src/VertexArray/VertexArray.h src/VertexBuffer/VertexBufferLayout.h src/Shader/Shader.cpp src/Shader/Shader.h src/loader.cpp src/Texture/Texture.cpp src/Texture/Texture.h src/tests/Test/Test.h src/tests/TestClearColor/TestClearColor.cpp src/tests/TestClearColor/TestClearColor.h src/tests/Test/Test.cpp src/tests/TestScreensaver/TestScreensaver.cpp src/tests/TestScreensaver/TestScreensaver.h src/common/Appstate.h src/tests/TestTexture2D/TestTexture2D.cpp src/tests/TestTexture2D/TestTexture2D.h src/tests/tests.h src/tests/TestBatch/TestBatch.cpp src/tests/TestBatch/TestBatch.h src/Input/Input.cpp src/Input/Input.h src/Input/WindowsInput.cpp src/Input/WindowsInput.h src/Input/KeyCodes.h src/Input/MouseButtonCodes.h src/common/Core.h src/Camera/OrthographicCamera.cpp src/Camera/OrthographicCamera.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)

find_package(OpenGL REQUIRED)

add_compile_definitions(GLEW_STATIC)
target_include_directories(win_opengl_test
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLEW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/STB
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
        )
target_link_libraries(win_opengl_test
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLEW/lib/Release/Win32/glew32s.lib
        glfw
        glm
        imgui
        OpenGL::GL
        )
