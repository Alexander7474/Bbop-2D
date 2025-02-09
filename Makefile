CC = g++
#comment this if you are on macOS
CFLAGS = -std=c++11 -Wall -I/usr/include/freetype2 -g
LIBS = -lglfw3 -lGLEW -lGL -lfreetype -lLDtkLoader

#Uncomment if you use macOS or if you are gay
#CFLAGS = -std=c++11 -Wall -I/opt/homebrew/Cellar/freetype/2.13.2/include/freetype2 -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/usr/local/include/GLFW
#LIBS = -L/opt/homebrew/Cellar/freetype/2.13.2/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -framework Cocoa -framework OpenGL -framework IOKit -lfreetype -lglfw3 -lGLEW.2.2.0

SRCS = src/BBOP/Graphics/bbopFunc.cpp src/BBOP/Graphics/fontsClass.cpp src/BBOP/Graphics/shaders.cpp src/BBOP/Graphics/bbopMathClass.cpp src/BBOP/Graphics/bbopGlobal.cpp src/BBOP/Graphics/sceneClass.cpp src/BBOP/Graphics/cameraClass.cpp src/BBOP/Graphics/shaderClass.cpp src/BBOP/Graphics/textureClass.cpp src/BBOP/Graphics/VBO.cpp src/BBOP/Graphics/VAO.cpp src/BBOP/Graphics/EBO.cpp src/BBOP/Graphics/spriteClass.cpp src/BBOP/Graphics/collisionBoxClass.cpp src/BBOP/Graphics/shapeClass.cpp src/BBOP/Performance/benchmark.cpp src/BBOP/Graphics/lightClass.cpp src/BBOP/Graphics/geometricClass.cpp src/BBOP/Graphics/animatedSpriteClass.cpp src/BBOP/Graphics/mapClass.cpp
SRCSM = main.cpp

OBJS = $(SRCSM:.cpp=.o) $(SRCS:.cpp=.o)
OBJSNM = $(SRCS:.cpp=.o) 

GREEN = \033[0;32m
CYAN = \033[0;36m
PURPLE = \033[0;35m
NC = \033[0m

all: final

final: $(OBJS)
	@echo -e "$(PURPLE)Linking compiled files $(NC)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo -e "$(GREEN)Linkage done ! $(NC)"

%.o: %.cpp
	@echo -e "$(GREEN)Compiling $(CYAN)[$@] $(NC)"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo -e "$(PURPLE)Deleting all objects files and final$(NC)"
	@rm -f final libbbop.a $(OBJS)

lib:
	@echo -e "$(PURPLE)Making $(CYAN)[libbbop.a]$(NC)"
	@ar rcs libbbop.a $(OBJSNM)
	@echo -e "$(CYAN)[libbbop.a]$(GREEN) created !$(NC)"

install:
	@echo -e "$(PURPLE)Making $(CYAN)[libbbop.a]$(NC)"
	@ar rcs libbbop.a $(OBJSNM)
	@echo -e "$(CYAN)[libbbop.a]$(GREEN) created !$(NC)"
	@echo -e "$(PURPLE)Moving include to $(CYAN)[/usr/local/include/]$(NC)"
	@cp -r include/BBOP /usr/local/include/
	@echo -e "$(GREEN)Move done !$(NC)"
	@echo -e "$(PURPLE)Moving $(CYAN)[libbbop.a]$(GREEN) to $(CYAN)[/usr/local/lib/]$(NC)"
	@mv libbbop.a /usr/local/lib/
	@echo -e "$(GREEN)Move done !$(NC)"

uninstall:
	@rm /usr/local/lib/libbbop.a
	@rm -rf /usr/local/include/BBOP

update:
	make clean
	make
	sudo make install
