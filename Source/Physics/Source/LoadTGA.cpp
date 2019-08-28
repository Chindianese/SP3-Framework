#include <iostream>
#include <fstream>
#include <GL\glew.h>

#include "LoadTGA.h"
#include "Resources.h"

#include "Preferences.h"
GLuint LoadTGA(std::string path)				// load TGA file to memory
{
	std::string sQuality = Preferences::GetPref(Resources::PreferencesTerm::Quality);
	std::ifstream fileStream;
	if (sQuality == "HIGH")
	{
		std::string file_path = Resources::Path::Texture + sQuality + '/' + path + ".tga";
		fileStream.open(file_path, std::ios::binary);
		if (!fileStream.is_open())
		{
			//std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
			std::string error = "Unable to load texture at ";
			error += file_path;
			error += " for HIGH preset.";
			error += ".";
			DEFAULT_LOG(error);
			return 0;
		}
	}
	else if (sQuality == "LOW")
	{
		// Attempt to load LOW qual first,  if fail, use HIGH
		std::string file_path = Resources::Path::Texture + sQuality + '/' + path + ".tga";
		fileStream.open(file_path, std::ios::binary);
		if (!fileStream.is_open())
		{
			std::string file_path = Resources::Path::Texture + "HIGH" + '/' + path + ".tga";
			fileStream.open(file_path, std::ios::binary);
			if (!fileStream.is_open())
			{
				//std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
				std::string error = "Unable to load texture at ";
				error += file_path;
				error += " for LOW & HIGH preset.";
				error += ".";
				DEFAULT_LOG(error);
				return 0;
			}
		}
	}

	GLubyte		header[18];									// first 6 useful header bytes
	GLuint		bytesPerPixel;								    // number of bytes per pixel in TGA gile
	GLuint		imageSize;									    // for setting memory
	GLubyte *	data;
	GLuint		texture = 0;
	unsigned	width, height;

	fileStream.read((char*)header, 18);
	width = header[12] + header[13] * 256;
	height = header[14] + header[15] * 256;

	if (width <= 0 ||								// is width <= 0
		height <= 0 ||								// is height <=0
		(header[16] != 24 && header[16] != 32))		// is TGA 24 or 32 Bit
	{
		fileStream.close();							// close file on failure
		std::cout << "File header error.\n";
		return 0;
	}

	bytesPerPixel = header[16] / 8;						//divide by 8 to get bytes per pixel
	imageSize = width * height * bytesPerPixel;	// calculate memory required for TGA data

	data = new GLubyte[imageSize];
	fileStream.seekg(18, std::ios::beg);
	fileStream.read((char *)data, imageSize);
	fileStream.close();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (bytesPerPixel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	else //bytesPerPixel == 4
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	float maxAnisotropy = 1.f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, (GLint)maxAnisotropy);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);

	delete[]data;

	return texture;
}