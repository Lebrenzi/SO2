#include "Cashbox.h"

class Client
{

public:
	
	static int xMax, yMax;
	static char character;	

	bool active;
	bool is_waiting;	
	
	Direction dir;
	double speed;
	int coorX, coorY;
	int wait_time;

	Client();
	~Client();
	std::thread clientThread(); 
	
	static void initScene(int xMax, int yMax);
	

	void move();




};
