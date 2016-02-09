#ifndef STAGEAI
#define STAGEAI
#include "../othelloAI.h"
class stageAI:virtual public othelloAI{
public:
	stageAI();
	~stageAI();
	void readData(FILE*);
	void generateInitData();
	void encode(int [][8],int []);
	double evaluate(int [][8],int);
	double ***table;
};

class stageLearner:
public stageAI,
public AILearner{
public:
	stageLearner():AILearner(2,0.000001){};
	~stageLearner(){writeData();};
	void gameOver(int [][8],int type);
protected:
	void learning(int [],double,int);
	void writeData();
};

class stageTrainer:
public stageLearner,
public AITrainer{
public :
	stageTrainer(int a):AITrainer(a){}
	int generateMove(int [][8],int type);
	void gameOver(int [][8],int type);
};

class stageContestant:
public stageAI,
public AIContestant{
protected:
	double finalScore(int [][8],int);
};
#endif
