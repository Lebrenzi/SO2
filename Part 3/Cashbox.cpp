#include "Cashbox.h"


char Cashbox::character = '#';
int Cashbox::xMax;
int Cashbox::yMax;
Storage* Cashbox::storage;
std::mutex storageMutex;

Cashbox::Cashbox(){
	
	free = true;
	product_quantity = 1;

}

Cashbox::~Cashbox()
{


}


void Cashbox::initScene(int xMax, int yMax){
	
	Cashbox::xMax = xMax;
	Cashbox::yMax = yMax;
}

void Cashbox::initStorage(Storage* storage){
	
	Cashbox::storage = storage;

}

void Cashbox::work()
{
	
	while(true)
	{	
		if(free) usleep(50000);
		else
		{
			if(product_quantity == 0)
			{
				if(storage[0].products > 0){
					storageMutex.lock();
					storage[0].products -= 1;
					product_quantity += 1;
					storageMutex.unlock();
				}
				else
				{
					usleep(50000);
				}
				
			}
			else
			{
				usleep(50000);
			}
			
		}
		
		
	}


}

std::thread Cashbox::cashboxThread(){
	
	return std::thread(&Cashbox::work, this);
}
