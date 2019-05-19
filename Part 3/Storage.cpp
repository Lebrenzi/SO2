#include "Storage.h"



void Storage::decreaseProduct()
{
	products-=1;
}



void Storage::increaseProduct()
{
	products+=1;
}


void Storage::live(){

	while(active)
	{

		usleep(100000);
	}

}

