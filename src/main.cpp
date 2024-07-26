#include <GLAD/glad.h>
#include <GLFW/glfw3.h>


int g_windowSizeX = 500;
int g_windowSizeY = 500;


void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

void glfwKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
}


int main()
{
    GLFWwindow* pWindow;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(640, 480, "BattleCity", nullptr, nullptr);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack);
    glfwSetKeyCallback(pWindow, glfwKeyCallBack);

    if (!gladLoadGL()) 
        return -1;

    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

