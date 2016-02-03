#ifndef OTHELLOAI
#define OTHELLOAI
#include "Game/nonBitBoard/othello.h"
#include "Game/player.h"
#include <cstdio>
class othelloAI:public computerPlayer{
public:
	othelloAI();
	~othelloAI();
	virtual void init();
	virtual int generateMove(int[][8],int type);
	virtual void gameOver(int[][8],int);
private:
	double evaluate(int [][8],int);
	void readData(FILE*);
	void generateInitData();
	void writeData();
	void learning(int [],double,int);
	void encode(int [][8],int []);
	int stepSize;
	othello simulate;
	int *lastCharacteristic;
	double ***table;
};
#endif
