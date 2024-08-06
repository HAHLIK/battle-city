#pragma once

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"

#include <string>
#include <memory>
#include <map>


class ResourceManager
{
public:
	ResourceManager(std::string& executablePath);
	~ResourceManager() = default;

	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator= (ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShader
		(const std::string& shaderProgramName,
		 const std::string& vertexShaderPath, 
		 const std::string& fragmentShaderPath);

	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram
		(const std::string& shaderProgramName);

	std::shared_ptr<Renderer::Texture2D> loadTexture2D
		(const std::string& textureName,
		 const std::string& texturePath);

	std::shared_ptr<Renderer::Texture2D> getTexture2D
		(const std::string& textureName);


private:
	typedef std::map <const std::string,
			std::shared_ptr<Renderer::ShaderProgram> >		mapShaderProgram;

	typedef std::map <const std::string,
		std::shared_ptr<Renderer::Texture2D> >				mapTexture2D;

	void getFileString(const std::string& reletiveFilePath, std::string& recordString);

	const std::string m_executablePath;
	mapShaderProgram  m_shaderPrograms;
	mapTexture2D	  m_textures2D;
};