

#ifndef LEDSIM_GRAPHICS_RENDERER_HPP
#define LEDSIM_GRAPHICS_RENDERER_HPP

#include "LedSim/Display/FrameBuffer.hpp"
#include "LedSim/Graphics/IndexBuffer.hpp"
#include "LedSim/Graphics/InstanceBuffer.hpp"
#include "LedSim/Graphics/InstanceData.hpp"
#include "LedSim/Graphics/LedInstance.hpp"
#include "LedSim/Graphics/Shader.hpp"
#include "LedSim/Graphics/VertexArray.hpp"
#include "LedSim/Graphics/VertexBuffer.hpp"
#include <vector>

namespace LedSim::Graphics {

class Renderer {
public:
  Renderer();
  ~Renderer();

  bool Initialize();

  void BeginFrame(int width, int height);
  void EndFrame();
  void Draw(const LedSim::Display::FrameBuffer& framebuffer);

private:
  Shader shader;

  VertexArray vao;
  VertexBuffer vbo;
  IndexBuffer ibo;

  InstanceBuffer instance_buffer;

  std::vector<LedInstance> led_positions;
  std::vector<InstanceData> instance_data;
  
};
} // namespace LedSim::Graphics

#endif // LEDSIM_GRAPHICS_RENDERER_HPP