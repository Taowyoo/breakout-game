#include "Engine.hpp"


#include "KeyControllerComponent.hpp"
#include "SpriteGraphicsComponent.hpp"
#include "TileMapGraphicsComponent.hpp"
#include "TransformComponent.hpp"
// I recommend a map for filling in the resource manager
#include <iterator>
#include <map>
#include <memory>
#include <string>



// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine() {
  gameObjects.resize(OBJECT_NUM);
}

// Proper shutdown and destroy initialized objects
Engine::~Engine() {}

// Return Input
void Engine::Input(bool* quit) {
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;
  // Handle events on queue
  
  while (SDL_PollEvent(&e) != 0) {
    // User posts an event to quit
    // An example is hitting the "x" in the corner of the window.
    // printf("Input SDL_PollEvent one\n");
    
    if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE) {
      *quit = true;
    }
  }
}

// Update SDL
void Engine::Update() {
  // Set the color of the empty framebuffer
  m_renderer->SetRenderDrawColor(110, 130, 170, 0xFF);
  // Clear the screen to the color of the empty framebuffer
  m_renderer->RenderClear();

  for (auto& obj : gameObjects) {
    obj.update();
  }

  // Flip the buffer to render
  m_renderer->RenderPresent();
}

// Render
// The render function gets called once per loop
void Engine::Render() {}

// Loops forever!
void Engine::MainGameLoop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;
  SDL_StartTextInput();
  // While application is running
  while (!quit) {
    // Let all game objects to read input, update scene and draw
    Update();
    // Check input for quiting game
    Input(&quit);
    SDL_Delay(150);
  }
  // Disable text input
  SDL_StopTextInput();
}

void Engine::Start() {
  // Report which subsystems are being initialized
  if (m_renderer != nullptr) {
    SDL_Log("Initializing Graphics Subsystem") ;
  } else {
    SDL_Log("No Graphics Subsystem initialized") ;
  }

  // Setup Sprite
  TransformComponent* sprite_tf = new TransformComponent{128, 508, 128, 128};
  KeyControllerComponent* keyController = new KeyControllerComponent{sprite_tf};
  SpriteGraphicsComponent* spriteGraphicsComponent =
      new SpriteGraphicsComponent{m_renderer->GetRenderer(), sprite_tf, 0, 6};
  spriteGraphicsComponent->LoadImage("./images/sprite.bmp");
  gameObjects[0].AddComponent(sprite_tf);
  gameObjects[0].AddComponent(keyController);
  gameObjects[0].AddComponent(spriteGraphicsComponent);

  // Setup our TileMap
  TransformComponent* tilemap_tf = new TransformComponent{0, 0, -1, -1};
  TileMapGraphicsComponent* tileMapGraphicsComponent =
      new TileMapGraphicsComponent{
          m_renderer->GetRenderer(), tilemap_tf, 8, 8, 64, 64, 20, 11};
  tileMapGraphicsComponent->LoadImage("./images/Tiles1.bmp");
  tileMapGraphicsComponent->GenerateSimpleMap();
  tileMapGraphicsComponent->PrintMap();
  gameObjects[0].AddComponent(tilemap_tf);
  gameObjects[0].AddComponent(tileMapGraphicsComponent);
}

void Engine::Shutdown() {
  // Shut down our Tile Systems
  if (nullptr != m_renderer) {
    delete m_renderer;
  }
}

void Engine::InitializeGraphicsSubSystem() {
  // Setup our Renderer
  m_renderer = new GraphicsEngineRenderer(1280, 720);
  if (nullptr == m_renderer) {
    SDL_Log("Failed to init GraphicsEngineRenderer");
    exit(1);  // Terminate program if renderer cannot be created.
  }
  SDL_Log("Succeed to init GraphicsEngineRenderer");
}
