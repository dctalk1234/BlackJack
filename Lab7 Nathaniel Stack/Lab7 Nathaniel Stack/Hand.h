#pragma once
#include "card.h"
class Hand
{
public:
	Hand();
	Hand(Hand& copy);
	Hand& operator=(Hand& rhs);
	void addCard(card cardToAdd);
	void subtLastCard();
	card& operator[](int index) const;
	card* getHand();
	int getNumCards();
	void display() const; 
	void displayDealer(); 
	void setContinue(bool state);
	bool getContinue();
	bool getBust();
	bool getBlackJack();
	int returnHandVal();
	~Hand();
private:
	card* m_hand;
	int m_numCards;
	bool m_bust;
	bool m_continue;
	bool m_blackJack;
};

