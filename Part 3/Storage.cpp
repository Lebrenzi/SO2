#include "Storage.h"


char Storage::character = '@';
int Storage::xMax;
int Storage::yMax;

Storage::Storage(){


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

		usleep(100000);
	}

}

