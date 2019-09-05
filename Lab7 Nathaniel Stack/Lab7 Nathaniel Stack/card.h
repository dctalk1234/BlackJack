#pragma once
#include <iostream>
using std::cout;
using std::endl;
enum value {Ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
enum suit { Spades, Clubs, Hearts, Diamonds };

class card
{
public:
	card();
	card(value val, suit s);
	card(card& data);
	card& operator=(const card& rhs);
	bool operator==(const card& rhs);
	int getVal() const;
	void setVal(value val);
	suit getSuit() const;
	void setSuit(suit s);
	void display();
	~card();
private:
	 value m_cardVal;
	 suit m_cardSuit;
};

