#include "othello.h"

othello::othello(){
	board = new int*[8];
	for(int i=0;i<8;i++){
		board[i] = new int [8];
	}
	init();
}

void othello::init(){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			board[i][j] = 0;
		}
	}
	board[3][3] = 2;
	board[3][4] = 1;
	board[4][3] = 1;
	board[4][4] = 2;
}

inline bool othello::legalCoordinate(int thei,int thej){
	return 0<=thei&&thei<8&&0<=thej&&thej<8;
}

bool othello::canPut(int sti,int stj,int type){
	if(!legalCoordinate(sti,stj)||board[sti][stj]!=0) return 0;
	static const int di[8] = {-1,-1,-1,0,0,1,1,1};
	static const int dj[8] = {-1,0,1,-1,1,-1,0,1};
	int enemy = 3 - type;
	for(int t=0;t<8;t++){
		int myi = sti+di[t];
		int myj = stj+dj[t];
		if(!legalCoordinate(myi,myj)||board[myi][myj]!=enemy) continue;
		while(1){
			myi += di[t];
			myj += dj[t];
			if(!legalCoordinate(myi,myj)||board[myi][myj]==0) break;
			if(board[myi][myj]==type) return 1;
		}
	}
	return 0;
}

bool othello::canMove(int type){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(canPut(i,j,type)) return 1;
		}
	}
	return 0;
}

void othello::putChess(int sti,int stj,int type){
	if(!legalCoordinate(sti,stj)||board[sti][stj]!=0) return;
	static const int di[8] = {-1,-1,-1,0,0,1,1,1};
	static const int dj[8] = {-1,0,1,-1,1,-1,0,1};
	int enemy = 3 - type;
	for(int t=0;t<8;t++){
		int myi = sti+di[t];
		int myj = stj+dj[t];
		if(!legalCoordinate(myi,myj)||board[myi][myj]!=enemy) continue;
		while(1){
			myi += di[t];
			myj += dj[t];
			if(!legalCoordinate(myi,myj)||board[myi][myj]==0) break;
			if(board[myi][myj]==type){
				while(!(myi==sti&&myj==stj)){
					myi -= di[t];
					myj -= dj[t];
					board[myi][myj] = type;
				}
				break;
			}
		}
	}
}

void othello::getBoard(int board[8][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			board[i][j] = this->board[i][j];
		}
	}
}
