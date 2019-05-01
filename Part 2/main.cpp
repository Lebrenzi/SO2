#include <ncurses.h>
#include <thread>
#include "Circle.h"
bool running = true; 

vector<Platform> platVector;
vector<Circle> circVector;
vector<std::thread> threads;
vector<std::thread> platThreads;
// "Monitor" function
void refreshScreen()
{
	while(running == true)
	{
		clear(); 
		for(int i = 0; i < circVector.size(); i++){
			if( circVector[i].isActive() ){	
				mvprintw( circVector[i].getY() , circVector[i].getX(), "o" ); }
			else	
				mvprintw( circVector[i].getY() , circVector[i].getX(), " " );
		}
		for(int i = 0; i< platVector.size(); i++) {
				mvprintw( platVector[i].getY() , platVector[i].getX(), "#" );
		}
		refresh();
		// Refresh every 0.01 s
		usleep(10000);
	}
}

int main(){
	int xMax, yMax;
	int circlesUsed = 0;
	int platUsed = 0;
	srand(time(0));

	initscr();
	curs_set(0);
	getmaxyx(stdscr, yMax, xMax);
	Circle::initScene(xMax, yMax);
	Platform::initScene(xMax, yMax);
	for(int i = 0; i < 3; i++) {
		
		Platform plat;
		platVector.push_back(plat);
	}
	Circle::initPlatforms(&platVector);
	for(int i = 0 ; i < 10; i++) {

		Circle circ;
		circVector.push_back(circ);

	}
	
	std::thread monitor(refreshScreen);
	
	
	while( platUsed < platVector.size() ){
		
		threads.push_back( platVector.at(platUsed).platformThread() );
		platUsed++;
	}
	while( circlesUsed < circVector.size() ){
		
		threads.push_back( circVector.at(circlesUsed).circleThread() );
		circlesUsed++;
		int randTime = rand() % 5 + 1;
		usleep(300000 * randTime);
	
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
