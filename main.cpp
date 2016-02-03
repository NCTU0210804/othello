#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "Game/player.h"
#include "Game/gameManeger.h"
#include "othelloAI.h"
int main(int argc,char*argv[]){
	srand(time(NULL));
	manPlayer man;
	randomPlayer random;
	random.setMessage(0);
	othelloAI ai;
	ai.setMessage(1);
	gameManeger maneger;
	maneger.setPassMassage(0);
	if(argc==1) maneger.playgame(ai,random);
	else{
		int get = atoi(argv[1]);
		maneger.playgame(ai,random,get);
	}
	maneger.showStatistic();
}

