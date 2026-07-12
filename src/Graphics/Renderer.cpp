#include "LedSim/Graphics/Renderer.hpp"
#include <GLFW/glfw3.h>
#include <glad/gl.h>

static constexpr float vertices[] = {
    // Position      UV
    -0.5f, -0.5f, 0.f, 0.f, 0.5f,  -0.5f, 1.f, 0.f,
    0.5f,  0.5f,  1.f, 1.f, -0.5f, 0.5f,  0.f, 1.f};

static constexpr unsigned int indices[] = {0, 1, 2, 2, 3, 0};

const char *vertex_shader = R"(
#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_uv;

layout(location = 2) in vec2 a_instance_position;
layout(location = 3) in vec3 a_instance_color;

out vec2 v_uv;
out vec3 v_color;

void main()
{
    const float led_size = 0.025;

    vec2 position =
        a_instance_position +
        a_position * led_size;

    gl_Position = vec4(position, 0.0, 1.0);

    v_uv = a_uv;
    v_color = a_instance_color;
}
)";

const char *fragment_shader = R"(#version 330 core

in vec2 v_uv;
in vec3 v_color;
out vec4 FragColor;

void main()
{
    // UV -> [-1, 1]
    vec2 p = v_uv * 2.0 - 1.0;

    // Temporary aspect correction
    p.x *= 1280.0 / 720.0;

    float d = length(p);

    // Outside LED
    if (d > 1.0)
        discard;

    //----------------------------------------------------
    // Plastic body
    //----------------------------------------------------

    vec3 body = vec3(0.10);

    //----------------------------------------------------
    // LED emitter
    //----------------------------------------------------

    float emitter = 1.0 - smoothstep(0.0, 0.65, d);

    //----------------------------------------------------
    // Inner glow
    //----------------------------------------------------

    float glow = exp(-5.0 * d);

    //----------------------------------------------------
    // Plastic rim
    //----------------------------------------------------

    float rim = smoothstep(0.75, 0.95, d);

    //----------------------------------------------------
    // Fake light reflection
    //----------------------------------------------------

    vec2 light = normalize(vec2(-0.4, -0.6));

    float spec = max(dot(normalize(vec3(p, sqrt(max(0.0, 1.0-d*d)))),
                         vec3(light, 1.0)), 0.0);

    spec = pow(spec, 40.0);

    //----------------------------------------------------
    // LED color
    //----------------------------------------------------

    vec3 ledColor = v_color;

    vec3 color = body;

    color += ledColor * emitter;
    color += ledColor * glow * 0.6;
    color += vec3(spec);
    color *= (1.0 - rim * 0.35);

    FragColor = vec4(color, 1.0);
}
)";

namespace LedSim::Graphics {
constexpr GLuint ATTR_POSITION = 0;
constexpr GLuint ATTR_UV = 1;
constexpr GLuint ATTR_INSTANCE_POSITION = 2;
constexpr GLuint ATTR_INSTANCE_COLOR = 3;
} // namespace LedSim::Graphics

LedSim::Graphics::Renderer::Renderer() {}

LedSim::Graphics::Renderer::~Renderer() {}

bool LedSim::Graphics::Renderer::Initialize()
{
    if (!shader.Create(vertex_shader, fragment_shader))
    {
        return false;
    }

    vao.Create();
    vao.Bind();

    //--------------------------------------------------------------------------
    // Create geometry
    //--------------------------------------------------------------------------

    vbo.Create(vertices, sizeof(vertices));
    ibo.Create(indices, 6);

    //--------------------------------------------------------------------------
    // Generate LED instances
    //--------------------------------------------------------------------------

    constexpr int PANEL_WIDTH  = 64;
    constexpr int PANEL_HEIGHT = 32;

    const float x_step = 1.90f / static_cast<float>(PANEL_WIDTH - 1);
    const float y_step = 1.90f / static_cast<float>(PANEL_HEIGHT - 1);

    led_positions.reserve(PANEL_WIDTH * PANEL_HEIGHT);

    for (int y = 0; y < PANEL_HEIGHT; ++y)
    {
        for (int x = 0; x < PANEL_WIDTH; ++x)
        {
            LedInstance led;

            led.x = -0.95f + static_cast<float>(x) * x_step;
            led.y =  0.95f - static_cast<float>(y) * y_step;

            led_positions.push_back(led);
        }
    }

    instance_buffer.Create(
        led_positions.data(),
        sizeof(LedInstance) * led_positions.size());

    //==========================================================================
    // Vertex attributes (VBO)
    //==========================================================================

    vbo.Bind();

    glEnableVertexAttribArray(ATTR_POSITION);
    glVertexAttribPointer(
        ATTR_POSITION,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        nullptr);

    glEnableVertexAttribArray(ATTR_UV);
    glVertexAttribPointer(
        ATTR_UV,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        reinterpret_cast<void*>(2 * sizeof(float)));

    //==========================================================================
    // Instance attributes (InstanceBuffer)
    //==========================================================================

    instance_buffer.Bind();

    glEnableVertexAttribArray(ATTR_INSTANCE_POSITION);
    glVertexAttribPointer(
        ATTR_INSTANCE_POSITION,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(LedInstance),
        nullptr);
    glVertexAttribDivisor(ATTR_INSTANCE_POSITION, 1);

    glEnableVertexAttribArray(ATTR_INSTANCE_COLOR);
    glVertexAttribPointer(
        ATTR_INSTANCE_COLOR,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(LedInstance),
        reinterpret_cast<void*>(2 * sizeof(float)));
    glVertexAttribDivisor(ATTR_INSTANCE_COLOR, 1);

    vao.Unbind();

    return true;
}

void LedSim::Graphics::Renderer::BeginFrame(int width, int height) {
  glViewport(0, 0, width, height);

  glClearColor(0.08f, 0.08f, 0.08f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  shader.Bind();

  vao.Bind();

  glDrawElementsInstanced(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT,
                          nullptr, static_cast<GLsizei>(led_positions.size()));

  vao.Unbind();

  shader.Unbind();
}


void LedSim::Graphics::Renderer::Draw(
    const LedSim::Display::FrameBuffer& framebuffer)
{
    instance_data.clear();

    instance_data.reserve(led_positions.size());

    for (std::size_t i = 0; i < led_positions.size(); ++i)
    {
        InstanceData instance;

        instance.x = led_positions[i].x;
        instance.y = led_positions[i].y;

        const auto& pixel = framebuffer.Data()[i];

        instance.r = static_cast<float>(pixel.red) / 255.0f;
        instance.g = static_cast<float>(pixel.green) / 255.0f;
        instance.b = static_cast<float>(pixel.blue) / 255.0f;

        instance_data.push_back(instance);
    }

    instance_buffer.Update(
        instance_data.data(),
        sizeof(InstanceData) * instance_data.size());

    shader.Bind();
    vao.Bind();

    glDrawElementsInstanced(
        GL_TRIANGLES,
        ibo.Count(),
        GL_UNSIGNED_INT,
        nullptr,
        static_cast<GLsizei>(instance_data.size()));
}

void LedSim::Graphics::Renderer::EndFrame() {}