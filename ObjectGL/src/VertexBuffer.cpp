#include "VertexBuffer.h"
#include "Debug.h"

VertexBuffer::VertexBuffer(unsigned int verticies, unsigned int vertex_size)
{
    GLCall( glGenBuffers(1, &m_RendererID) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
    GLCall( glBufferData(GL_ARRAY_BUFFER, verticies * vertex_size, nullptr, GL_DYNAMIC_DRAW) );
}

VertexBuffer::~VertexBuffer()
{
    GLCall( glDeleteBuffers(1, &m_RendererID) );
}

void VertexBuffer::Bind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
}

void VertexBuffer::Unbind() const
{
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}
