#include "eightTupleAI.h"
#include "cstdio"
eightTupleAI::eightTupleAI(){
	table = new double**[2];
	for(int i=0;i<2;i++){
		table[i] = new double*[5];
		for(int j=0;j<5;j++){
			table[i][j] = new double [1<<16];//4^8
		}
	}
	FILE *fPtr = fopen("eight_tuple_3.knowledge","r");
	if(fPtr) readData(fPtr);
	else generateInitData();
}

eightTupleAI::~eightTupleAI(){
	for(int i=0;i<2;i++){
		for(int j=0;j<5;j++){
			delete[] table[i][j];
		}
		delete[] table[i];
	}
	delete[] table;
}

void eightTupleAI::generateInitData(){
	for(int i=0;i<2;i++){
		for(int j=0;j<5;j++){
			for(int k=0;k<(1<<16);k++){
				table[i][j][k] = 1000000;
			}
		}
	}
}

void eightTupleAI::readData(FILE* fPtr){
	for(int i=0;i<2;i++){
		for(int j=0;j<5;j++){
			fread(table[i][j],sizeof(double),1<<16,fPtr);
		}
	}
}

void eightTupleAI::encode(int board[8][8],int characteristic[22]){

//near side1
	characteristic[0] = (board[0][0]<<14)|(board[0][1]<<12)|(board[0][2]<<10)|(board[0][3]<<8)|(board[1][0]<<6)|(board[1][1]<<4)|(board[1][2]<<2)|board[1][3];
	characteristic[1] = (board[0][7]<<14)|(board[0][6]<<12)|(board[0][5]<<10)|(board[0][4]<<8)|(board[1][7]<<6)|(board[1][6]<<4)|(board[1][5]<<2)|board[1][4];
	characteristic[2] = (board[7][0]<<14)|(board[7][1]<<12)|(board[7][2]<<10)|(board[7][3]<<8)|(board[6][0]<<6)|(board[6][1]<<4)|(board[6][2]<<2)|board[6][3];
	characteristic[3] = (board[7][7]<<14)|(board[7][6]<<12)|(board[7][5]<<10)|(board[7][4]<<8)|(board[6][7]<<6)|(board[6][6]<<4)|(board[6][5]<<2)|board[6][4];
	characteristic[4] = (board[0][0]<<14)|(board[1][0]<<12)|(board[2][0]<<10)|(board[3][0]<<8)|(board[0][1]<<6)|(board[1][1]<<4)|(board[2][1]<<2)|board[3][1];
	characteristic[5] = (board[7][0]<<14)|(board[6][0]<<12)|(board[5][0]<<10)|(board[4][0]<<8)|(board[7][1]<<6)|(board[6][1]<<4)|(board[5][1]<<2)|board[4][1];
	characteristic[6] = (board[0][7]<<14)|(board[1][7]<<12)|(board[2][7]<<10)|(board[3][7]<<8)|(board[0][6]<<6)|(board[1][6]<<4)|(board[2][6]<<2)|board[3][6];
	characteristic[7] = (board[7][7]<<14)|(board[6][7]<<12)|(board[5][7]<<10)|(board[4][7]<<8)|(board[7][6]<<6)|(board[6][6]<<4)|(board[5][6]<<2)|board[4][6];
//near side2
	characteristic[8] = (board[0][2]<<14)|(board[0][3]<<12)|(board[0][4]<<10)|(board[0][5]<<8)|(board[1][2]<<6)|(board[1][3]<<4)|(board[1][4]<<2)|board[1][5];
	characteristic[9] = (board[7][2]<<14)|(board[7][3]<<12)|(board[7][4]<<10)|(board[7][5]<<8)|(board[6][2]<<6)|(board[6][3]<<4)|(board[6][4]<<2)|board[6][5];
	characteristic[10] = (board[2][0]<<14)|(board[3][0]<<12)|(board[4][0]<<10)|(board[5][0]<<8)|(board[2][1]<<6)|(board[3][1]<<4)|(board[4][1]<<2)|board[5][1];
	characteristic[11] = (board[2][7]<<14)|(board[3][7]<<12)|(board[4][7]<<10)|(board[5][7]<<8)|(board[2][6]<<6)|(board[3][6]<<4)|(board[4][6]<<2)|board[5][6];
//near side3
	characteristic[12] = (board[0][0]<<14)|(board[0][1]<<12)|(board[0][2]<<10)|(board[0][3]<<8)|(board[0][4]<<6)|(board[0][5]<<4)|(board[0][6]<<2)|board[0][7];
	characteristic[13] = (board[7][0]<<14)|(board[7][1]<<12)|(board[7][2]<<10)|(board[7][3]<<8)|(board[7][4]<<6)|(board[7][5]<<4)|(board[7][6]<<2)|board[7][7];
	characteristic[14] = (board[0][0]<<14)|(board[1][0]<<12)|(board[2][0]<<10)|(board[3][0]<<8)|(board[4][0]<<6)|(board[5][0]<<4)|(board[6][0]<<2)|board[7][0];
	characteristic[15] = (board[0][7]<<14)|(board[1][7]<<12)|(board[2][7]<<10)|(board[3][7]<<8)|(board[4][7]<<6)|(board[5][7]<<4)|(board[6][7]<<2)|board[7][7];
//diagonal
	characteristic[16] = (board[0][0]<<14)|(board[1][1]<<12)|(board[2][2]<<10)|(board[3][3]<<8)|(board[4][4]<<6)|(board[5][5]<<4)|(board[6][6]<<2)|board[7][7];
	characteristic[17] = (board[7][0]<<14)|(board[6][1]<<12)|(board[5][2]<<10)|(board[4][3]<<8)|(board[3][4]<<6)|(board[2][5]<<4)|(board[1][6]<<2)|board[0][7];
//center
	characteristic[18] = (board[2][2]<<14)|(board[2][3]<<12)|(board[2][4]<<10)|(board[2][5]<<8)|(board[3][2]<<6)|(board[3][3]<<4)|(board[3][4]<<2)|board[3][5];
	characteristic[19] = (board[5][2]<<14)|(board[5][3]<<12)|(board[5][4]<<10)|(board[5][5]<<8)|(board[4][2]<<6)|(board[4][3]<<4)|(board[4][4]<<2)|board[4][5];
	characteristic[20] = (board[2][2]<<14)|(board[3][2]<<12)|(board[4][2]<<10)|(board[5][2]<<8)|(board[2][3]<<6)|(board[3][3]<<4)|(board[4][3]<<2)|board[5][3];
	characteristic[21] = (board[2][5]<<14)|(board[3][5]<<12)|(board[4][5]<<10)|(board[5][5]<<8)|(board[2][4]<<6)|(board[3][4]<<4)|(board[4][4]<<2)|board[5][4];
}
double eightTupleAI::evaluate(int board[8][8],int type){
	type--;
	static int characteristic[22];
	encode(board,characteristic);
	const int role[22] = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,4,4,4,4};
	double ans = 0;
	for(int i=0;i<22;i++){
		ans += table[type][role[i]][characteristic[i]];
	}
	return ans;
}

/*****************************************learner**************************************/
void eightTupleLearner::learning(int characteristic[22],double goal,int type){
	type--;
	const int role[22] = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,4,4,4,4};
	double temp[22];
	double ori = 0;
	for(int i=0;i<22;i++){
		ori += temp[i] = table[type][role[i]][characteristic[i]];
	}
	double diff = goal-ori;
	for(int i=0;i<22;i++){
//		table[type][role[i]][characteristic[i]] += diff*(temp[i]/ori)*stepSize;
		table[type][role[i]][characteristic[i]] += diff/22*stepSize;		
	}
}

void eightTupleLearner::gameOver(int board[8][8],int type){
	int score = 0;
	int enemy = 3-type;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==type) score++;
			if(board[i][j]==enemy) score--;
		}
	}
	if(score>0) score = 1000000;
	else score = 18;
	learning(lastCharacteristic[type-1],score,type);
}
void eightTupleLearner::writeData(){
	FILE *fPtr = fopen("eight_tuple_3.knowledge","w");
	for(int i=0;i<2;i++){
		for(int j=0;j<5;j++){
			fwrite(table[i][j],sizeof(double),1<<16,fPtr);
		}
	}
}
/****************************contestant************************/
double eightTupleContestant::finalScore(int board[8][8],int type){
	int score = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==0) continue;
			score += board[i][j]==type? 1:-1;
		}
	}
	puts("in fianl");
	score += score>0? 100000000:-1;
	return score;
}
