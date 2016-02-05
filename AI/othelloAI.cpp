#include "othelloAI.h"
AILearner::AILearner(int a,double b):lengthOfCharact(a),stepSize(b){
	lastCharacteristic = new int* [2];
	lastCharacteristic[0] = new int [lengthOfCharact];
	lastCharacteristic[1] = new int [lengthOfCharact];
}

AILearner::~AILearner(){
	delete[] lastCharacteristic[0];
	delete[] lastCharacteristic[1];
	delete[] lastCharacteristic;
}

void AILearner::init(){
	int board[8][8];
	simulate.init();
	simulate.getBoard(board);
	encode(board,lastCharacteristic[0]);
	encode(board,lastCharacteristic[1]);
}

int AILearner::generateMove(int board[8][8],int type){
	simulate.setBoard(board);
	int ansi = -1, ansj;
	static int temp[8][8];
	double maxScore;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(!simulate.canPut(i,j,type)) continue;
			simulate.putChess(i,j,type);
			simulate.getBoard(temp);
			double get = evaluate(temp,type);
			if(get>maxScore||ansi==-1){
				ansi = i;
				ansj = j;
				maxScore = get;
			}
			simulate.setBoard(board);
		}
	}
	learning(lastCharacteristic[type-1],maxScore,type);
	simulate.putChess(ansi,ansj,type);
	simulate.getBoard(temp);
	encode(temp,lastCharacteristic[type-1]);
	return ansi<<3|ansj;
}

int AIContestant::generateMove(int board[8][8],int type){
	simulate.setBoard(board);
	int ansi = -1, ansj;
	static int temp[8][8];
	double maxScore = -1000000000;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(!simulate.canPut(i,j,type)) continue;
			simulate.putChess(i,j,type);
			simulate.getBoard(temp);
			double get = betaSearch(temp,type,3,maxScore,1000000000,0);
			if(get>maxScore||ansi==-1){
				ansi = i;
				ansj = j;
				maxScore = get;
			}
			simulate.setBoard(board);
		}
	}
//	printf("my ans = %d,%d\n",ansi,ansj);
	return ansi<<3|ansj;
}

double AIContestant::alphaSearch(int board[8][8],int type,int deep,double alpha,double beta,int counter){
//	printf("alpha deep:%d\n",deep);
	if(counter==2){
		double get = finalScore(board,type);
		if(get>alpha) alpha = get;
		return alpha;
	}
	int temp[8][8];;
	simulate.setBoard(board);
	bool move = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(!simulate.canPut(i,j,type)) continue;
			move = 1;
			simulate.putChess(i,j,type);
			simulate.getBoard(temp);
			double get = betaSearch(temp,type,deep,alpha,beta,0);
			if(get>alpha) alpha = get;
			if(alpha>beta) return alpha;
			simulate.setBoard(board);
		}
	}
	if(!move){
		double get = betaSearch(board,type,deep,alpha,beta,counter+1);
		if(get>alpha) alpha = get;
	}
	return alpha;
}

double AIContestant::betaSearch(int board[8][8],int type,int deep,double alpha,double beta,int counter){
//	printf("beta deep:%d\n",deep);
	if(counter==2){
		double get = finalScore(board,type);
		if(get<beta) beta = get;
		return beta;
	}
	if(deep==0) return evaluate(board,type);
	deep--;

	int temp[8][8];
	int enemy = 3-type;
	simulate.setBoard(board);
	bool move = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(!simulate.canPut(i,j,enemy)) continue;
			move = 1;
			simulate.putChess(i,j,enemy);
			simulate.getBoard(temp);
			double get = alphaSearch(temp,type,deep,alpha,beta,0);
			if(get<beta) beta = get;
			if(beta<alpha) return beta;
			simulate.setBoard(board);
		}
	}
	if(!move){
		double get = alphaSearch(board,type,deep,alpha,beta,counter+1);
		if(get<beta) beta = get;
	}
	return beta;
}

