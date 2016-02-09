#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "Game/player.h"
#include "Game/gameManeger.h"
#include "AI/eightTuple/eightTupleAI.h"
#include "AI/few/fewAI.h"
#include "AI/stage/stageAI.h"
int main(int argc,char*argv[]){
	srand(time(NULL));
	manPlayer man;
	randomPlayer random;
	random.setMessage(0);
//	stageTrainer ai(2);
	eightTupleLearner ai;
	ai.setMessage(1);
//	stageContestant cai;
//	eightTupleContestant cai;
	fewContestant cai;
	gameManeger maneger;
	maneger.setPassMassage(0);
	if(argc==1) maneger.playgame(cai,man);
	else{
		int get = atoi(argv[1]);
		maneger.playgame(ai,ai,get);
	}
	maneger.showStatistic();
}

