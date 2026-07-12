#ifndef LEDSIM_GRAPHICS_SHADER_HPP
#define LEDSIM_GRAPHICS_SHADER_HPP

#include <string>

#include <glad/gl.h>

namespace LedSim::Graphics {

class Shader
{
public:
    Shader();
    ~Shader();

    bool Create(const char* vertex_source, const char* fragment_source);

    void Bind() const;
    void Unbind() const;

private:
    bool CompileShader(GLuint& shader, GLenum type, const char* source);

private:
    GLuint m_program = 0;
};

} // namespace LedSim::Graphics

#endif // LEDSIM_GRAPHICS_SHADER_HPP