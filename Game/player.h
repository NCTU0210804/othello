#ifndef PLAYER
#define PLAYER
class othelloPlayer{
public:
	virtual void init() = 0;
	virtual int generateMove(int [][8],int) = 0;
	virtual void getIllegaelMessage(int,int,int) = 0;
	virtual void gameOver(int [][8],int) = 0;
};

class manPlayer:public othelloPlayer{
public:
	virtual void init(){}//do notihing
	virtual int generateMove(int [][8],int);
	virtual void getIllegaelMessage(int,int,int);
	virtual void gameOver(int[][8],int);
};

class computerPlayer:public othelloPlayer{
public:
	virtual void init() = 0;
	virtual int generateMove(int [][8],int) = 0;
	virtual void gameOver(int [][8],int) = 0;
/*************************************************/
	virtual void getIllegaelMessage(int,int,int);
	void setMessage(bool open){sound = open;}
private:
	bool sound;
};

class randomPlayer:public computerPlayer{
public:
	virtual void init(){};//do nothing
	virtual int generateMove(int [][8],int);
	virtual void gameOver(int[][8],int){};//do nothing
};

#endif
