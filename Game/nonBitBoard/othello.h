#ifndef OTHELLO
#define OTHELLO
class othello{
public:
	othello();
	~othello();
	void init();
	bool legalCoordinate(int,int);
	bool canPut(int,int,int);
	bool canMove(int);
	void putChess(int,int,int);
	void getBoard(int [][8]);
	void setBoard(int [][8]);
private:
	int **board;
};
#endif
