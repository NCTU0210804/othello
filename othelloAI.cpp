#include "othelloAI.h"
#include "cstdio"
othelloAI::othelloAI(){
	stepSize = 0.01;
	lastCharacteristic = new int[16];
	table = new double**[2];
	for(int i=0;i<2;i++){
		table[i] = new double*[4];
		for(int j=0;j<4;j++){
			table[i][j] = new double [1<<16];//4^8
		}
	}
	FILE *fPtr = fopen("eight_tuple.knowledge","r");
	if(fPtr) readData(fPtr);
	else generateInitData();
}

othelloAI::~othelloAI(){
	writeData();
	delete[] lastCharacteristic;
	for(int i=0;i<4;i++){
		delete[] table[i];
	}
	delete[] table;
}

void othelloAI::generateInitData(){
	for(int i=0;i<2;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<(1<<16);k++){
				table[i][j][k] = 1.0;
			}
		}
	}
}

void othelloAI::readData(FILE* fPtr){
	for(int i=0;i<2;i++){
		for(int j=0;j<4;j++){
			fread(table[i][j],sizeof(double),1<<16,fPtr);
		}
	}
}

void othelloAI::writeData(){
	FILE *fPtr = fopen("eight_tuple.knowledge","w");
	for(int i=0;i<2;i++){
		for(int j=0;j<4;j++){
			fwrite(table[i],sizeof(double),1<<16,fPtr);
		}
	}
}

void othelloAI::init(){
	for(int i=0;i<16;i++) lastCharacteristic[i] = 0;
	lastCharacteristic[3] = (2<<8)|(1<<6);
	lastCharacteristic[4] = (1<<8)|(2<<6);
	lastCharacteristic[11] = (2<<8)|(1<<6);
	lastCharacteristic[12] = (1<<8)|(2<<6);
}

int othelloAI::generateMove(int board[8][8],int type){
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
	learning(lastCharacteristic,maxScore,type);
	simulate.putChess(ansi,ansj,type);
	simulate.getBoard(temp);
	encode(temp,lastCharacteristic);
	return ansi<<3|ansj;
}

double othelloAI::evaluate(int board[8][8],int type){
	type--;
	static int characteristic[16];
	encode(board,characteristic);
	const int role[16] = {0,1,2,3,3,2,1,0,0,1,2,3,3,2,1,0};
	double ans = 0;
	for(int i=0;i<16;i++){
		ans += table[type][role[i]][characteristic[i]];
	}
	return ans;
}

void othelloAI::learning(int charcteristic[16],double goal,int type){
	type--;
	const int role[16] = {0,1,2,3,3,2,1,0,0,1,2,3,3,2,1,0};
	double temp[16];
	double ori = 0;
	for(int i=0;i<16;i++){
		ori += temp[i] = table[type][role[i]][charcteristic[i]];
	}
	double diff = goal-ori;
	for(int i=0;i<16;i++){
		table[type][role[i]][charcteristic[i]] += diff*(temp[i]/ori)*stepSize;
	}
}

void othelloAI::encode(int board[8][8],int characteristic[16]){
	for(int i=0;i<8;i++){
		characteristic[i] = 0;
		for(int j=0;j<8;j++){
			characteristic[i] <<= 2;
			characteristic[i] |= board[i][j];
		}
	}
	for(int j=0;j<8;j++){
		characteristic[j+8] = 0;
		for(int i=0;i<8;i++){
			characteristic[j+8] <<= 2;
			characteristic[j+8] |= board[i][j];
		}
	}
}

void othelloAI::gameOver(int board[8][8],int type){
	int score = 64;
	int enemy = 3-type;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==type) score++;
			if(board[i][j]==enemy) score--;
		}
	}
	learning(lastCharacteristic,score,type);
}
