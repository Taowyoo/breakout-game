#include "Engine.hpp"

#include "Sprite.hpp"
#include "TileMap.hpp"
// I recommend a map for filling in the resource manager
#include <iterator>
#include <map>
#include <memory>
#include <string>

// Try toggling this number!
#define CHARACTERS 1

// Global array to create our characters
Sprite characters[CHARACTERS];

// Create a TileMap
TileMap* myTileMap;

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine() {}

// Proper shutdown and destroy initialized objects
Engine::~Engine() {}

// Return Input
void Engine::Input(bool* quit) {
  // Event handler that handles various events in SDL
  // that are related to input and output
  SDL_Event e;
  // Enable text input
  SDL_StartTextInput();
  // Handle events on queue
  while (SDL_PollEvent(&e) != 0) {
    // User posts an event to quit
    // An example is hitting the "x" in the corner of the window.
    if (e.type == SDL_QUIT) {
      *quit = true;
    } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
      bool new_state = e.type == SDL_KEYDOWN;
      switch (e.key.keysym.sym) {
        case SDLK_w:
        case SDLK_UP:
          direction_buttom_state[Direction::UP] = new_state;
          break;
        case SDLK_s:
        case SDLK_DOWN:
          direction_buttom_state[Direction::DOWN] = new_state;
          break;
        case SDLK_a:
        case SDLK_LEFT:
          direction_buttom_state[Direction::LEFT] = new_state;
          break;
        case SDLK_d:
        case SDLK_RIGHT:
          direction_buttom_state[Direction::RIGHT] = new_state;
          break;
        default:
          break;
      }
    }
  }
}

// Update SDL
void Engine::Update() {
  static int frame = 0;
  static int ticks = 0;
  // slow down the update of frame
  ticks++;
  if (ticks > 20) {
    // Increment the frame that
    // the sprite is playing
    frame++;
    if (frame > 6) {
      frame = 0;
    }
    ticks = 0;
  }

  // Update camera position
  if (direction_buttom_state[Direction::UP]) {
    camera_y -= camera_speed;
  }
  if (direction_buttom_state[Direction::DOWN]) {
    camera_y += camera_speed;
  }
  if (direction_buttom_state[Direction::LEFT]) {
    camera_x -= camera_speed;
  }
  if (direction_buttom_state[Direction::RIGHT]) {
    camera_x += camera_speed;
  }
  myTileMap->SetCameraPosition(camera_x, camera_y);
  // iterate through each of our characters
  for (int i = 0; i < CHARACTERS; i++) {
    characters[i].Update(20, 20, frame);
  }
}

// Render
// The render function gets called once per loop
void Engine::Render() {
  // Set the color of the empty framebuffer
  m_renderer->SetRenderDrawColor(110, 130, 170, 0xFF);
  // Clear the screen to the color of the empty framebuffer
  m_renderer->RenderClear();

  // Render each of the character(s)
  for (int i = 0; i < CHARACTERS; i++) {
    characters[i].Render(m_renderer->GetRenderer());
  }

  // Render the tile map
  myTileMap->Render(m_renderer->GetRenderer());

  // Flip the buffer to render
  m_renderer->RenderPresent();
}

// Loops forever!
void Engine::MainGameLoop() {
  // Main loop flag
  // If this is quit = 'true' then the program terminates.
  bool quit = false;

  // While application is running
  while (!quit) {
    // Get user input
    Input(&quit);
    // If you have time, implement your frame capping code here
    // Otherwise, this is a cheap hack for this lab.
    // SDL_Delay(250);
    // Update our scene
    Update();
    // Render using OpenGL
    Render();
    // Update screen of our specified window
  }
  // Disable text input
  SDL_StopTextInput();
}

void Engine::Start() {
  // Report which subsystems are being initialized
  if (m_renderer != nullptr) {
    std::cout << "Initializing Graphics Subsystem\n";
  } else {
    std::cout << "No Graphics Subsystem initialized\n";
  }

  // Move Sprite to initial position
  characters[0].SetPosition(128, 508);
  // Load an image for our character
  characters[0].LoadImage("./images/sprite.bmp", m_renderer->GetRenderer());

  // Setup our TileMap
  // This tile map is 20x11 in our game
  // It is using a 'reference' tilemap with 8x8 tiles
  // that are each 64x64 pixels.
  myTileMap = new TileMap("./images/Tiles1.bmp", 8, 8, 64, 64, 30, 20, 0, 0,
                          m_renderer->GetRenderer());
  // Generate a a simple tilemap
  myTileMap->GenerateSimpleMap();
  // Print out the map to the console
  // so we can see what was created.
  myTileMap->PrintMap();
}

void Engine::Shutdown() {
  // Shut down our Tile Systems
  if (nullptr != m_renderer) {
    delete m_renderer;
  }

  // Destroy our tilemap
  if (nullptr != myTileMap) {
    delete myTileMap;
  }
}

void Engine::InitializeGraphicsSubSystem() {
  // Setup our Renderer
  m_renderer = new GraphicsEngineRenderer(1280, 720);
  if (nullptr == m_renderer) {
    std::cerr << "Fail to initialize GraphicsEngineRenderer!" << std::endl;
    exit(1);  // Terminate program if renderer cannot be created.
  }
}
