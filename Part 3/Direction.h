#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

enum Direction{
	
	TOCASHBOXLEFT, TOCASHBOXRIGHT, FROMCASHBOXLEFT, FROMCASHBOXRIGHT, FROMQUEUE, INCASHBOX

};

