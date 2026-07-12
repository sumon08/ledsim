#ifndef LEDSIM_GRAPHICS_VERTEXARRAY_HPP
#define LEDSIM_GRAPHICS_VERTEXARRAY_HPP

#include <glad/gl.h>

namespace LedSim::Graphics {

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    bool Create();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_id = 0;
};

} // namespace LedSim::Graphics

#endif