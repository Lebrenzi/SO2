#include "Circle.h"
#include <mutex>

std::mutex addingCircle;
std::mutex deattachPlatform;
// Fix initialized ; error : initialized is not static
bool Circle::initialized = false;
double Circle::GRAVITY = 0.6;
int Circle::xMax;
int Circle::yMax;
vector<Platform>* Circle::platforms;

Circle::Circle(){
	
	this->active = true;
	this->isAttached = false;

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

void Circle::initPlatforms(vector<Platform> *platforms){
	Circle::platforms = platforms;
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


bool Circle::ifPlatform(){
	for ( int i = 0; i < 1; i++){
		for(int j = 0; j< platforms[i].size(); j++ )
		{
		    if ( this-> coorY == platforms[i][j].coorY )
		    {
			if ( this-> coorX < platforms[i][j].coorX + 1 && this-> coorX > platforms[i][j].coorY - 1 ) 
			{
			    	if( platforms[i][j].platformsAttached < 2 ){

					deattachPlatform.lock();
					platforms[i][j].deattach = false;
					deattachPlatform.unlock();
					isAttached = true;
					this->dir = PLATFORM_NORTH;
					this->assignedPlatform = &platforms[i][j];
					platforms[i][j].platformsAttached += 1;
					move();
					return true;
				}
				else {
					if( platforms[i][j].platformsAttached == 2){
						deattachPlatform.lock();
						platforms[i][j].deattach = true;
						deattachPlatform.unlock();}
				}	
			}
		    }
		}
	}
}	




void Circle::isDeattach(){
	if(assignedPlatform->deattach){
		//add mutex to decrement valu
		
		int choose = rand() % 3;
		Direction array[3] = { SOUTH , SOUTH_WEST, SOUTH_EAST };
		addingCircle.lock();
		assignedPlatform->platformsAttached -= 1;
		addingCircle.unlock();
		dir =  array[choose];
		move();
		
	}
}


double Circle::getSpeed(){

	return this->speed;

}



void Circle::move(){
	
	// Circle moves depending on the direction
	// Gravity accelerates or stops circle depends on direction
	// Using switch check all routes
	while(this->active) {
        switch (this->dir) {

            case NORTH:
                while (this->coorY > 0) {
                    this->coorY--;
                    usleep(this->speed);
                    ifPlatform();
                    this->speed += 3000.0 / GRAVITY;
                    if (this->speed > 200000) break;
                }
                this->dir = SOUTH;
                if (speed < 200000) {
                    this->speed *= 1.5;
                } else {
                    if (this->speed < 400000) this->speed *= 1.5;
                    else {
                        this->active = false;
                        return;
                    }
                }
                move();
                break;


            case SOUTH:
                while (this->coorY < yMax - 1) {
                    this->coorY++;
                    usleep(this->speed);
                    ifPlatform();
                    this->speed -= 3000.0 / GRAVITY;
                }
                this->dir = NORTH;
                this->coorY = yMax - 1;
                if (this->speed < 400000) this->speed *= 1.5;
                /*else{
                    this->active = false;
                    return;
                }*/
                move();
                break;

            case NORTH_WEST:
                while (this->coorY > 0 && this->coorX > 0) {
                    this->coorY--;
                    this->coorX--;
                    usleep(this->speed);
                    ifPlatform();
                    this->speed += 3000.0 / GRAVITY;
                    if (this->speed > 180000) break;
                }
                if (this->speed > 400000) {

                    this->active = false;
                    return;
                }
                if (coorY == 0) {
                    this->dir = SOUTH_WEST;
                    this->speed *= 1.5;
                } else {
                    if (coorX == 0) {
                        this->dir = NORTH_EAST;
                        this->speed *= 1.5;
                    } else {
                        this->dir = SOUTH_WEST;
                        this->speed *= 1.5;
                    }
                }
                move();
                break;

            case NORTH_EAST:
                while (this->coorY > 0 && this->coorX < xMax - 1) {
                    this->coorY--;
                    this->coorX++;
                    usleep(this->speed);
                    ifPlatform();
                    this->speed += 3000.0 / GRAVITY;
                    if (this->speed > 180000) break;
                }
                if (this->speed > 400000) {
                    this->active = false;
                    return;
                }
                if (coorY == 0) {
                    this->dir = SOUTH_EAST;
                    this->speed *= 1.5;
                } else {
                    if (coorX == xMax - 1) {
                        this->dir = NORTH_WEST;
                        this->speed *= 1.5;
                    } else {
                        this->dir = SOUTH_EAST;
                        this->speed *= 1.5;
                    }
                }
                move();
                break;

            case SOUTH_EAST:
                while (this->coorY < yMax - 1 && this->coorX < xMax - 1) {
                    this->coorY++;
                    this->coorX++;
                    usleep(this->speed);
                    ifPlatform();
                    this->speed -= 3000.0 / GRAVITY;

                }
                if (coorY == yMax - 1) {
                    this->dir = NORTH_EAST;
                    this->speed *= 1.5;

                } else {
                    if (coorX == xMax - 1) {
                        this->dir = SOUTH_WEST;
                        this->speed *= 1.5;
                    }
                }
                move();
                break;

            case SOUTH_WEST:
                while (this->coorY < yMax - 1 && this->coorX > 0) {
                    this->coorY++;
                    this->coorX--;
                    usleep(this->speed);
                    ifPlatform();
                    this->speed -= 3000.0 / GRAVITY;

                }
                if (coorY == yMax - 1) {
                    this->dir = NORTH_WEST;
                    this->speed *= 1.5;

                } else {
                    if (coorX == 0) {
                        this->dir = SOUTH_EAST;
                        this->speed *= 1.5;
                    }
                }
                move();
                break;
            case WEST:
                if (isAttached) {
                    coorX = this->assignedPlatform->coorX;
                    coorY = this->assignedPlatform->coorY;
                    while (this->coorX > 0) {
                        this->coorX--;
                        usleep(assignedPlatform->speed);
                    }
                    if (coorX == 0) {
                        this->dir = assignedPlatform->dir;
                    }
                    move();
                    break;


                } else {
                    break;
                }

            case EAST:
                if (isAttached) {
                    coorX = this->assignedPlatform->coorX;
                    coorY = this->assignedPlatform->coorY;
                    while (this->coorX < xMax - 1) {
                        this->coorX++;
                        usleep(assignedPlatform->speed);
                    }
                    if (coorX == xMax - 1) {
                        this->dir = assignedPlatform->dir;
                    }
                    move();
                    break;
                } else { break; }


        case PLATFORM_NORTH:
            if (isAttached) {
                coorX = this->assignedPlatform->coorX;
		if(assignedPlatform->platformsAttached == 1){
			dir = PLATFORM_SOUTH;
			usleep(assignedPlatform->speed);
			move();
		}
		else
		{
                	coorY = this->assignedPlatform->coorY-1;
		}
		//addingCircle.lock();
		//addingCircle.unlock();
		isDeattach();
	        usleep(assignedPlatform->speed);
                move();
                break;
            }
	
        case PLATFORM_SOUTH:
            if (isAttached) {
                coorX = this->assignedPlatform->coorX;
               	coorY = this->assignedPlatform->coorY+1;
		//addingCircle.lock();
		//addingCircle.unlock();
		isDeattach();
	        usleep(assignedPlatform->speed);
		isDeattach();
                move();
                break;
		}
        
	}}
}

std::thread Circle::circleThread(){
	
	return std::thread(&Circle::move, this);
}
