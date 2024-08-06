#include "ShaderProgram.h"
#include <iostream>


namespace Renderer 
{
	ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, 
                                 const std::string& fragmentShaderSource)
	{
        GLuint vertexShader;
        if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderSource.c_str()))
        {
            std::cerr << "VERTEX SHADER compile time error" << std::endl;
            system("pause");
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource.c_str()))
        {
            std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
            system("pause");
            glDeleteShader(vertexShader);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShader);
        glAttachShader(m_ID, fragmentShader);
        glLinkProgram(m_ID);

        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
            system("pause");
        }
        else
            m_isCompiled = true;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
	}


    bool ShaderProgram::CreateShader(GLuint& shaderID, 
        const GLenum shaderType, const GLchar* shaderSource)
    {
        shaderID = glCreateShader(shaderType);
        glShaderSource(shaderID, 1, &shaderSource, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
            system("pause");
            return false;
        }
        return true;
    }


    ShaderProgram::~ShaderProgram() { glDeleteProgram(m_ID); }


    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    {
        m_ID = other.m_ID;
        m_isCompiled = other.m_isCompiled;

        other.m_ID = 0;
        other.m_isCompiled = 0;
    }


    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = other.m_ID;
        m_isCompiled = other.m_isCompiled;

        other.m_ID = 0;
        other.m_isCompiled = 0;

        return *this;
    }


    bool ShaderProgram::isCompiled() { return m_isCompiled; }
    void ShaderProgram::use() { glUseProgram(m_ID); }

    void ShaderProgram::setInt(const std::string& name, const GLint value)
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

}