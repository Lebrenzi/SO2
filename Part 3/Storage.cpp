#include "Storage.h"


const char* Storage::character;
int Storage::xMax;
int Storage::yMax;
std::mutex backdoorMutex;

Storage::Storage(){

	products = 9;
}

Storage::~Storage()
{


}


void Storage::initScene(int xMax, int yMax){
	
	Storage::xMax = xMax;
	Storage::yMax = yMax;
}



void Storage::live(){

	while(active)
	{
		std::string s = std::to_string(products);
		
		character = s.c_str(); 
		usleep(100000);
	}

}

void Storage::increaseProducts()
{
	backdoorMutex.lock();
	products += 1;
	backdoorMutex.unlock();
}

void Storage::decreaseProducts()
{
	backdoorMutex.lock();
	products -= 1;
	backdoorMutex.unlock();
}

std::thread Storage::storageThread(){
	
	return std::thread(&Storage::live, this);
}


