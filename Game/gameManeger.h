#ifndef GAME_MANEGER
#define GAME_MANEGER
#include "nonBitBoard/othello.h"
#include "player.h"
#include "statistic.h"
class gameManeger{
public:	
	void playgame(othelloPlayer &black,othelloPlayer &white,int = 1);
	void setPassMassage(bool open){passSound = open;}
	void reset(){mystatistic.reset();}
	void showStatistic();
private:
	bool oneMove(othelloPlayer &plater,int);
	othello game;
	bool passSound;
	statistic mystatistic;
};
#endif
