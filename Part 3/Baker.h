#include "Storage.h"

class Baker
{

public:

	static int xMax, yMax;
	static char character;
	static Storage* storage;

	int coorX, coorY;
	int bake_time;
	bool active;
	BakingCycle state;	

	Baker();
	~Baker();
	std::thread bakerThread(); 

	static void initStorage(Storage* storage);
	static void initScene(int xMax, int yMax);

	void bake();




};
