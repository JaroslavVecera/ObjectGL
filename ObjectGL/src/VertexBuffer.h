#pragma once

class VertexBuffer
{
    private:
        unsigned int m_RendererID;

    public:
        VertexBuffer(unsigned int verticies, unsigned int vertex_size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
        void AddData() const;
};
