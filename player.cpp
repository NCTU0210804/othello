#include <cstdio>
#include <cstdlib>
#include "nonBitBoard/othello.h"
#include "player.h"
/*
class othelloPlayer{
public:
	virtual void initial()=0;
	virtual int generateMove(int [][8],int)=0;
	virtual void getIllegaelMessage(int,int,int)=0;
	virtual void gameOver(int [][8])=0;
};

class manPlayer:public othelloPlayer{
public:
	void initial(){}
	int generateMove(int [][8],int);
	void getIllegaelMessage(int,int,int);
	void gameOver(int[][8]);
};
*/
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
/*
class randomPlayer:public othelloPlayer{
public:
	randomPlayer(){}
	virtual void initial(){};
	virtual int generateMove(int [][8],int);
	virtual void getIllegaelMessage(int,int,int);
	virtual void gameOver(int[][8]){};
	void setMessage(bool open){sound = open;}
private:
	bool sound;
};
*/
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
/*
class gameManeger{
public:	
	void playgame(othelloPlayer &black,othelloPlayer &white,int = 1);
	void setPassMassage(bool open){passSound = open;}
private:
	bool oneMove(othelloPlayer &plater,int);
	othello game;
	bool passSound;
};
*//*
void gameManeger::playgame(othelloPlayer &black,othelloPlayer &white,int round){
	static int temp[8][8];
	while(round--){
		game.init();
		black.initial();
		white.initial();
		int passCounter = 0;
		int turn = 0;
		while(passCounter!=2){
			bool get;
			if(turn==0) get = oneMove(black,1);
			else get = oneMove(white,2);
			if(get) passCounter=0;
			else{
				if(passSound) printf("%d pass!!\n",turn+1);
				passCounter++;
			}
			if(++turn>1) turn = 0;
		}
		game.getBoard(temp);
		black.gameOver(temp);
		white.gameOver(temp);
	}
}

inline bool gameManeger::oneMove(othelloPlayer &player,int type){
	if(!game.canMove(type)) return 0;
	static int temp[8][8];
	game.getBoard(temp);
	int geti = player.generateMove(temp,type);
	int getj = geti&7;
	geti >>= 3;
	while(!game.canPut(geti,getj,type)){
		player.getIllegaelMessage(geti,getj,type);
		geti = player.generateMove(temp,type);
		getj = geti&7;
		geti >>= 3;
	}
	game.putChess(geti,getj,type);
	return 1;
}

int main(){

	manPlayer man;
	randomPlayer random;
	random.setMessage(0);
	gameManeger maneger;
	maneger.setPassMassage(0);
	maneger.playgame(random,random,100000);
}*/
