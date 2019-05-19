#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

enum Direction{
	
	TOCASHBOXLEFT, TOCASHBOXRIGHT, FROMCASHBOXLEFT, FROMCASHBOXRIGHT, FROMQUEUE

};

enum Action
{
	DEFAULT
};
