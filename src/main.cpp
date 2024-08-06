#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Resources/ResourceManager.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"


int g_windowSizeX = 256;
int g_windowSizeY = 256;


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


GLfloat vertex[] = { 0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 
                    -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,  
                     0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f };   


int main(int argc, char** argv)
{
    GLFWwindow* pWindow;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "BattleCity", nullptr, nullptr);
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


    {
        ResourceManager resourceManager((std::string)argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShader("DefaultShaderProgram",
            "res/shaders/vertex_shader.txt",
            "res/shaders/fragment_shader.txt");
        auto MapTexture = resourceManager.loadTexture2D("MapTexture", 
            "res/textures/map.png");


        GLfloat vertexs[] = {
             1.0f,  1.0f, 0.0f,     //right top
             1.0f, -1.0f, 0.0f,     //right bottom
            -1.0f, -1.0f, 0.0f,     //left bottom
            -1.0f,  1.0f, 0.0f,     //right top
        };
        GLfloat texure_points[] = {
            1.0f, 1.0f,     //right top
            1.0f, 0.0f,     //right bottom
            0.0f, 0.0f,     //left bottom
            0.0f, 1.0f,     //right top
        };


        GLuint vertex_VBO;
        glGenBuffers(1, &vertex_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);

        GLuint texture_VBO;
        glGenBuffers(1, &texture_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texure_points), texure_points, GL_STATIC_DRAW);

        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        // Game loop
        while (!glfwWindowShouldClose(pWindow))
        {
            glfwPollEvents();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            pDefaultShaderProgram->use();

            glBindVertexArray(VAO);
                MapTexture->bind();
                glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            glfwSwapBuffers(pWindow);
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &vertex_VBO);
        glDeleteBuffers(1, &texture_VBO);
    }
    glfwTerminate();
    return 0;
}