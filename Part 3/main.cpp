#include <ncurses.h>
#include "Client.h"
#include <signal.h>
bool running = true; 
bool program = true;
vector<Client> circVector;
vector<Cashbox> cashVector;
vector<Storage> storageVector;
vector<Baker> bakerVector;
vector<std::thread> threads;
vector<std::thread> monitorThread;

// "Monitor" function

void refreshScreen()
{
	while(running == true)
	{
		clear(); 
		for(int i = 0; i < circVector.size(); i++){
			if(circVector[i].active)
				mvprintw( circVector[i].coorY , circVector[i].coorX, "o" ); 
			else
				mvprintw( circVector[i].coorY , circVector[i].coorX, " " ); 
		}
		
		for(int i = 0; i < cashVector.size(); i++){
			mvprintw( cashVector[i].coorY-1 , cashVector[i].coorX, "#" );
			mvprintw( cashVector[i].coorY+1 , cashVector[i].coorX, "#" ); 
			mvprintw( cashVector[i].coorY , cashVector[i].coorX, "o" ); 
			if(cashVector[i].free)
				mvprintw( cashVector[i].coorY - 1, cashVector[i].coorX + 1, "^" ); 
			else
				mvprintw( cashVector[i].coorY - 1, cashVector[i].coorX + 1, "!" ); 
			mvprintw( cashVector[i].coorY , cashVector[i].coorX-1, "#" ); 
			mvprintw( cashVector[i].coorY , cashVector[i].coorX+1, "#" ); 
		}
		for(int i = 0; i < storageVector.size(); i++){
			mvprintw( storageVector[i].coorY-1 , storageVector[i].coorX, storageVector[i].character );
		}
		for(int i = 0; i < bakerVector.size(); i++){
			mvprintw( bakerVector[i].coorY-1 , bakerVector[i].coorX, "&" );
		}
		
		refresh();
		// Refresh every 0.01 s
		usleep(5000);
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
		Storage store;
		store.coorX = xMax / 2;
		store.coorY = yMax / 5;
		storageVector.push_back(store);
	}
	Cashbox::initStorage(&storageVector[0]);
	Baker::initStorage(&storageVector[0]);
	for(int i = 0 ; i < 2; i++) {
		Baker baker;
		baker.coorX = (xMax/4) * (i+1) + xMax/8;
		baker.coorY = yMax/5;
		bakerVector.push_back(baker);
	}
	for(int i = 0 ; i < 2; i++) {
		Cashbox cash;
		cash.coorX = (xMax/4) * (i+1) + xMax/8;
		cash.coorY = yMax/3;
		cashVector.push_back(cash);
	}
	Client::initCashboxes(&cashVector);
	for(int i = 0 ; i < 15; i++) {
		Client circ;
		circVector.push_back(circ);
	}
	
	monitorThread.push_back(std::thread(refreshScreen));
	
	for( int i = 0; i < storageVector.size(); i++ )
	{
		threads.push_back( storageVector.at(i).storageThread() );
	}
	for( int i = 0; i < bakerVector.size(); i++ )
	{
		threads.push_back( bakerVector.at(i).bakerThread() );
	}
	for( int i = 0; i < cashVector.size(); i++ )
	{
		threads.push_back( cashVector.at(i).cashboxThread() );
	}
	while( circlesUsed < circVector.size() ){
		
		threads.push_back( circVector.at(circlesUsed).clientThread() );

		circlesUsed++;
		int randTime = rand() % 7 + 1;
		usleep(400000 * randTime);
	
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
