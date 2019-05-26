#include "Direction.h"

class Storage
{

public:
	
	static int xMax, yMax;
	static const char* character;
	int coorX, coorY;
	int products;
	bool active;

	Storage();
	~Storage();
	std::thread storageThread(); 
	
	static void initScene(int xMax, int yMax);
	void live();
};
