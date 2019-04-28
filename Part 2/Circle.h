#include "Platform.h"

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
	
//Orientational variables such as direction coordinates and speed of Circle
	Direction dir;
	double speed;
	int coorX, coorY;

//List of all platforms in the scene, equal to every circle in the scene
	static vector<Platform> *platforms;
	Platform *assignedPlatform;
	bool isAttached;	

//Operational functions
	std::thread circleThread(); 
	Circle();	
	~Circle();
	Circle(int coorX, int coorY);

	static void initScene(int xMax, int yMax);
	static void initPlatforms(vector<Platform> *platforms);

	bool ifPlatform();
	int getX();
	int getY();
	bool isActive();
	double getSpeed();
	void move();

};
