#include "Platform.h"

// Fix initialized ; error : initialized is not static
bool Platform::initialized = false;
double Platform::GRAVITY = 0.6;
int Platform::xMax;
int Platform::yMax;

Platform::Platform(){
	
	this->active = true;
	int choose = rand() % 2;
	Direction array[2] = { WEST , EAST };
	this->speed = rand()% 10000 + 20000;
	this->coorX= rand() % Platform::xMax - 1;
	this->coorY= rand() % (Platform::yMax - 7) + 5;	
	platformsAttached = 0;
	//at the beginning no circle is attached to platform
	//this->topOne = NULL;
	//this->bottomOne = NULL;

	switch(choose){

		case 0:
			this->dir = array[0];
			break;
		case 1:
			this->dir = array[1];
			break;
		default:
			this->dir = array[0];
			break;

	}

}

Platform::~Platform(){

}


void Platform::initScene(int xMax, int yMax){
	
	Platform::xMax = xMax;
	Platform::yMax = yMax;
	Platform::initialized = true;
}



int Platform::getX(){
	
	return this->coorX;

}


bool Platform::isActive(){
	
	return this->active;

}
int Platform::getY(){

	return this->coorY;

}



double Platform::getSpeed(){

	return this->speed;

}



void Platform::move(){
	
	// Platform moves depending on the direction
	// Gravity accelerates or stops platform depends on direction
	// Using switch check all routes
	while(this->active){
	switch(this->dir){

		case WEST:
			while (  this-> coorX > 0 ) {
				this -> coorX--;
				usleep(this->speed);
			}	
			if ( coorX == 0 ) {
				this->dir = EAST;
			}
			move();
			break;
		
		case EAST:
			while (  this-> coorX < xMax -1 ) {
				this -> coorX++;
				usleep(this->speed);
			}	
			if ( coorX == xMax -1 ) {
				this->dir = WEST;
			}
			move();
			break;
		}
	}
}

std::thread Platform::platformThread(){
	
	return std::thread(&Platform::move, this);
}
