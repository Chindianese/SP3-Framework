#pragma once

#include <GL/glew.h>

class ColorFBO
{
public:
	ColorFBO();
	~ColorFBO();

	bool Init(unsigned width, unsigned height);
	void BindForWriting();
	void BindForReading(GLenum textureUnit);

	GLuint GetFBO() { return m_fbo; }
	GLuint GetTexture() { return m_texture; }
	unsigned GetWidth() { return m_width; }
	unsigned GetHeight() { return m_height; }

private:
	GLuint m_fbo;		// The frame buffer object, to be written to
	GLuint m_texture;	// Color texture, to be sampled later in your shader
	unsigned m_width;
	unsigned m_height;
};