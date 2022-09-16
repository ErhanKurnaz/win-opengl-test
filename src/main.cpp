#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "common/Core.h"

#include "Input/WindowsInput.h"

#include "tests/tests.h"
#include "common/Appstate.h"

AppState appState = {0.0f, 960, 540};

int main() {
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(appState.windowWidth, appState.windowHeight, "OpenGL test", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
        return 1;
    }

    glfwSetKeyCallback(window, KeyEvent::HandleGLFWEvent);

    std::cout << glGetString(GL_VERSION) << std::endl;

    (dynamic_cast<WindowsInput*>(Input::GetInstance()))->SetWindow(window);
    // new scope so that all the open gl stuff gets cleaned correctly
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
        ImGui::StyleColorsDark();

        test::Test* currentTest;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<test::TestScreensaver>("Screen Saver");
        testMenu->RegisterTest<test::TestBatch>("Batch rendering");

        while (!glfwWindowShouldClose(window)) {
            renderer.Clear(0.0f, 0.0f, 0.0f, 1.0f);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest) {
                while (!Event::GetQueue()->empty()) {
                    auto event = Event::PopEvent();
                    currentTest->OnEvent(*event);
                }
                currentTest->OnUpdate(appState);
                currentTest->OnRender(renderer);
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = testMenu;
                }

                currentTest->OnIMGuiRender();
                ImGui::End();
            }

            ImGui::Begin("Configurations");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);

            glfwPollEvents();
        }

        if (currentTest != testMenu)
            delete testMenu;

        delete currentTest;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
