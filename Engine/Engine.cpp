#include <iostream>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"

#include "../config.h"
#include "Engine.h"

namespace MO3D
{
    Engine::Engine() : run(true), window(NULL), videoWidth(1600), videoHeight(900)
    {
    }
    void Engine::Initialize()
    {
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
        }
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
        window = glfwCreateWindow(VideoWidth(), VideoHeight(), "Test engine", NULL, NULL);
        if (window == NULL)
        {
            fprintf(stderr, "Failed to open GLFW window.\n");
            glfwTerminate();
        }
        glfwMakeContextCurrent(window); // Initialize GLEW
                                        // Create game objects
        // Setup Dear ImGui binding
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        ImGui_ImplGlfw_InitForOpenGL(window, false);
        ImGui_ImplOpenGL3_Init();

        // Setup style
        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
        Windows95Theme();
        imgui = ImGui::GetCurrentContext();

        // Cursor callbacks
        glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
        glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
        glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
        glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);

  
    }
    void Engine::Update()
    {
        int width = VideoWidth();
        int height = VideoHeight();

        glfwSetWindowSize(window, width, height);

        ImGui::SetCurrentContext(imgui);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        bool show_demo_window = false;
        ImGui::ShowDemoWindow(&show_demo_window);

         bool showW  = true;
        ImGui::Begin("Another Window", &showW);
        ImGui::Text("Hello from another window!");
        ImGui::Button("Close Me");
        ImGui::End();
        ImGui::Render();

        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(33, 16, 56, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwMakeContextCurrent(window);

        std::cout << "EEEEEEE" << std::endl;
    }
    void Engine::Quit()
    {
        run = false;
    }

} // namespace MO3D