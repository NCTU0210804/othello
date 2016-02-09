#ifndef FEWAI
#define FEWAI
#include "../othelloAI.h"
class fewAI:
virtual public othelloAI{
protected:
	void readData(FILE*){}
	void generateInitData(){};
	void encode(int [][8],int[]){};
	double evaluate(int [][8],int type);
};

class fewContestant:
public fewAI,
public AIContestant{
	int generateMove(int board[8][8],int type);
protected:
	double finalScore(int [][8],int);
};
#endif
