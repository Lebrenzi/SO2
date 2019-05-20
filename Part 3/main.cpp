#include <ncurses.h>
#include "Client.h"
#include <signal.h>
bool running = true; 
bool program = true;
vector<Client> circVector;
vector<std::thread> threads;
vector<std::thread> monitorThread;
// "Monitor" function

void refreshScreen()
{
	while(running == true)
	{
		clear(); 
		for(int i = 0; i < circVector.size(); i++){
			mvprintw( circVector[i].coorY , circVector[i].coorX, "o" ); 
		}
		refresh();
		// Refresh every 0.01 s
		usleep(10000);
	}
}

void endThreads(int dummy){
	for(int i = 0; i<circVector.size(); i++){
		
		circVector[i].active = false;
		circVector[i].move();
		
	}

	for(int i = 0; i<threads.size(); i++){
		
		threads.at(i).join();
		sleep(1);
		
	}

	sleep(1);
  	running = false;
    	monitorThread[0].join();
	// Close ncurses
    	endwin();
	program = false;
	exit(0);
}

int main(){
	signal(SIGTSTP, endThreads);
	int xMax, yMax;
	int circlesUsed = 0;
	int platUsed = 0;
	srand(time(0));

	initscr();
	curs_set(0);
	getmaxyx(stdscr, yMax, xMax);
	Client::initScene(xMax, yMax);
	for(int i = 0 ; i < 1; i++) {

		Client circ;
		circVector.push_back(circ);
	}
	
	monitorThread.push_back(std::thread(refreshScreen));
	
	while( circlesUsed < circVector.size() ){
		
		threads.push_back( circVector.at(circlesUsed).clientThread() );
		circlesUsed++;
		int randTime = rand() % 5 + 1;
		usleep(300000 * randTime);
	
	}
	for(int i = 0; i<threads.size(); i++){
		
		threads.at(i).join();
		sleep(1);
		
	}

	sleep(1);
  	running = false;
    	monitorThread[0].join();
	// Close ncurses
    	endwin();
	return  0;
}
