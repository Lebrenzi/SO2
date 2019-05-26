#include "Baker.h"

class Cashbox{

public:
	static int xMax, yMax;
	static char character;
	static Storage* storage;
	bool free;
	int coorX, coorY;
	
	int product_quantity;
	Cashbox();
	~Cashbox();
	
	std::thread cashboxThread(); 
	static void initScene(int xMax, int yMax);
	static void initStorage(Storage* storage);
	void work();


};
