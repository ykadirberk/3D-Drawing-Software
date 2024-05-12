#include "FrameBufferTexture.h"
#include "../CoreGL.h"
dra::FrameBufferTexture::FrameBufferTexture(int width, int height) : m_Width(width), m_Height(height)
{
	m_FrameBufferId = 0;
	GLCall(glGenFramebuffers(1, &m_FrameBufferId));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId));

	m_TextureId = 0;
	GLCall(glGenTextures(1, &m_TextureId));

	// "Bind" the newly created texture : all future texture functions will modify this texture
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));

	// Give an empty image to OpenGL ( the last "0" )
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0));

	// Poor filtering. Needed !
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

	// Set "renderedTexture" as our colour attachement #0
	GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_TextureId, 0));

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	GLCall(glDrawBuffers(1, DrawBuffers)); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw;

}

unsigned char* dra::FrameBufferTexture::GetPixelArray()
{
	BindFrameBuffer();
	if (nullptr != m_LastPixelArray) {
		delete m_LastPixelArray;
		m_LastPixelArray = nullptr;
	}
	
	m_LastPixelArray = new unsigned char[m_Width * m_Height * 4];

	GLCall(glReadPixels(0,0,m_Width,m_Height, GL_RGBA, GL_UNSIGNED_BYTE, (void*)m_LastPixelArray));
	UnbindFrameBuffer();

	return m_LastPixelArray;
}

void dra::FrameBufferTexture::BindTexture()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));
}

void dra::FrameBufferTexture::UnbindTexture()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void dra::FrameBufferTexture::BindFrameBuffer()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId));
	glViewport(0, 0, m_Width, m_Height);
}

void dra::FrameBufferTexture::UnbindFrameBuffer()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	glViewport(0, 0, m_Width, m_Height);
}
