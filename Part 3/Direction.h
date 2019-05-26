#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

enum Direction{
	
	TOCASHBOXQUEUE, TOCASHBOXLEFT, TOCASHBOXRIGHT, FROMCASHBOXLEFT, FROMCASHBOXRIGHT, FROMQUEUE, INCASHBOX

};

enum BakingCycle{
	
	IDLE, BAKE, END_BAKING

};

