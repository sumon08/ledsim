#ifndef LEDSIM_GRAPHICS_INDEXBUFFER_HPP
#define LEDSIM_GRAPHICS_INDEXBUFFER_HPP

#include <cstddef>

#include <glad/gl.h>

namespace LedSim::Graphics {

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    bool Create(const unsigned int* data, std::size_t count);

    void Bind() const;
    void Unbind() const;

    int Count() const;

    GLsizei GetCount() const;

private:
    GLuint m_id = 0;
    GLsizei m_count = 0;
};

} // namespace LedSim::Graphics

#endif