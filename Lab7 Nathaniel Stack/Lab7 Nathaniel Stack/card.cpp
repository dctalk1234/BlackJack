#include "card.h"



card::card() : m_cardSuit(Diamonds), m_cardVal(Ace)
{
}

card::card(value val, suit s) : m_cardSuit(s), m_cardVal(val)
{
}

card::card(card & data) : m_cardSuit(data.m_cardSuit), m_cardVal(data.m_cardVal)
{
}

card & card::operator=(const card& rhs)
{
	if (this != &rhs)
	{
		m_cardSuit = rhs.m_cardSuit;
		m_cardVal = rhs.m_cardVal;
	}
	
	return *this;
}

/* 
	test if both cards values are equal
*/

bool card::operator==(const card & rhs)
{
	bool test = false;
	if (m_cardVal == rhs.m_cardVal)
	{
		test = true;
	}

	return test;
}

/*
	return the correct numeric value
*/
int card::getVal() const
{
	int val = 0;

	if (m_cardVal == 14)             //if ace is one
	{
		val = 1;
	}
	else if (m_cardVal > 10)
	{
		val = 10;
	}
	
	else if (m_cardVal == 1)                 //if ace is eleven
	{
		val = 11;
	}
	else
	{
		val = m_cardVal;
	}
	
	return val;
}
/*
	set the value of the card
*/
void card::setVal(value val)
{
	m_cardVal = val;
}

suit card::getSuit() const
{
	return m_cardSuit;
}

void card::setSuit(suit s)
{
	m_cardSuit = s;
}

/*
	display a card object
*/
void card::display()
{
	char valText[14] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'a' };
	char suitText[4] = { 's', 'c', 'h', 'd' };

	if (m_cardVal == 14)
	{
		cout << valText[13];
		cout << suitText[m_cardSuit] << endl;
	}
	cout << valText[m_cardVal - 1];
	cout << suitText[m_cardSuit] << endl;

	
}

card::~card()
{
}


