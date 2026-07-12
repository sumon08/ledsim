#ifndef LEDSIM_GRAPHICS_INSTANCEBUFFER_HPP
#define LEDSIM_GRAPHICS_INSTANCEBUFFER_HPP

#include <cstddef>

#include <glad/gl.h>

namespace LedSim::Graphics {

class InstanceBuffer
{
public:

    InstanceBuffer();
    ~InstanceBuffer();

    InstanceBuffer(const InstanceBuffer&) = delete;
    InstanceBuffer& operator=(const InstanceBuffer&) = delete;

    bool Create(const void* data,
                std::size_t size);

    void Update(const void* data,
                std::size_t size);

    void Bind() const;
    void Unbind() const;

private:

    GLuint m_id = 0;
};

}

#endif