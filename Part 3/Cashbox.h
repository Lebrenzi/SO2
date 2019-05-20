#include "Baker.h"

class Cashbox{

public:
	
	static int xMax, yMax;
	static char character;
	int coorX, coorY;
	
	Cashbox();
	~Cashbox();
	
	std::thread cashboxThread(); 
	static void initScene(int xMax, int yMax);
	void work();


};
