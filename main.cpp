#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <ctime>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "config.h"
#include "stb/stb_image.h"

// Load from file
int image_width = 0;
int image_height = 0;
unsigned char *image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
if (image_data == NULL)
  return false;

// Create a OpenGL texture identifier
GLuint image_texture;
glGenTextures(1, &image_texture);
glBindTexture(GL_TEXTURE_2D, image_texture);

// Setup filtering parameters for display
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
stbi_image_free(image_data);

*out_texture = image_texture;
*out_width = image_width;
*out_height = image_height;

return true;
}

GLFWwindow *g_window;
ImVec4 clear_color = ImVec4(0.01, 0.0f, 0.0f, 0.00f);
ImGuiContext *imgui = 0;
bool show_demo_window = false;
bool show_another_window = true;

EM_JS(int, canvas_get_width, (), {
  return Module.canvas.width;
});

EM_JS(int, canvas_get_height, (), {
  return Module.canvas.height;
});

EM_JS(void, resizeCanvas, (), {
  js_resizeCanvas();
});

void loop()
{
  int width = canvas_get_width();
  int height = canvas_get_height();

  glfwSetWindowSize(g_window, width, height);

  ImGui::SetCurrentContext(imgui);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  if (ImGui::BeginMainMenuBar())
  {
    static bool show_app_main_menu_bar = false;
    if (ImGui::BeginMenu("Applications"))
    {
      ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
      ImGui::MenuItem("Console", NULL, &show_app_main_menu_bar);
      ImGui::MenuItem("Log", NULL, &show_app_main_menu_bar);
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
      if (ImGui::MenuItem("Undo", "CTRL+Z"))
      {
      }
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
      {
      } // Disabled item
      ImGui::Separator();
      if (ImGui::MenuItem("Cut", "CTRL+X"))
      {
      }
      if (ImGui::MenuItem("Copy", "CTRL+C"))
      {
      }
      if (ImGui::MenuItem("Paste", "CTRL+V"))
      {
      }
      ImGui::EndMenu();
    }
    ImGui::Separator();
    auto date = std::chrono::system_clock::now();
    std::time_t date_time = std::chrono::system_clock::to_time_t(date);
    ImGui::Text(std::ctime(&date_time)); // Display some text (you can use a format string too)
    ImGui::EndMainMenuBar();
  }

  // 1. Show a simple window.
  // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
  {
    static float f = 0.0f;
    static int counter = 0;
    ImGui::Text("Hello, world!");                            // Display some text (you can use a format string too)
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

    ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our windows open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    if (ImGui::Button("Button")) // Buttons return true when clicked (NB: most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }

  //std::cout << "2nd window" << std::endl;

  // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
  if (show_another_window)
  {
    ImGui::Begin("Another Window", &show_another_window);
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }

  // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
  if (show_demo_window)
  {
    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
    ImGui::ShowDemoWindow(&show_demo_window);
  }
  ImGui::Render();

  int display_w, display_h;
  glfwMakeContextCurrent(g_window);
  glfwGetFramebufferSize(g_window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  glfwMakeContextCurrent(g_window);
}

int init()
{
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return 1;
  }

  //glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  int canvasWidth = 800;
  int canvasHeight = 600;
  g_window = glfwCreateWindow(canvasWidth, canvasHeight, "WebGui Demo", NULL, NULL);
  if (g_window == NULL)
  {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(g_window); // Initialize GLEW

  // Create game objects
  // Setup Dear ImGui binding
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  ImGui_ImplGlfw_InitForOpenGL(g_window, false);
  ImGui_ImplOpenGL3_Init();

  // Setup style
  //ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();
  CherryTheme();

  imgui = ImGui::GetCurrentContext();

  // Cursor callbacks
  glfwSetMouseButtonCallback(g_window, ImGui_ImplGlfw_MouseButtonCallback);
  glfwSetScrollCallback(g_window, ImGui_ImplGlfw_ScrollCallback);
  glfwSetKeyCallback(g_window, ImGui_ImplGlfw_KeyCallback);
  glfwSetCharCallback(g_window, ImGui_ImplGlfw_CharCallback);

  resizeCanvas();

  return 0;
}

void quit()
{
  glfwTerminate();
}

extern "C" int main(int argc, char **argv)
{
  if (init() != 0)
    return 1;

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#endif

  quit();

  return 0;
}
