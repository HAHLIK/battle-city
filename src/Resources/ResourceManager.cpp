#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"

#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "..\Resources\stb_image.h"


ResourceManager::ResourceManager(std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	const std::string m_path = executablePath.substr(0, found);
}


std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShader(
	const std::string& shaderProgramName,
	const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::string vertexShaderSource;
	getFileString(vertexShaderPath, vertexShaderSource);
	if (vertexShaderSource.empty()){
		std::cerr << "ERROR::SHADER: Load-time error:\nvertexShaderSource";
		system("pause");
		return nullptr;
	}

	std::string fragmentShaderSource;
	getFileString(fragmentShaderPath, fragmentShaderSource);
	if (fragmentShaderSource.empty()) {
		std::cerr << "ERROR::SHADER: Load-time error:\nfragmentShaderSource";
		system("pause");
		return nullptr;
	}

	auto newShaderProgram = m_shaderPrograms.emplace(shaderProgramName, 
		std::shared_ptr<Renderer::ShaderProgram> (new Renderer::ShaderProgram (
		vertexShaderSource, fragmentShaderSource))). first->second;

	if (newShaderProgram->isCompiled())
		return newShaderProgram;
	else 
		return nullptr;
}


std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram
	(const std::string& shaderProgramName)
{
	auto it = m_shaderPrograms.find(shaderProgramName);
	if (it != m_shaderPrograms.cend())
		return it->second;

	std::cerr << "Can't find the shaderProgram";
	system("pause");
	return nullptr;
}


void ResourceManager::getFileString(const std::string& reletiveFilePath, 
										  std::string& recordString)
{
	std::fstream f;
	f.open(m_executablePath+reletiveFilePath);
	if (f.is_open()) 
		std::getline(f, recordString, '\0');

	f.close();

}


std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture2D
			(const std::string& textureName,
			 const std::string& texturePath)
{
	int channels = 0;
	int width = 0, height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load((m_executablePath + texturePath).c_str(), 
		&width, &height, &channels, 0);

	auto newTexture2D = m_textures2D.emplace(textureName, 
		std::shared_ptr<Renderer::Texture2D>(new Renderer::Texture2D(
		width, height, pixels, channels))).first->second;

	if (!pixels) {
		std::cerr << "Can't load image" << texturePath << std::endl;
		return nullptr;
	}
	stbi_image_free(pixels);
	return newTexture2D;
}


std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture2D
	(const std::string& textureName)
{
	auto it = m_textures2D.find(textureName);
	if (it != m_textures2D.cend())
		return it->second;

	std::cerr << "Cant't find texture";
	system("pause");
	return nullptr;
}