#pragma once
#include <GLAD/glad.h>
#include <string>


namespace Renderer 
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShaderSource,
					  const std::string& fragmentShaderSource);
		~ShaderProgram();
		ShaderProgram() = delete;

		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&& other) noexcept;
		ShaderProgram& operator = (ShaderProgram&& other) noexcept;

		bool isCompiled();
		void use();
		void setInt(const std::string& name, const GLint value);

	private:
		bool CreateShader(GLuint& shaderID, const GLenum shaderType, const GLchar* shaderSource);

		bool m_isCompiled = false;
		GLuint m_ID;
	};
}