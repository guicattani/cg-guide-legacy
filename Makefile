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
SOURCES += ./src/matrices.cpp ./src/callbacks.cpp ./src/interface.cpp ./src/camera.cpp ./src/opengl_loader.cpp
SOURCES += ./src/model_loader.cpp
SOURCES += ./src/scene_loader.cpp ./src/scene_2.cpp ./src/scene_2_interface.cpp \
																	./src/scene_3.cpp ./src/scene_3_interface.cpp \
																	./src/scene_4.cpp ./src/scene_4_interface.cpp \
																	./src/scene_5.cpp ./src/scene_5_interface.cpp

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

CXXFLAGS += -I./libs/imgui  -I./libs/tiny_obj_loader -I./libs/KHR/ -I./libs/glfw/include

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL `pkg-config --static --libs glfw3`

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
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32 -lsoil2

	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

OBJS = $(addsuffix .o, $(basename $(addprefix $(BIN)/,$(notdir $(SOURCES)))))

$(BIN)/%.o:./src/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

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

run:
	cd ./bin;	./$(EXE);

clean:
ifeq ($(OS),Windows_NT)
	del /s "*.exe" "*.o"
else
	rm -rf $(EXE) $(OBJS);
	cd ./bin;	rm -rf $(EXE) $(OBJS);
endif
