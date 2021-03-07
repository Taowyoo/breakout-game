#include "TileMapGraphicsComponent.hpp"

#include <iomanip>
#include <iostream>
TileMapGraphicsComponent::TileMapGraphicsComponent(
    SDL_Renderer* g_renderer, TransformComponent* tf, int rows, int cols,
    int _TileWidth, int _TileHeight, int _mapX, int _mapY) :GraphicsComponent{g_renderer,tf}{
  // Setup variables
  m_Rows = rows;
  m_Cols = cols;
  m_TileWidth = _TileWidth;
  m_TileHeight = _TileHeight;
  m_MapX = _mapX;
  m_MapY = _mapY;
  // Setup the TileMap array
  // This sets each tile to '0'
  m_Tiles = new int[m_MapX * m_MapY];
  for (int i = 0; i < m_MapX * m_MapY; i++) {
    m_Tiles[i] = -1;  // Default value is no tile.
  }
}
TileMapGraphicsComponent::~TileMapGraphicsComponent() { delete[] m_Tiles; }

void TileMapGraphicsComponent::update() {
  TileMapGraphicsComponent::Render();
}

// Helper function to gegenerate a simlpe map
void TileMapGraphicsComponent::GenerateSimpleMap() {
  for (int y = 0; y < m_MapY; y++) {
    for (int x = 0; x < m_MapX; x++) {
      if (y == 0) {
        SetTile(x, y, 12);
      }
      if (y == m_MapY - 1) {
        SetTile(x, y, 0);
      }
    }
  }
}

// Helper function to print out the tile map
// to the console
void TileMapGraphicsComponent::PrintMap() {
  for (int y = 0; y < m_MapY; y++) {
    for (int x = 0; x < m_MapX; x++) {
      std::cout << std::setw(3) << GetTileType(x, y);
    }
    std::cout << "\n";
  }
}

// Sets a tile a certain type
void TileMapGraphicsComponent::SetTile(int x, int y, int type) {
  m_Tiles[y * m_MapX + x] = type;
}

// Returns what the tile is at a specific position.
int TileMapGraphicsComponent::GetTileType(int x, int y) {
  return m_Tiles[y * m_MapX + x];
}

// render TileMap
void TileMapGraphicsComponent::Render() {
  SDL_Rect Src, Dest;
  int tf_x = transform->getSDLRect().x;
  int tf_y = transform->getSDLRect().y;
  for (int y = 0; y < m_MapY; y++) {
    for (int x = 0; x < m_MapX; x++) {
      // Select our Tile
      int currentTile = GetTileType(x, y);
      if (currentTile > -1) {
        // Reverse lookup, given the tile type
        // and then figuring out how to select it
        // from the texture atlas.
        Src.x = (currentTile % m_Cols) * m_TileWidth;
        Src.y = (currentTile / m_Rows) * m_TileHeight;
        Src.w = m_TileWidth;
        Src.h = m_TileHeight;
        // Render our Tile at this location
        Dest.x = x * m_TileWidth + tf_x;
        Dest.y = y * m_TileHeight + tf_y;
        Dest.w = m_TileWidth;
        Dest.h = m_TileHeight;
        SDL_RenderCopy(renderer, m_texture, &Src, &Dest);
      }
    }
  }
}
