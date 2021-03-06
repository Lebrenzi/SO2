#include "Baker.h"

char Baker::character = '@';
int Baker::xMax;
int Baker::yMax;
std::mutex strMutex;
Storage* Baker::storage;

Baker::Baker(){

	state = IDLE;

}

Baker::~Baker()
{


}


void Baker::initScene(int xMax, int yMax){
	
	Baker::xMax = xMax;
	Baker::yMax = yMax;
}

void Baker::initStorage(Storage* storage){
	
	Baker::storage = storage;

}

void Baker::bake()
{
	while(active)
	{

		switch(state)
		{

			case IDLE:
				if(storage[0].products < 9)
				{
					state = BAKE;
					usleep(50000);
					bake();
				}
				else
				{
					usleep(50000);
					bake();
				}
				
				break;

			case BAKE:
				usleep(5000000);
				storage[0].increaseProducts();
				usleep(50000);
				state = IDLE;
				bake();
				break;
			
		}	

	}


};

std::thread Baker::bakerThread(){
	
	return std::thread(&Baker::bake, this);
}
