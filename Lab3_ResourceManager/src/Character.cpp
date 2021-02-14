
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>

#include "Character.hpp"

Character::Character(){
}


Character::~Character(){
	SDL_DestroyTexture(texture_);
}

void Character::init(int x, int y, SDL_Texture* texture){
	xPos_ = x;
	yPos_ = y;

	texture_ = texture;
}


void Character::update(int x, int y, int frame){
	// The part of the image that we want to render
	currentFrame_ = frame;
	if(currentFrame_>6){
		currentFrame_=0;
	}        

	// Here I am selecting which frame I want to draw
	// from our sprite sheet. Think of this as just
	// using a mouse to draw a rectangle around the
	// sprite that we want to draw.
	src_.x = currentFrame_*75;
	src_.y = 0;
	src_.w = 75;
	src_.h = 87;

	// Where we want the rectangle to be rendered at.
	// This is an actual 'quad' that will draw our
	// source image on top of.	
	dest_.x = xPos_;
	dest_.y = yPos_;
	dest_.w = 128;
	dest_.h = 128;
}

void Character::render(SDL_Renderer* ren){
    SDL_RenderCopy(ren, texture_, &src_, &dest_);
}
