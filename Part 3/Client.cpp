#include "Client.h"

char Client::character = 'o';
int Client::xMax;
int Client::yMax;

Client::Client(){
	
	coorX = xMax/2;
	coorY = yMax - 1;
	speed = 50000;
	dir = TOCASHBOXLEFT;

}

Client::~Client()
{


}


void Client::initScene(int xMax, int yMax){
	
	Client::xMax = xMax;
	Client::yMax = yMax;
}


void Client::move()
{
	
	while(active)
	{
		switch(dir){

			case TOCASHBOXLEFT:
				while(coorY > yMax/2){
					coorY--;
					usleep(speed);
				}
				for(int i = 0; i < xMax/4; i++)
				{
					coorX--;
					usleep(speed);
				}
				while(coorY > yMax/3){
					coorY--;
					usleep(speed);
				}
				active = false;
	
		}
	}


};



std::thread Client::clientThread(){
	
	return std::thread(&Client::move, this);
}
