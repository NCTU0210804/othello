#ifndef EIGHTTUPLEAI
#define EIGHTTUPLEAI
#include "../othelloAI.h"
class eightTupleAI:virtual public othelloAI{
public:
	eightTupleAI();
	~eightTupleAI();
protected:
	virtual void readData(FILE*);
	virtual void generateInitData();
	virtual void encode(int [][8],int []);
	virtual double evaluate(int [][8],int);
	double***table;
};

class eightTupleLearner:
public eightTupleAI,
public AILearner{
public:
	eightTupleLearner():AILearner(22,0.01){}
	~eightTupleLearner(){writeData();}
	virtual void gameOver(int[][8],int);
protected:
	virtual void learning(int [],double,int);
	virtual void writeData();
};

class eightTupleContestant:
public eightTupleAI,
public AIContestant{
protected:
	virtual double finalScore(int [][8],int);
};
#endif
