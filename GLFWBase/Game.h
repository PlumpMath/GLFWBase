#ifndef __GLFWBase__Game__
#define __GLFWBase__Game__

#include <stdio.h>

class GLFWwindow;

class Game {
    GLFWwindow *window;
public:
    Game(GLFWwindow *window);
    void run();
};

#endif
