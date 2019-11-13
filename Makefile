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

#CXX = g++
#CXX = clang++

EXE = example_imgui
SOURCES = ./src/main.cpp
SOURCES += ./src/callbacks.cpp ./src/shaders.cpp
SOURCES += ./libs/imgui/imgui_impl_glfw.cpp ./libs/imgui/imgui_impl_opengl3.cpp
SOURCES += ./libs/imgui/imgui.cpp ./libs/imgui/imgui_demo.cpp ./libs/imgui/imgui_draw.cpp ./libs/imgui/imgui_widgets.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

INCLUDE	:= include
LIB		:= libs

CXXFLAGS = -I./src/imgui
CXXFLAGS += -g -Wall -Wformat -Wno-unknown-pragmas
LIBS =

##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

## Using OpenGL loader: gl3w [default]
SOURCES += ./libs/gl3w/GL/gl3w.c
CXXFLAGS += -I./libs/gl3w

## Using OpenGL loader: glew
## (This assumes a system-wide installation)
CXXFLAGS += -lGLEW -DIMGUI_IMPL_OPENGL_LOADER_GLEW

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

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

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:./src/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c -o $@ $<

%.o:./src/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:./libs/gl3w/GL/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(EXE)
	mv $(OBJS) ./bin/
	mv $(EXE) ./bin/
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

run: all
	cd ./bin/
	./$(EXECUTABLE)

clean:
	cd ./bin/
	rm -f $(EXE) $(OBJS)
