
#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>
#include "./Window/ChildWindow.h"
#include <vector>

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

        inline const bool Run() const { return bRun; }
        inline GLFWwindow *Window() { return mWindow; }
        inline const float VideoWidth() const
        {
            return mVideoWidth;
        }
        inline const float VideoHeight() const
        {
            return mVideoHeight;
        }

    private:
        bool bRun;
        GLFWwindow *mWindow;
        std::vector<ChildWindow> mChildWindows;
        float mVideoWidth, mVideoHeight;
        ImGuiContext *mImguiContext;

    };
    static Engine &Core = Engine::GetInstance();

} // namespace MO3D