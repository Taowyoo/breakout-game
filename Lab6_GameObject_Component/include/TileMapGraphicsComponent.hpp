#ifndef TILEMAPGRAPHICSCOMPONENT_HPP
#define TILEMAPGRAPHICSCOMPONENT_HPP

#include "GraphicsComponent.hpp"
class TileMapGraphicsComponent : public GraphicsComponent {
 public:
  TileMapGraphicsComponent(SDL_Renderer* g_renderer, TransformComponent* tf,
                           int rows, int cols, int _TileWidth, int _TileHeight,
                           int _mapX, int _mapY);
  virtual ~TileMapGraphicsComponent();
  virtual void update();
  virtual void Render();
  /**
   * Temporary function for generating a simple
   * map to display some tiles
   */
  void GenerateSimpleMap();
  /**
   * Function for printing text to console
   */
  void PrintMap();
  /**
   * Set the 'type' of tile at an x and y position
   */
  void SetTile(int x, int y, int type);
  /**
   * Return the tile type at an x and y position
   */
  int GetTileType(int x, int y);

 protected:
  // Dimensions of our TileMap and individual tiles.
  // Used for spiltting up the sprite sheet
  int m_Rows;
  int m_Cols;
  // How big each tile is.
  int m_TileWidth;
  int m_TileHeight;
  // size of our tilemap
  int m_MapX;
  int m_MapY;
  // Stores our tile types
  int* m_Tiles;
};

#endif