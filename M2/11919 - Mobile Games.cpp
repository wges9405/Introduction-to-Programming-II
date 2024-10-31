#include "11919.h"

int main() {
	int N;
	cin >> N;
	for (int n = 1; n <= N; n++) {
		// Read player info
		string name[2];
		int power[2], extra[2], p_type[2];
		/*
			p_type == 0 -> PoorPlayer
			p_type == 1 -> NTDWarrior
		*/
		for (int i = 0; i < 2; i++)
			cin >> name[i] >> p_type[i] >> power[i] >> extra[i];
		// Create player
		Player *p[2];
		for (int i = 0; i < 2; i++) {
			if (p_type[i] == 0) p[i] = new PoorPlayer(name[i], power[i], extra[i]);
			else p[i] = new NTDWarrior(name[i], power[i], extra[i]);
		}

		// Read game info
		int difficulty, g_type;
		/*
			g_type == 0 -> FreeGame
			g_type == 1 -> GTCGame
		*/
		cin >> difficulty >> g_type;
		// Create game
		Game *game;
		if (g_type == 0) game = new FreeGame(difficulty);
		else game = new GTCGame(difficulty);

		// Play game
		cout << "Game #" << n << ": ";
		game->play(*p[0], *p[1]);

		delete p[0];
		delete p[1];
		delete game;
	}
	return 0;
}
