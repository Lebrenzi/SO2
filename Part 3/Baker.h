#include "Storage.h"

class Baker
{

public:

	static int xMax, yMax;
	static char character;
	int coorX, coorY;
	int bake_time;
	bool active;	

	Baker();
	~Baker();
	std::thread bakerThread(); 
	
	static void initScene(int xMax, int yMax);

	void bake();




};
