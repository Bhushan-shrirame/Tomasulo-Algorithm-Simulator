
#include <vector>
#include "structure_class/instruction.h"
using namespace std;

void decoder(vector<Instruction>& instructions);


// gcc -o app main.cpp -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/opt/homebrew/Cellar/glfw/3.4/include -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -lglew -framework OpenGL