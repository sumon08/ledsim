#ifndef LEDSIM_GRAPHICS_VERTEXBUFFER_HPP
#define LEDSIM_GRAPHICS_VERTEXBUFFER_HPP

#include <cstddef>

#include <glad/gl.h>

namespace LedSim::Graphics {

class VertexBuffer
{
public:
    VertexBuffer() = default;
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    bool Create(const void* data, std::size_t size);

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_id = 0;
};

} // namespace LedSim::Graphics

#endif