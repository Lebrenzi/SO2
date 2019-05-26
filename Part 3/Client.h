#include "Cashbox.h"

class Client
{

public:
	
	static int xMax, yMax;
	static char character;	
	static vector<Cashbox> *cashboxes;

	int cashbox_idx;
	bool active;
	bool is_waiting;	
	
	Direction dir;
	double speed;
	int coorX, coorY;
	int wait_time;

	Client();
	~Client();
	std::thread clientThread(); 
	void freeCashbox();

	static void initCashboxes(vector<Cashbox> *cashboxes);	
	static void initScene(int xMax, int yMax);
	

	void move();




};
