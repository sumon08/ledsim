#include "LedSim/Graphics/Shader.hpp"

#include <iostream>

namespace LedSim::Graphics {

Shader::Shader()
{
}

Shader::~Shader()
{
    if (m_program != 0)
    {
        glDeleteProgram(m_program);
    }
}

bool Shader::CompileShader(GLuint& shader,
                           GLenum type,
                           const char* source)
{
    shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[1024];

        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);

        std::cerr << log << '\n';

        glDeleteShader(shader);
        shader = 0;

        return false;
    }

    return true;
}

bool Shader::Create(const char* vertex_source,
                    const char* fragment_source)
{
    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;

    if (!CompileShader(vertex_shader,
                       GL_VERTEX_SHADER,
                       vertex_source))
    {
        return false;
    }

    if (!CompileShader(fragment_shader,
                       GL_FRAGMENT_SHADER,
                       fragment_source))
    {
        glDeleteShader(vertex_shader);
        return false;
    }

    m_program = glCreateProgram();

    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);

    glLinkProgram(m_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    GLint success = GL_FALSE;

    glGetProgramiv(m_program,
                   GL_LINK_STATUS,
                   &success);

    if (!success)
    {
        char log[1024];

        glGetProgramInfoLog(m_program,
                            sizeof(log),
                            nullptr,
                            log);

        std::cerr << log << '\n';

        glDeleteProgram(m_program);
        m_program = 0;

        return false;
    }

    return true;
}

void Shader::Bind() const
{
    glUseProgram(m_program);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

} // namespace LedSim::Graphics