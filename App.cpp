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
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "Engine/Engine.h"
#include "Engine/Audio/AudioPlayer.h"

EM_JS(void, resizeCanvas, (), {
  js_resizeCanvas();
});

Mix_Chunk *sound, *sound2, *sound3;
Mix_Music *music;

int play2()
{
  Mix_ChannelFinished(done);

  int channel2 = Mix_PlayChannel(-1, sound2, 0);
  int channel3 = Mix_PlayChannel(-1, sound3, 0);
  return channel2;
}

int play()
{
  int channel = Mix_PlayChannel(-1, sound, 0);
  assert(channel == 0);

  emscripten_run_script("setTimeout(Module['_play2'], 500)");
  return channel;
}

void loop()
{
  MO3D::Core.Update();
}

extern "C" int main(int argc, char **argv)
{

  SDL_Init(SDL_INIT_AUDIO);
  int ret = Mix_OpenAudio(0, 0, 0, 0); // we ignore all these..

  sound2 = Mix_LoadWAV("data/piano.mp3");

  std::cout << "Main lancé" << std::endl;
  FILE *file = fopen("data/hello.txt", "rb");
  if (!file)
  {
    printf("cannot open file\n");
    return 1;
  }
  while (!feof(file))
  {
    char c = fgetc(file);
    if (c != EOF)
    {
      putchar(c);
    }
  }
  fclose(file);

  MO3D::Core.Initialize();
  MO3D::Audio.Initialize();
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#endif
  MO3D::Core.Quit();
  return 0;
}
