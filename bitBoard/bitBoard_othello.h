#ifndef BITBOARD_OTHELLO
#define BITBOARD_OTHELLO

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

class othello{
public:
	othello();
	void init();
	bool canPut(int thei,int thej,int type);
	bool canMove(int type);
	void putChess(int thei,int thej,int type);
	void getBoard(int [][8]);
//private:
	int **board;
};
#endif
