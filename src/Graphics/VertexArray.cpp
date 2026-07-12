#include "LedSim/Graphics/VertexArray.hpp"

namespace LedSim::Graphics {

VertexArray::VertexArray()
{
}

VertexArray::~VertexArray()
{
    if (m_id != 0)
    {
        glDeleteVertexArrays(1, &m_id);
    }
}

bool VertexArray::Create()
{
    glGenVertexArrays(1, &m_id);
    return true;
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

} // namespace LedSim::Graphics