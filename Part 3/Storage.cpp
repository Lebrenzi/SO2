#include "Storage.h"


const char* Storage::character;
int Storage::xMax;
int Storage::yMax;

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

std::thread Storage::storageThread(){
	
	return std::thread(&Storage::live, this);
}


