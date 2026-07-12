#include "LedSim/Graphics/InstanceBuffer.hpp"

namespace LedSim::Graphics {

InstanceBuffer::InstanceBuffer()
{
}

InstanceBuffer::~InstanceBuffer()
{
    if (m_id)
    {
        glDeleteBuffers(1, &m_id);
    }
}

bool InstanceBuffer::Create(const void* data,
                            std::size_t size)
{
    glGenBuffers(1, &m_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_id);

    glBufferData(GL_ARRAY_BUFFER,
                 size,
                 data,
                 GL_DYNAMIC_DRAW);

    return true;
}

void InstanceBuffer::Update(const void* data,
                            std::size_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);

    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    size,
                    data);
}

void InstanceBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void InstanceBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}