#pragma once
#include "Player.h"
#include "Deck.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class BlackJack
{
public:
	BlackJack(int numPlayers);
	BlackJack(BlackJack& copy);
	BlackJack& operator=(BlackJack& rhs);
	Player& operator[](int index);
	int getNumPlayers() const;
	Player* getPlayers();
	Player& getDealer();
	Deck& getDeck();
	void Play();
	void dealStartingHands();
	void playHand();
	~BlackJack();
private:
	Player* m_players;
	Player m_dealer;
	Deck m_playableDeck;
	int m_numPlayers;
};