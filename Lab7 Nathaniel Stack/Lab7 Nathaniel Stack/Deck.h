#pragma once
#include "card.h"
#include "RandNumGen.h"
#include <stdlib.h>
class Deck
{
public:
	Deck();
	Deck(Deck& deck);
	Deck& operator=(Deck& rhs);
	void shuffle();
	card deal();
	~Deck();
private:
	card m_deck[52];
	int m_cardIndex;
};

