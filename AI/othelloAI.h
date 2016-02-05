#ifndef OTHELLOAI
#define OTHELLOAI
#include "../Game/nonBitBoard/othello.h"
#include "../Game/player.h"
#include <cstdio>
class othelloAI{
protected:
	virtual void readData(FILE*) = 0;
	virtual void generateInitData() = 0;
	virtual void encode(int [][8],int []) = 0;
	virtual double evaluate(int [][8],int) = 0;
	othello simulate;
};

class AILearner:
virtual public othelloAI,
public computerPlayer{
public:
	AILearner(int,double);
	~AILearner();
	virtual void init();//basic version
	virtual int generateMove(int[][8],int type);//basic version
protected:
	int **lastCharacteristic;
	int lengthOfCharact;
	double stepSize;

//different from sub-class
public:
	virtual void gameOver(int[][8],int) = 0;
protected:
	virtual void learning(int [],double,int) = 0;
	virtual void writeData() = 0;
};

class AIContestant:
virtual public othelloAI,
public computerPlayer{
public:
	virtual void init(){};
	virtual int generateMove(int[][8],int type);
	virtual void gameOver(int[][8],int type){};
protected:
	virtual double alphaSearch(int board[8][8],int type,int deep,double alpha,double beta,int counter);
	virtual double betaSearch(int board[8][8],int type,int deep,double alpha,double beta,int counter);
//different from sub-class
	virtual double finalScore(int board[8][8],int type) = 0;
};
#endif
