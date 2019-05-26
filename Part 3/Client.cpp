#include "Client.h"

char Client::character = 'o';
int Client::xMax;
int Client::yMax;
std::mutex cashboxMutex;
std::mutex productQuantityMutex;
vector<Cashbox>* Client::cashboxes;

Client::Client(){
	coorX = xMax/2;
	coorY = yMax - 1;
	speed = 50000;
	dir = TOCASHBOXQUEUE;

}

Client::~Client()
{


}

void Client::initCashboxes(vector<Cashbox> *cashboxes){
	Client::cashboxes = cashboxes;
}

void Client::initScene(int xMax, int yMax){
	
	Client::xMax = xMax;
	Client::yMax = yMax;
}

void Client::freeCashbox(){
	for(int i = 0; i<cashboxes[0].size(); i++)
	{
		if(cashboxes[0][i].free){
			cashbox_idx = i;
			cashboxMutex.lock();
			cashboxes[0][i].free = false;
			cashboxMutex.unlock();
			if(i == 0) dir = TOCASHBOXLEFT;
			else dir = TOCASHBOXRIGHT;
			move();
		}
		else
		{
			usleep(50000);
		}
	}
}

void Client::move()
{
	//////(xMax/4) * (i+1) + xMax/8;
	while(active)
	{
		switch(dir){


			case TOCASHBOXQUEUE:
				while(coorY > cashboxes[0][0].coorY * 2){
					coorY--;
					usleep(speed);
				}
				freeCashbox();
				break;
		
			case TOCASHBOXLEFT:
				
				for(int i = 0; coorX > cashboxes[0][0].coorX + 2; i++)
				{
					coorX--;
					usleep(speed);
				}
				while(coorY > cashboxes[0][0].coorY){
					coorY--;
					usleep(speed);
				}
				dir = INCASHBOX;
				move();
				break;

			case TOCASHBOXRIGHT:
				
				for(int i = 0; coorX < cashboxes[0][1].coorX - 2; i++)
				{
					coorX++;
					usleep(speed);
				}
				while(coorY > cashboxes[0][1].coorY){
					coorY--;
					usleep(speed);
				}
				dir = INCASHBOX;
				move();
				break;

			case FROMCASHBOXLEFT:
				while(coorY < cashboxes[0][0].coorY * 2){
					coorY++;
					usleep(speed);
				}
				cashboxMutex.lock();
				cashboxes[0][cashbox_idx].free = true;
				cashboxMutex.unlock();
				for(int i = 0; coorX > cashboxes[0][0].coorX - 2; i++)
				{
					coorX--;
					usleep(speed);
				}
				while(coorY < yMax - 1){
					coorY++;
					usleep(speed);
				}
				active = false;
				break;

			case FROMCASHBOXRIGHT:
				while(coorY < cashboxes[0][1].coorY * 2){
					coorY++;
					usleep(speed);
				}
				cashboxMutex.lock();
				cashboxes[0][cashbox_idx].free = true;
				cashboxMutex.unlock();
				for(int i = 0; coorX < cashboxes[0][1].coorX + 2; i++)
				{
					coorX++;
					usleep(speed);
				}
				while(coorY < yMax - 1){
					coorY++;
					usleep(speed);
				}
				active = false;
				break;

			case INCASHBOX:
				if(cashboxes[0][cashbox_idx].product_quantity == 0){
					if(cashbox_idx == 0) dir = FROMCASHBOXLEFT;
					else dir = FROMCASHBOXRIGHT;
					move();
				}
				else
				{
					usleep(2500000);
					productQuantityMutex.lock();
					cashboxes[0][cashbox_idx].product_quantity -= 1;
					productQuantityMutex.unlock();
					if(cashbox_idx == 0) dir = FROMCASHBOXLEFT;
					else dir = FROMCASHBOXRIGHT;
					move();
				}
				break;
	
		}
	}


};



std::thread Client::clientThread(){
	
	return std::thread(&Client::move, this);
}
