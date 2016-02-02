#include <cstdio>
#include <cstdlib>
#include "nonBitBoard/othello.h"


void manPut(othello&game,int type){
	int geti,getj;
	do{
		scanf("%d%d",&geti,&getj);
	}while(!game.canPut(geti,getj,type));
	game.putChess(geti,getj,type);
}

void randomPut(othello&game,int type){
	int geti,getj;
	do{
		geti = rand()%8;
		getj = rand()%8;
	}while(!game.canPut(geti,getj,type));
	//printf("rand put:%d %d\n",geti,getj);
	game.putChess(geti,getj,type);
}

void show(othello&game){
	int board[8][8];
	game.getBoard(board);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			printf("%d ",board[i][j]);
		}
		puts("");
	}
	puts("");
}

void solve(){
	int counter = 0;	
	othello game;
	game.init();
	//show(game);
	while(counter!=2){
		if(game.canMove(1)){
	//		show(game);
//			manPut(game,1);
			randomPut(game,1);
			counter = 0;
	//		show(game);
		}
		else{
	//		puts("1 pass");
			counter++;
		}
		if(counter==2) break;
		if(game.canMove(2)){
			randomPut(game,2);
			counter = 0;
		}
		else{
	//		puts("2 pass");
			counter++;
		}
	//	char get;
	//	scanf(" %c",&get);
	}
//	show(game);
}

int main(void){
	for(int i=0;i<100000;i++)solve();
	return 0;
}
