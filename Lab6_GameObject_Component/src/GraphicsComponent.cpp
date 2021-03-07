#include "GraphicsComponent.hpp"
void GraphicsComponent::Render() {
  SDL_RenderCopy(renderer, m_texture, &m_src, &transform->getSDLRect());
}
void GraphicsComponent::LoadImage(std::string filePath) {
  SDL_Surface* m_spriteSheet = SDL_LoadBMP(filePath.c_str());
  if (nullptr == m_spriteSheet) {
    SDL_Log("Failed to allocate surface");
  } else {
    SDL_Log("Allocated a bunch of memory to create identical game character");
    // Create a texture from our surface
    // Textures run faster and take advantage
    // of hardware acceleration
    m_texture = SDL_CreateTextureFromSurface(renderer, m_spriteSheet);
    SDL_FreeSurface(m_spriteSheet);
    m_spriteSheet = nullptr;
  }
}