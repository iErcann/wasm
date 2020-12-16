#include <iostream>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"

#include "Common/config.h"
#include "Engine.h"
#include "MalStudio/MalStudio.h"


namespace MO3D
{
    
    Engine::Engine() : bRun(true), mWindow(NULL), mVideoWidth(3900), mVideoHeight(3000)
    {
    }
    void Engine::Initialize()
    {
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
        }
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
        mWindow = glfwCreateWindow(VideoWidth(), VideoHeight(), "Test engine", NULL, NULL);
        if (mWindow == NULL)
        {
            fprintf(stderr, "Failed to open GLFW window.\n");
            glfwTerminate();
        }
        glfwMakeContextCurrent(mWindow); // Initialize GLEW
        // Create game objects
        // Setup Dear ImGui binding
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        ImGui_ImplGlfw_InitForOpenGL(mWindow, false);
        ImGui_ImplOpenGL3_Init();

        //ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
        Windows95Theme();
        mImguiContext = ImGui::GetCurrentContext();

        // Cursor callbacks
        glfwSetMouseButtonCallback(mWindow, ImGui_ImplGlfw_MouseButtonCallback);
        glfwSetScrollCallback(mWindow, ImGui_ImplGlfw_ScrollCallback);
        glfwSetKeyCallback(mWindow, ImGui_ImplGlfw_KeyCallback);
        glfwSetCharCallback(mWindow, ImGui_ImplGlfw_CharCallback);

        int ret = Mix_OpenAudio(0, 0, 0, 0); // we ignore all these..


        for (float i = 0; i < 1; i++) {
            std::string s =  "ZEM OEM NOE";
            std::string d = std::to_string(i);
            //MalStudio childWindow(i, i, s+d);
            mChildWindows.push_back(new MalStudio(i, i, s+d));

            // Il faut le delete!
        }



    }
    void tutoRender(){
        float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
        };

        unsigned int VBO;
        glGenBuffers(1, &VBO);
    }
    void Engine::Update()
    {
        int width = VideoWidth();
        int height = VideoHeight();

        glfwSetWindowSize(mWindow, width, height);
        ImGui::SetCurrentContext(mImguiContext);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (auto &childWindow : mChildWindows)
        {
            childWindow->Show();
        }
        bool show_demo_window = false;
        ImGui::ShowDemoWindow(&show_demo_window);
        ImGui::Render();

        int display_w, display_h;
        glfwMakeContextCurrent(mWindow);
        glfwGetFramebufferSize(mWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwMakeContextCurrent(mWindow);
        glfwSwapBuffers(mWindow);

    }
    void Engine::Quit()
    {
        bRun = false;
    }

} // namespace MO3D