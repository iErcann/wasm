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
#include <AL/al.h>
#include <AL/alc.h>

#include "Engine/Engine.h"
#include "Engine/Audio/AudioPlayer.h"

EM_JS(void, resizeCanvas, (), {
  js_resizeCanvas();
});

void loop()
{
  MO3D::Core.Update();
}

void playSource(void *arg)
{
  ALuint source = static_cast<ALuint>(reinterpret_cast<intptr_t>(arg));
  ALint state;

  alGetSourcei(source, AL_SOURCE_STATE, &state);
  alSourcePause(source);
  alGetSourcei(source, AL_SOURCE_STATE, &state);
  alSourcePlay(source);
  alGetSourcei(source, AL_SOURCE_STATE, &state);
#ifndef TEST_LOOPED_PLAYBACK
  alSourceStop(source);
  alGetSourcei(source, AL_SOURCE_STATE, &state);
#endif
}

int testAudio()
{
  int major, minor;
  alcGetIntegerv(NULL, ALC_MAJOR_VERSION, 1, &major);
  alcGetIntegerv(NULL, ALC_MINOR_VERSION, 1, &minor);


  printf("ALC version: %i.%i\n", major, minor);
  printf("Default device: %s\n", alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));

  ALCdevice *device = alcOpenDevice(NULL);
#if defined(TEST_ANIMATED_LOOPED_PANNED_PLAYBACK)
  ALCint attrs[] = {0x1992 /* ALC_HRTF_SOFT */, ALC_TRUE, 0x1996 /* ALC_HRTF_ID_SOFT */, 0, 0};
  ALCcontext *context = alcCreateContext(device, attrs);
#else
  ALCcontext *context = alcCreateContext(device, NULL);
#endif
  alcMakeContextCurrent(context);


  printf("OpenAL version: %s\n", alGetString(AL_VERSION));
  printf("OpenAL vendor: %s\n", alGetString(AL_VENDOR));
  printf("OpenAL renderer: %s\n", alGetString(AL_RENDERER));

  ALfloat listenerPos[] = {0.0, 0.0, 1.0};
  ALfloat listenerVel[] = {0.0, 0.0, 0.0};
  ALfloat listenerOri[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

  alListenerfv(AL_POSITION, listenerPos);
  alListenerfv(AL_VELOCITY, listenerVel);
  alListenerfv(AL_ORIENTATION, listenerOri);

  // check getting and setting global gain
  ALfloat volume;
  alGetListenerf(AL_GAIN, &volume);
  alListenerf(AL_GAIN, 0.0);
  alGetListenerf(AL_GAIN, &volume);

  alListenerf(AL_GAIN, 1.0); // reset gain to default

  ALuint buffers[1];

  alGenBuffers(1, buffers);

  FILE *source = fopen("data/piano.mp3", "rb");
  fseek(source, 0, SEEK_END);
  int size = ftell(source);
  fseek(source, 0, SEEK_SET);

  unsigned char *buffer = (unsigned char *)malloc(size);
  fread(buffer, size, 1, source);

  unsigned offset = 12; // ignore the RIFF header
  offset += 8;          // ignore the fmt header
  offset += 2;          // ignore the format type

  unsigned channels = buffer[offset + 1] << 8;
  channels |= buffer[offset];
  offset += 2;
  printf("Channels: %u\n", channels);

  unsigned frequency = buffer[offset + 3] << 24;
  frequency |= buffer[offset + 2] << 16;
  frequency |= buffer[offset + 1] << 8;
  frequency |= buffer[offset];
  offset += 4;
  printf("Frequency: %u\n", frequency);

  offset += 6; // ignore block size and bps

  unsigned bits = buffer[offset + 1] << 8;
  bits |= buffer[offset];
  offset += 2;
  printf("Bits: %u\n", bits);

  ALenum format = 0;
  if (bits == 8)
  {
    if (channels == 1)
      format = AL_FORMAT_MONO8;
    else if (channels == 2)
      format = AL_FORMAT_STEREO8;
  }
  else if (bits == 16)
  {
    if (channels == 1)
      format = AL_FORMAT_MONO16;
    else if (channels == 2)
      format = AL_FORMAT_STEREO16;
  }

  offset += 8; // ignore the data chunk

  printf("Start offset: %d\n", offset);

  alBufferData(buffers[0], format, &buffer[offset], size - offset, frequency);

#if defined(TEST_AL_SOFT_LOOP_POINTS)
  ALint loopPoints[] = {44100, 44100 * 2};
  ALint alLoopPointsSoft = alGetEnumValue("AL_LOOP_POINTS_SOFT");
  alBufferiv(buffers[0], alLoopPointsSoft, loopPoints);
#endif

  ALint val;
  alGetBufferi(buffers[0], AL_FREQUENCY, &val);
  alGetBufferi(buffers[0], AL_SIZE, &val);
  alGetBufferi(buffers[0], AL_BITS, &val);
  alGetBufferi(buffers[0], AL_CHANNELS, &val);

  ALuint sources[1];
  alGenSources(1, sources);

  alSourcei(sources[0], AL_BUFFER, buffers[0]);

  ALint state;
  alGetSourcei(sources[0], AL_SOURCE_STATE, &state);

  alSourcePlay(sources[0]);

  alGetSourcei(sources[0], AL_SOURCE_STATE, &state);

  printf("You should hear a short audio clip playing back.\n");

  emscripten_async_call(playSource, reinterpret_cast<void *>(sources[0]), 700);
  return 0;
}

extern "C" int main(int argc, char **argv)
{
  std::cout << "Main lancé" << std::endl;
  testAudio();
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
