#include "LedSim/Graphics/IndexBuffer.hpp"

namespace LedSim::Graphics {

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
    if (m_id != 0)
    {
        glDeleteBuffers(1, &m_id);
    }
}

int IndexBuffer::Count() const
{
    return m_count;
}

bool IndexBuffer::Create(const unsigned int* data, std::size_t count)
{
    m_count = static_cast<GLsizei>(count);

    glGenBuffers(1, &m_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 count * sizeof(unsigned int),
                 data,
                 GL_STATIC_DRAW);

    return true;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLsizei IndexBuffer::GetCount() const
{
    return m_count;
}

} // namespace LedSim::Graphics