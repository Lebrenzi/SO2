#include "Circle.h"

// Fix initialized ; error : initialized is not static
bool Circle::initialized = false;
double Circle::GRAVITY = 0.6;
int Circle::xMax;
int Circle::yMax;

Circle::Circle(){
	
	this->active = true;
	
	// Rand to chose starting direction [ NORTH, NORTH_WEST, NORTH_EAST ]	
	int choose = rand() % 3;
	Direction array[3] = { NORTH , NORTH_WEST, NORTH_EAST };
	this->speed = rand() % 15000 + 35000;
	cout << xMax << " " << yMax <<endl;

	this->coorX = Circle::xMax /2;
	this->coorY = Circle::yMax -1;	

	switch(choose){

		case 0: 
			this->dir = array[0];
			break;
		case 1:
			this->dir = array[1];
			break;
		case 2: 
			this->dir = array[2];
			break;
		default:
			this->dir = array[0];
			break;

	}

}

Circle::~Circle(){

}


void Circle::initScene(int xMax, int yMax){
	
	Circle::xMax = xMax;
	Circle::yMax = yMax;
	Circle::initialized = true;
}


int Circle::getX(){
	
	return this->coorX;

}


bool Circle::isActive(){
	
	return this->active;

}
int Circle::getY(){

	return this->coorY;

}



double Circle::getSpeed(){

	return this->speed;

}



void Circle::move(){
	
	// Circle moves depending on the direction
	// Gravity accelerates or stops circle depends on direction
	// Using switch check all routes
	while(this->active){
	switch(this->dir){

		case NORTH:
			while( this->coorY > 0 ){	
				this->coorY--;
				usleep(this->speed);
				this->speed += 2300.0/GRAVITY;
				if(this->speed > 200000) break;
			}
			this->dir = SOUTH;
			if(speed < 200000){
				this->speed *= 1.5;
			}
			else {
				if(this->speed < 400000) this->speed *= 1.5;
				else{
					this->active = false;
					return;
				}	
			}
			move();
			break;


		case SOUTH:
			while( this->coorY < yMax - 1 ){	
				this->coorY++;
				usleep(this->speed);
				this->speed -= 2300.0/GRAVITY;
			}
			this->dir = NORTH;
			this->coorY = yMax - 1;
			if(this->speed < 400000) this->speed *= 1.5;
			/*else{
				this->active = false;
				return;	
			}*/
			move();
			break;

		case NORTH_WEST:
			while ( this-> coorY > 0 && this->coorX > 0 ){
				this->coorY--;
				this->coorX--;
				usleep(this->speed);
				this->speed += 2300.0/GRAVITY;
				if(this-> speed > 180000) break;
			}
			if( this->speed > 400000 ) {
			
				this->active = false;
				return;
			}
			if( coorY == 0 ){
				this->dir = SOUTH_WEST;
				this->speed *= 1.5;
			}
			else{
				if ( coorX == 0 ){
					this->dir = NORTH_EAST;
					this->speed *= 1.5;
				}
			
				else{
					this->dir = SOUTH_WEST;
					this->speed *= 1.5;
				}
			}
			move();
			break;

		case NORTH_EAST:
			while ( this-> coorY > 0 && this->coorX < xMax -1 ){
				this->coorY--;
				this->coorX++;
				usleep(this->speed);
				this->speed += 2300.0/GRAVITY;
				if(this-> speed > 180000) break;
			}
			if( this->speed > 400000 ){
				this->active = false;
				return;
			}
			if( coorY == 0 ){
				this->dir = SOUTH_EAST;
				this->speed *= 1.5;
			}
			else{
				if ( coorX == xMax-1 ){
					this->dir = NORTH_WEST;
					this->speed *= 1.5;
				}
				else{
					this->dir = SOUTH_EAST;
					this->speed *= 1.5;
				}
			}
			move();
			break;

		case SOUTH_EAST:
			while ( this-> coorY < yMax -1 && this->coorX < xMax -1 ){
				this->coorY++;
				this->coorX++;
				usleep(this->speed);
				this->speed -= 2300.0/GRAVITY;

			}
			if( coorY == yMax-1 ){
				this->dir = NORTH_EAST;
				this->speed *= 1.5;

			}
			else {
				if( coorX == xMax-1 ) {
					this->dir = SOUTH_WEST;
					this->speed *= 1.5;
				}
			}
			move();
			break;
	
		case SOUTH_WEST:
			while ( this-> coorY < yMax -1 && this->coorX > 0 ){
				this->coorY++;
				this->coorX--;
				usleep(this->speed);
				this->speed -= 2300.0/GRAVITY;

			}
			if( coorY == yMax-1 ){
				this->dir = NORTH_WEST;
				this->speed *= 1.5;

			}
			else {
				if( coorX == 0 ) {
					this->dir = SOUTH_EAST;
					this->speed *= 1.5;
				}
			}
			move();
			break;

		}
	}
}

std::thread Circle::circleThread(){
	
	return std::thread(&Circle::move, this);
}
