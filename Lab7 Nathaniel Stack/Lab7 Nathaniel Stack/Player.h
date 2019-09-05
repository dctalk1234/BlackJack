#pragma once
#include "Hand.h"
class Player
{
public:
	Player();
	Player(Player& pl);
	Player& operator=(Player& rhs);
	void split();
	void hitMain(card hit);
	Hand& getMain();
	void hitSplit(card hit);
	Hand& getSplit();
	void playerBetMain(float bet);
	void playerBetSplit(float bet);
	float getPlayerBetMain();
	float getPlayerBetSplit();
	void playerCollect(float winnings);
	float getBankroll();
	bool getIsSplit();
	void purgeHand();
	~Player();
private:
	Hand m_main;
	Hand m_split;
	float m_betMain;
	float m_betSplit;
	float m_bankroll;
	bool m_isSplit;
	
};

