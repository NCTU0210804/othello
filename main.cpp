//bit-board version
#include <cstdio>
#include <cstdlib>
using namespace std;

class MoveTable{//0 = empty, 1 = black, 2 = white, 3 = outspace
public:
	static MoveTable move_table;
private:
	MoveTable();
	~MoveTable();
	void init();
	int putting_situation(int,int,int);
	int nextStatus(int,int,int,int);
public:
	bool **row_can_put_black;
	bool **row_can_put_white;
	int **row_after_put_black;
	int **row_after_put_white;
};

MoveTable MoveTable::move_table;

MoveTable::MoveTable(){
	row_can_put_black = new bool*[8];
	row_can_put_white = new bool*[8];
	row_after_put_black = new int*[8];
	row_after_put_white = new int*[8];
	for(int i=0;i<8;i++){
		row_can_put_black[i] = new bool[1<<16];//4^8
		row_can_put_white[i] = new bool[1<<16];
		row_after_put_black[i] = new int[1<<16];
		row_after_put_white[i] = new int[1<<16];
	}
	init();
}

MoveTable::~MoveTable(){
	for(int i=0;i<8;i++){
		delete [] row_can_put_black[i];
		delete [] row_can_put_white[i];
		delete [] row_after_put_black[i];
		delete [] row_after_put_white[i];
	}
	delete [] row_can_put_black;
	delete [] row_can_put_white;
	delete [] row_after_put_black;
	delete [] row_after_put_white;
}

void MoveTable::init(){
	for(int place = 0;place<8;place++){
		for(int i=0;i<1<<16;i++){
			int getblack = putting_situation(i,place,1);
			int getwhite = putting_situation(i,place,2);
			row_can_put_black[place][i] = getblack!=0;
			row_can_put_white[place][i] = getwhite!=0;
			if(getblack)
				row_after_put_black[place][i] = nextStatus(i,place,1,getblack);
			else
				row_after_put_black[place][i] = i;
			if(getwhite)
				row_after_put_white[place][i] = nextStatus(i,place,2,getwhite);
			else
				row_after_put_white[place][i] = i;
		}
	}
}

int MoveTable::putting_situation(int status,int place,int type){
	int mask = 3<<(7-place)*2;
	if((status&mask)!=0) return 0;
	int enemy = 3-type;
	int typerow = 0;
	int enemyrow = 0;
	for(int i=0;i<8;i++){
		typerow <<= 2;
		typerow |= type;
		enemyrow <<= 2;
		enemyrow |= enemy;
	}
	int ans = 0;
	int leftmask = mask<<2;
	while(leftmask!=(3<<16)&&(status&leftmask)==(enemyrow&leftmask)){
		leftmask <<= 2;
		if(leftmask!=(3<<16)&&(status&leftmask)==(typerow&leftmask)){
			ans = 2;
			break;
		}
	}
	int rightmask = mask>>2;
	while(rightmask!=0&&(status&rightmask)==(enemyrow&rightmask)){//even out of bound will break the loop
		rightmask >>= 2;
		if(rightmask!=0&&(status&rightmask)==(typerow&rightmask)){
			return ans+1;
		}
	}
	return ans;
}

int MoveTable::nextStatus(int status,int place,int type,int code){
	int ans = status;
	int mask = 3<<(7-place)*2;
	int enemy = 3-type;
	int typerow = 0;
	int enemyrow = 0;
	for(int i=0;i<8;i++){
		typerow <<= 2;
		typerow |= type;
		enemyrow <<= 2;
		enemyrow |= enemy;
	}
	if((code&2)){
		int leftmask = mask<<2;
		while(leftmask!=(3<<16)&&(status&leftmask)==(enemyrow&leftmask)){
			ans ^= leftmask;
			leftmask <<= 2;
		}
	}
	if((code&1)){
		int rightmask = mask>>2;
		while(rightmask!=0&&(status&rightmask)==(enemyrow&rightmask)){
			ans ^= rightmask;
			rightmask >>= 2;
		}
	}
	ans |= type<<(7-place)*2;
	return ans;
}

class othello_game{
public:
	othello_game();
	void init();
	bool canPut(int thei,int thej,int type);
	bool canMove(int type);
	void putChess(int thei,int thej,int type);
	void getBoard(int [][8]);
//private:
	int **board;
};

othello_game::othello_game(){
	board = new int* [8];
	for(int i=0;i<8;i++){
		board[i] = new int[8+7+7];
		for(int j=0;j<8+7+7;j++){
			board[i][j] = 3;
		}
	}
}

void othello_game::init(){
	for(int i=0;i<8;i++){
		for(int j=7;j<8+7;j++){
			board[i][j] = 0;
		}
	}
	board[3][3+7] = 2;
	board[3][4+7] = 1;
	board[4][3+7] = 1;
	board[4][4+7] = 2;
}

bool othello_game::canPut(int thei,int thej,int type){
	thej += 7;
	static const int di[4] = {1,1,1,0};
	static const int dj[4] = {-1,0,1,1};
	bool **table = type==1? (MoveTable::move_table.row_can_put_black) : MoveTable::move_table.row_can_put_white;
	int sti[4] = {0,0,0,thei};
	int stj[4] = {thej+thei,thej,thej-thei,7};
	int place[4] = {thei,thei,thei,thej-7};
	for(int way=0;way<4;way++){
		int status = 0;
		int myi = sti[way];
		int myj = stj[way];
		for(int k=0;k<8;k++){
			status <<= 2;
			status |= board[myi][myj];
//			if(thei==3&&thej==9&&way==3) printf("%d %d get %d in way 3,now %d %d\n",thei,thej-7,status,myi,myj);
			myi += di[way];
			myj += dj[way];
		}
//		if(thei==3&&thej==9&&way==3) printf("%d %d get %d in way 3\n",thei,thej-7,status);
		if(table[place[way]][status]){
//			if(thei==4&&thej==4+7) printf("%d %d get %d int way %d\n",thei,thej-7,status,way);
			return 1;
		}
	}
	return 0;
}

bool othello_game::canMove(int type){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(canPut(i,j,type)) return 1;
		}
	}
	return 0;
}

void othello_game::putChess(int thei,int thej,int type){
	thej += 7;
	static const int di[4] = {1,1,1,0};
	static const int dj[4] = {-1,0,1,1};
	int **table = type==1? MoveTable::move_table.row_after_put_black : MoveTable::move_table.row_after_put_white;
	bool **movable = type==1?  MoveTable::move_table.row_can_put_black : MoveTable::move_table.row_can_put_white;
//puts("here");
	int sti[4] = {0,0,0,thei};
	int stj[4] = {thej+thei,thej,thej-thei,7};
	int place[4] = {thei,thei,thei,thej-7};
	int move[4];
	int ans[4];
//puts("there");
	for(int way=0;way<4;way++){
//printf("way = %d\n",way);
		int status = 0;
		int myi = sti[way];
		int myj = stj[way];
		for(int k=0;k<8;k++){
			status <<= 2;
			status |= board[myi][myj];
			myi += di[way];
			myj += dj[way];
		}
		move[way] = movable[place[way]][status];
		ans[way] = table[place[way]][status];
	}
	for(int way=0;way<4;way++){
		if(!move[way])continue;
		int myi = sti[way];
		int myj = stj[way];
		int mask = 3<<14;
		for(int k=7;k>=0;k--){
			board[myi][myj] = (ans[way]>>(k*2))&3;
			myi += di[way];
			myj += dj[way];
		}
	}
	board[thei][thej] = type;
}

void othello_game::getBoard(int board[8][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			board[i][j] = this->board[i][j+7];
		}
	}
}

void manPut(othello_game&game,int type){
	int geti,getj;
	do{
		scanf("%d%d",&geti,&getj);
	}while(!game.canPut(geti,getj,type));
//puts("finish check");
	game.putChess(geti,getj,type);
}

void randomPut(othello_game&game,int type){
	int geti,getj;
	do{
		geti = rand()%8;
		getj = rand()%8;
	}while(!game.canPut(geti,getj,type));
//	printf("rand put:%d %d\n",geti,getj);
	game.putChess(geti,getj,type);
}

void show(othello_game&game){
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

void test(){
	for(int i=0;i<8;i++){
		for(int j=0;j<1<<16;j++){
			if(MoveTable::move_table.row_can_put_black[i][j]){
				printf("can put on %dth place in %d\n",i,j)	;
				return ;
			}
		}
	}
	puts("No place");
}

int test2(int status,int place,int type){
	int mask = 3<<(7-place)*2;
	if((status&mask)!=0) return 0;
	int enemy = 3-type;
	int typerow = 0;
	int enemyrow = 0;
	for(int i=0;i<8;i++){
		typerow <<= 2;
		typerow |= type;
		enemyrow <<= 2;
		enemyrow |= enemy;
	}
	int ans = 0;
	int leftmask = mask<<2;
	while(leftmask!=(3<<16)&&(status&leftmask)==(enemyrow&leftmask)){
		leftmask <<= 2;
		if(leftmask!=(3<<16)&&(status&leftmask)==(typerow&leftmask)){
			ans = 2;
			break;
		}
	}
	int rightmask = mask>>2;
	while(rightmask!=0&&(status&rightmask)==(enemyrow&rightmask)){//even out of bound will break the loop
		rightmask >>= 2;
		if(rightmask!=0&&(status&rightmask)==(typerow&rightmask)){
			return ans+1;
		}
	}
	return ans;
}

int test4(int status,int place,int type,int code);

void test3(){
//	int ans = MoveTable::move_table.row_after_put_black[2][2<<8|1<<6];
	int ans = test4(2<<8|1<<6,2,1,1);
	for(int i=0;i<8;i++){
		printf("%d ",(ans>>((7-i)*2))&3);
	}
	puts("");
}


int test4(int status,int place,int type,int code){
	int ans = status;
	int mask = 3<<(7-place)*2;
	int enemy = 3-type;
	int typerow = 0;
	int enemyrow = 0;
	for(int i=0;i<8;i++){
		typerow <<= 2;
		typerow |= type;
		enemyrow <<= 2;
		enemyrow |= enemy;
	}
	if((code&2)){
		int leftmask = mask<<2;
		while(leftmask!=(3<<16)&&(status&leftmask)==(enemyrow&leftmask)){
			ans ^= leftmask;
			leftmask <<= 2;
		}
	}
	if((code&1)){
puts("here");
		int rightmask = mask>>2;
		while(rightmask!=0&&(status&rightmask)==(enemyrow&rightmask)){
printf("before:%d\t",status);
			ans ^= rightmask;
printf("after:%d\n",status);
			rightmask >>= 2;
		}
	}
	ans |= type<<(7-place)*2;
	return ans;
}


void solve(){
	int counter = 0;	
	othello_game game;
	game.init();
//	show(game);
	while(counter!=2){
		if(game.canMove(1)){
//			show(game);
//			manPut(game,1);
			randomPut(game,1);
			counter = 0;
//			show(game);
		}
		else{
//			puts("1 pass");
			counter++;
		}
		if(counter==2) break;
		if(game.canMove(2)){
			randomPut(game,2);
			counter = 0;
		}
		else{
//			puts("2 pass");
			counter++;
		}
	}
//	show(game);
}

int main(void){
	for(int i=0;i<100000;i++) solve();
	return 0;
}
