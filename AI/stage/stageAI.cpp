#include "stageAI.h"
#include "cstdio"
stageAI::stageAI(){
	table = new double**[2];
	for(int i=0;i<2;i++){
		table[i] = new double*[1<<8];
		for(int j=0;j<(1<<8);j++){
			table[i][j] = new double[1<<12];
		}
	}
	FILE* fPtr= fopen("stage.knowledge","r");
	if(fPtr) readData(fPtr);
	else generateInitData();
/*
	printf("%f\t",table[0][(1<<6)|(1<<4)|(1<<2)|(1)][(60<<6)|10]);
	printf("%f\t",table[0][0][(60<<6)|10]);
	printf("%f\t",table[0][0][(30<<6)|15]);
	printf("%f\t",table[0][0][(60<<6)|40]);
	printf("%f\n",table[0][0][(30<<6)|7]);
*/
}

stageAI::~stageAI(){
	for(int i=0;i<2;i++){
		for(int j=0;j<(1<<8);j++){
			delete table[i][j];
		}
		delete table[i];
	}
	delete table;
}

void stageAI::readData(FILE* fPtr){
	for(int i=0;i<2;i++){
		for(int j=0;j<(1<<8);j++){
			fread(table[i][j],sizeof(double),1<<12,fPtr);
		}
	}
}

void stageAI::generateInitData(){
	for(int i=0;i<2;i++){
		for(int j=0;j<(1<<8);j++){
			for(int k=0;k<(1<<12);k++){
				table[i][j][k] = 1;
			}
		}
	}
}

void stageAI::encode(int board[8][8],int characteristic[2]){
	characteristic[0] = (board[0][0]<<6)|(board[0][7]<<4)|(board[7][0]<<2)|(board[7][7]);
	int num = 0,black = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==0) continue;
			num++;
			if(board[i][j]==1) black++;
		}
	}
	characteristic[1] = (num<<6)|black;
}

double stageAI::evaluate(int board[8][8],int type){
	int characteristic[2];
	encode(board,characteristic);
	return table[type-1][characteristic[0]][characteristic[1]];
}

/*********************Learner********************/
void stageLearner::learning(int characteristic[2],double goal,int type){
	double diff = goal - table[type-1][characteristic[0]][characteristic[1]];
	table[type-1][characteristic[0]][characteristic[1]] += diff*stepSize;
}

void stageLearner::writeData(){
	FILE* fPtr = fopen("stage.knowledge","w");
	for(int i=0;i<2;i++){
		for(int j=0;j<(1<<8);j++){
			fwrite(table[i][j],sizeof(double),1<<12,fPtr);
		}
	}
}

void stageLearner::gameOver(int board[8][8],int type){
	int score = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==0) continue;
			score += board[i][j]==type? 1:-1;
		}
	}
	learning(lastCharacteristic[type-1],score>0? 1000000:1,type);
}

/******************Contestant*****************/
double stageContestant::finalScore(int board[8][8],int type){
	int score = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==0) continue;
			score += board[i][j]==type? 1:-1;
		}
	}
	if(score>0) score += 100000000;
	return score;
}

/***************Trainer***********************/
int stageTrainer::generateMove(int board[8][8],int type){
//printf("type=%d,trainer=%d\n",type,trainer);
	if(type==trainer) return generateTrainningMove(board,type);
	return AILearner::generateMove(board,type);
}

void stageTrainer::gameOver(int board[8][8],int type){
	if(type==trainer) return;
	stageLearner::gameOver(board,type);
}
