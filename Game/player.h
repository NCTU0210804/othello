#ifndef PLAYER
#define PLAYER
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
#endif
