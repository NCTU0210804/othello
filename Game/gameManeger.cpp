#include <cstdio>
#include "gameManeger.h"
void gameManeger::playgame(othelloPlayer &black,othelloPlayer &white,int round){
	static int temp[8][8];
	while(round--){
		game.init();
		black.init();
		white.init();
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
		black.gameOver(temp,1);
		white.gameOver(temp,2);
		int result = 0;
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(temp[i][j]==1) result++;
				if(temp[i][j]==2) result--;
			}
		}
		if(result>0) mystatistic.black_win++;
		else if(result==0) mystatistic.draw_game++;
		else mystatistic.white_win++;
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

void gameManeger::showStatistic(){
	printf("Black wins:\t%d\n",mystatistic.black_win);
	printf("White wins:\t%d\n",mystatistic.white_win);
	printf("Draw games:\t%d\n",mystatistic.draw_game);
}
