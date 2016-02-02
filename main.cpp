#include <cstdio>
#include <cstdlib>
#include "Game/player.h"
#include "Game/gameManeger.h"
int main(){

	manPlayer man;
	randomPlayer random;
	random.setMessage(0);
	gameManeger maneger;
	maneger.setPassMassage(0);
	maneger.playgame(man,random);
}

