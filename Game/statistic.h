#ifndef STATISTIC
#define STATISTIC
class statistic{
public:
	statistic(int a=0,int b=0,int c=0):black_win(a),white_win(b),draw_game(c){};
	void reset(){ black_win = white_win = draw_game = 0; }
	int black_win;
	int white_win;
	int draw_game;
};
#endif
