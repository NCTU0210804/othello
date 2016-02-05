#include "fewAI.h"

double fewAI::evaluate(int board[8][8],int type){
	int score = 129;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==type) score--;
		}
	}
	int p[2] = {0,7};
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			if(board[p[i]][p[j]]==0) continue;
			score += board[p[i]][p[j]]==type? 16:-16;
		}
	}
	return score;
}

double fewContestant::finalScore(int board[8][8],int type){
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
