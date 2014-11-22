#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "hudDisplay.h"

hudDisplay::hudDisplay(){}
hudDisplay::hudDisplay(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position){
	mHealthTexture.loadFromFile( "Heart.png", gRenderer );
	mThurstTexture.loadFromFile( "Drop.png", gRenderer );


}
hudDisplay::~hudDisplay(){

}

void hudDisplay::Draw(){

}