#include "Direction.h"
#include <random>
#include <ctime>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <cstdlib>


class Circle{

	public:
// Local variables
// dir sets direction of flying circle
// speed shows how much will circle fly from refresh to refresh
// coorX, coorY are the coordinates of circle
	static double GRAVITY;
	static int xMax, yMax;
	static bool initialized;
	bool active;
	
	Direction dir;
	double speed;
	int coorX, coorY;

	std::thread circleThread(); 
	Circle();	
	~Circle();
	Circle(int coorX, int coorY);
	static void initScene(int xMax, int yMax);
	int getX();
	int getY();
	bool isActive();
	double getSpeed();
	void move();

};
