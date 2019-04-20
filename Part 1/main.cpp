#include <ncurses.h>
#include <thread>
#include "Circle.h"


bool running = true; 

vector<Circle> circVector;
vector<std::thread> threads;
// "Monitor" function
void refreshScreen()
{
	while(running == true)
	{
		clear();
		for(int i = 0; i < circVector.size(); i++){
			if( circVector[i].isActive() )
				mvprintw( circVector[i].getY() , circVector[i].getX(), "o" );
			else
				mvprintw( circVector[i].getY() , circVector[i].getX(), " " );
		}
		refresh();
		// Refresh every 0.01 s
		usleep(10000);
	}
}

int main(){
	int xMax, yMax;
	int circlesUsed = 0;
	
	srand(time(0));

	initscr();
	curs_set(0);
	getmaxyx(stdscr, yMax, xMax);
	Circle::initScene(xMax, yMax);
	
	for(int i = 0 ; i < 5; i++) {

		Circle circ;
		circVector.push_back(circ);

	}
	
	std::thread monitor(refreshScreen);
	
	while( circlesUsed < circVector.size() ){
		
		threads.push_back( circVector.at(circlesUsed).circleThread() );
		circlesUsed++;
		int randTime = rand() % 5 + 1;
		usleep(1000000 * randTime);
	
	}

	for(int i = 0; i<threads.size(); i++){
		
		threads.at(i).join();
		
	}
	sleep(1);
  	running = false;
    	monitor.join();
    	
	// Close ncurses
    	endwin();
			
	return  0;



}
