#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "Game/player.h"
#include "Game/gameManeger.h"
#include "AI/eightTuple/eightTupleAI.h"
#include "AI/few/fewAI.h"
int main(int argc,char*argv[]){
	srand(time(NULL));
	manPlayer man;
	randomPlayer random;
	random.setMessage(0);
	eightTupleLearner ai;
	ai.setMessage(1);
	gameManeger maneger;
	eightTupleContestant cai;
	fewContestant fai;
	cai.setMessage(1);
	maneger.setPassMassage(0);
	if(argc==1) maneger.playgame(fai,man);
	else{
		int get = atoi(argv[1]);
		maneger.playgame(ai,ai,get);
	}
	maneger.showStatistic();
}

