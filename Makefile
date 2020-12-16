CXX = emcc
OUTPUT = Dist/main.js
IMGUI_DIR:=../imgui
LOCAL_IMGUI_DIR:=./Imgui

SOURCES = App.cpp Engine/Engine.cpp Engine/Audio/AudioPlayer.cpp Engine/Window/ChildWindow.cpp Engine/MalStudio/MalStudio.cpp Engine/Common/config.cpp
SOURCES += $(LOCAL_IMGUI_DIR)/imgui_impl_glfw.cpp $(LOCAL_IMGUI_DIR)/imgui_impl_opengl3.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_widgets.cpp

LIBS = -lGL
WEBGL_VER = -s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1
#WEBGL_VER = USE_GLFW=2
USE_WASM = -s WASM=1

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES) 
	$(CXX)   -Wall $(SOURCES) -std=c++11 -o $(OUTPUT) $(LIBS) $(WEBGL_VER) -O2 --preload-file data $(USE_WASM) -I$(IMGUI_DIR) -Iressources -s ASSERTIONS=1 -s LLD_REPORT_UNDEFINED
	


clean:
	rm -f $(OUTPUT)
