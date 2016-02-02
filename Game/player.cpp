#include <cstdio>
#include <cstdlib>
#include "nonBitBoard/othello.h"
#include "player.h"

int manPlayer::generateMove(int board[8][8],int type){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			printf("%d ",board[i][j]);
		}
		puts("");
	}
	printf("Your character is %d. Please place your chess.\n",type);
	int geti,getj;
	scanf("%d%d",&geti,&getj);
	return (geti<<3)|getj;
}

void manPlayer::getIllegaelMessage(int thei,int thej,int type){
	printf("%d,%d is illegal place for %d!!!\n",thei,thej,type);
}

void manPlayer::gameOver(int board[8][8]){
	int black = 0,white = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			printf("%d ",board[i][j]);
			if(board[i][j]==1) black++;
			if(board[i][j]==2) white++;
		}
		puts("");
	}
	printf("Game Over.Black:White = %d:%d.\n",black,white);
}

int randomPlayer::generateMove(int board[][8],int){

	int geti,getj;
	do{
		geti = rand()%8;
		getj = rand()%8;
	}while(board[geti][getj]!=0);
	return geti<<3|getj;
}

void randomPlayer::getIllegaelMessage(int thei, int thej, int type){
	if(!sound) return;
	printf("random put on illegal place %d,%d as %d!!!\n",thei,thej,type);
}
