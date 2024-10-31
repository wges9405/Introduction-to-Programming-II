#include <string>
#include <iostream>
using namespace std;
class Player {
protected:
    int power;
    string name;

public:
	Player(int basic, string name) {
		this->power = basic;
		this->name = name;
	}

    int get_base_power() const {
    	return power;
    }

    virtual int get_total_power() const = 0;

    string get_name() const {
    	return name;
    }

    virtual ~Player() {}
};

class NTDWarrior: public Player {
private:
	int dad_money;

public:
	NTDWarrior(string name, int basic, int money): Player(basic, name) {
		this->dad_money = money;
	}

	virtual ~NTDWarrior() {}

	virtual int get_total_power() const;
};

class PoorPlayer: public Player {
private:
	int kidney;

public:
	PoorPlayer(string name, int basic, int kidney): Player(basic, name) {
		this->kidney = kidney;
	}

	virtual ~PoorPlayer() {}

	virtual int get_total_power() const;
};

class Game {
protected:
	int difficulty;

public:
	Game(int diff) {
		this->difficulty = diff;
	}

	virtual void play(const Player& p1, const Player& p2) = 0;

	void print_result(int result_code, string winner) {
		if (result_code == 1) cout << winner << " wins!\n";
		else if (result_code == 2) cout << "Draw!\n";
		else if (result_code == 3) cout << "Failed!\n";
		else cout << "[ERROR] Unknown result_code!\n";
	}

	virtual ~Game() {}
};

class FreeGame: public Game {
public:
	FreeGame(int diff): Game(diff) {}
	virtual ~FreeGame() {};
	virtual void play(const Player& p1, const Player& p2);
};

class GTCGame: public Game {
public:
	GTCGame(int diff): Game(diff) {}
	virtual ~GTCGame() {}
	virtual void play(const Player& p1, const Player& p2);
};

///////////////////////////////////////////////////////////

int NTDWarrior::get_total_power() const {
    return power + 100*dad_money;
	//get_base_power       for FreeGame
	//get_total_power      for GTCGame
}

int PoorPlayer::get_total_power() const {
    return power + 100000*kidney;
	//get_base_power       for FreeGame
	//get_total_power      for GTCGame
}

void GTCGame::play(const Player& p1, const Player& p2) {
    int result = 0;
	int power_1 = p1.get_total_power(), power_2 = p2.get_total_power();
    string win = "0";
    if (power_1 < difficulty && power_2 < difficulty) result = 3;
    else if (power_1 == power_2) result = 2;
    else{
        result = 1;
        if (power_1 > power_2) win = p1.get_name();
        else win = p2.get_name();
    }
    print_result(result, win);
}

void FreeGame::play(const Player& p1, const Player& p2) {
    int result = 0;
	int power_1 = p1.get_base_power(), power_2 = p2.get_base_power();
    string win = "0";
    if (power_1 < difficulty && power_2 < difficulty) result = 3;
    else if (power_1 == power_2) result = 2;
    else{
        result = 1;
        if (power_1 > power_2) win = p1.get_name();
        else win = p2.get_name();
    }
    print_result(result, win);
}
