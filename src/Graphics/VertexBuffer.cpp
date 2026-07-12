#include "LedSim/Graphics/VertexBuffer.hpp"

namespace LedSim::Graphics {

VertexBuffer::~VertexBuffer()
{
    if (m_id != 0)
    {
        glDeleteBuffers(1, &m_id);
    }
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
{
    m_id = other.m_id;
    other.m_id = 0;
}

VertexBuffer&
VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this != &other)
    {
        if (m_id != 0)
        {
            glDeleteBuffers(1, &m_id);
        }

        m_id = other.m_id;
        other.m_id = 0;
    }

    return *this;
}

bool VertexBuffer::Create(const void* data,
                          std::size_t size)
{
    glGenBuffers(1, &m_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_id);

    glBufferData(GL_ARRAY_BUFFER,
                 size,
                 data,
                 GL_STATIC_DRAW);

    return true;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace LedSim::Graphics