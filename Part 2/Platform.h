#include "Direction.h"
#include <random>
#include <ctime>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <cstdlib>
using namespace std;
class Platform{

	public:
// Local variables
// dir sets direction of flying platform
// speed shows how much will platform fly from refresh to refresh
// coorX, coorY are the coordinates of platform
	static double GRAVITY;
	static int xMax, yMax;
	static bool initialized;
	bool active;
	
	Direction dir;
	double speed;
	int coorX, coorY;

	std::thread platformThread(); 
	Platform();	
	~Platform();
	Platform(int coorX, int coorY);
	static void initScene(int xMax, int yMax);
	int getX();
	int getY();
	bool isActive();
	double getSpeed();
	void move();

};
