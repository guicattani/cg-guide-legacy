#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

CXX = g++
#CXX = clang++
CC  = gcc

BIN=./bin

EXE = main
SOURCES = ./src/main.cpp
SOURCES += ./src/matrices.cpp ./src/bezier.cpp ./src/callbacks.cpp ./src/interface.cpp ./src/camera.cpp ./src/opengl_loader.cpp
SOURCES += ./src/model_loader.cpp

### TODO paths are wrong but it still works?
SOURCES += ./src/scenes/scene_1.cpp ./src/scenes/scene_1_interface.cpp \
				   ./src/scenes/scene_2.cpp ./src/scenes/scene_2_interface.cpp \
				   ./src/scenes/scene_3.cpp ./src/scenes/scene_3_interface.cpp \
				   ./src/scenes/scene_4.cpp ./src/scenes/scene_4_interface.cpp \
				   ./src/scenes/scene_5.cpp ./src/scenes/scene_5_interface.cpp \
				   ./src/scenes/scene_6.cpp ./src/scenes/scene_6_interface.cpp \
				   ./src/scenes/scene_7.cpp ./src/scenes/scene_7_interface.cpp \
				   ./src/scenes/scene_8.cpp ./src/scenes/scene_8_interface.cpp \
				   ./src/scenes/scene_9.cpp ./src/scenes/scene_9_interface.cpp \
				   ./src/scenes/scene_10.cpp ./src/scenes/scene_10_interface.cpp

INCLUDE	:= ./include
LIB		  := ./lib

CXXFLAGS = -g -Wall -Wformat -Wno-unknown-pragmas

##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

## Using OpenGL loader: gl3w [default]
SOURCES  += ./libs/gl3w/GL/gl3w.c
CXXFLAGS += -I./libs/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W

##---------------------------------------------------------------------
## EXTERNAL LIBS
##---------------------------------------------------------------------

SOURCES += ./libs/tiny_obj_loader/tiny_obj_loader.cpp
SOURCES += ./libs/imgui/imgui_impl_glfw.cpp ./libs/imgui/imgui_impl_opengl3.cpp
SOURCES += ./libs/imgui/imgui.cpp ./libs/imgui/imgui_demo.cpp ./libs/imgui/imgui_draw.cpp ./libs/imgui/imgui_widgets.cpp

CXXFLAGS += -I./libs/imgui -I./libs/tiny_obj_loader -I./libs/KHR/ -I./libs/glfw/include

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL `pkg-config --static --libs glfw3 freetype2`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/local/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS),Windows_NT)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lfreetype -lgdi32 -lopengl32 -limm32

	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

OBJS = $(addsuffix .o, $(basename $(addprefix $(BIN)/,$(notdir $(SOURCES)))))

## Make release build by calling: make RELEASE=1
## necessary folders are:
## 	./data
## 	./misc
## 	./src/scenes/** (only *.vert and *.frag)
##
ifeq ($(RELEASE),1)
   CXXFLAGS += -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive
	 LIBS += -static-libgcc -static-libstdc++
endif

$(BIN)/%.o:./src/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### TODO find a way to improve this
####################### Scenes
### Scene 1
$(BIN)/%.o:./src/scenes/scene_1/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 2
$(BIN)/%.o:./src/scenes/scene_2/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 3
$(BIN)/%.o:./src/scenes/scene_3/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 4
$(BIN)/%.o:./src/scenes/scene_4/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 5
$(BIN)/%.o:./src/scenes/scene_5/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 6
$(BIN)/%.o:./src/scenes/scene_6/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 7
$(BIN)/%.o:./src/scenes/scene_7/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 8
$(BIN)/%.o:./src/scenes/scene_8/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 9
$(BIN)/%.o:./src/scenes/scene_9/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

### Scene 10
$(BIN)/%.o:./src/scenes/scene_10/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

####################### End Scenes
$(BIN)/%.o:./libs/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

$(BIN)/%.o:./libs/tiny_obj_loader/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN)/%.o:./libs/gl3w/GL/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ $<

all: $(BIN)/$(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(BIN)/$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) -L$(LIB) $(LIBS)

release: all


run:
	cd ./bin;	./$(EXE);

clean:
ifeq ($(OS),Windows_NT)
	del /s "*.exe" "*.o"
else
	rm -rf $(EXE) $(OBJS);
	cd ./bin;	rm -rf $(EXE) $(OBJS);
endif
