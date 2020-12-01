
#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

namespace MO3D
{
    class Engine
    {
    public:
        Engine();

        static Engine &GetInstance()
        {
            static Engine reference;
            return reference;
        } 

        void Quit();
        void Update();
        void Initialize();

        inline const bool Run() const { return run; }
        inline GLFWwindow* Window() { return window; }
        inline const float VideoWidth() const { return videoWidth; }
        inline const float VideoHeight() const { return videoHeight; }

    private:
        bool run;
        GLFWwindow *window;
        float videoWidth, videoHeight;
    };
    static Engine& Core = Engine::GetInstance();

} // namespace MO3D