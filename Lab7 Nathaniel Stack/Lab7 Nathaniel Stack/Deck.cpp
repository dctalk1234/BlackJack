#include "Deck.h"


/*
	create a deck of 52 cards
*/
Deck::Deck() : m_deck(), m_cardIndex(0)
{
	for (int i = 0; i < 13; i++)
	{
		(m_deck + i)->setSuit(Diamonds);
		(m_deck + i)->setVal((static_cast<value>(Ace + i)));
	}

	for (int i = 0; i < 13; i++)
	{
		(m_deck + i + 13)->setSuit(Hearts);
		(m_deck + i + 13)->setVal((static_cast<value>(Ace + i)));
	}

	for (int i = 0; i < 13; i++)
	{
		(m_deck + i + 26)->setSuit(Clubs);
		(m_deck + i + 26)->setVal((static_cast<value>(Ace + i)));
	}

	for (int i = 0; i < 13; i++)
	{
		(m_deck + i + 39)->setSuit(Spades);
		(m_deck + i + 39)->setVal((static_cast<value>(Ace + i)));
	}
	
}

Deck::Deck(Deck & deck)
{
	
		for (int i = 0; i < 52; i++)
		{
			*(m_deck + i) = *(deck.m_deck + i);
		}
		m_cardIndex = deck.m_cardIndex;
}

Deck & Deck::operator=(Deck & rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 52; i++)
		{
			*(m_deck + i) = *(rhs.m_deck + i);
		}
		m_cardIndex = rhs.m_cardIndex;
	}

	return *this;
}

/*
	shuffle the deck using the random class
*/

void Deck::shuffle()
{
	for (int i = 0; i < 51; i++)
	{
		RandNumGen j;
		card temp;

		temp = *(m_deck + i);
		*(m_deck + i) = *(m_deck + j.returnRandNum());
		*(m_deck + j.returnRandNum()) = temp;

	}
	m_cardIndex = 0;
}

/*
	deal a card from the deck
*/
card Deck::deal()
{
	if (m_cardIndex < 52)
	{
		card temp = m_deck[m_cardIndex];
		m_cardIndex++;
		return temp;
	}
	else
	{
		throw "deck empty";
	}
	
}


Deck::~Deck()
{
}
