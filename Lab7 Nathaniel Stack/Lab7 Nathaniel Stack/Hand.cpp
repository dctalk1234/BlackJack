#include "Hand.h"



Hand::Hand() : m_hand(nullptr), m_numCards(0), m_continue(true), m_bust(false), m_blackJack(false)
{
}

Hand::Hand(Hand & copy) : m_hand(nullptr), m_numCards(0)
{
	m_numCards = copy.m_numCards;
	if (copy.m_hand != nullptr)
	{
		m_hand = new card[m_numCards];
		for (int i = 0; i < m_numCards; i++)
		{
			*(m_hand + i) = *(copy.m_hand + i);
		}
	}
	m_continue = copy.m_continue;
	m_bust = copy.m_bust;
	m_blackJack = copy.m_blackJack;
}

Hand & Hand::operator=(Hand & rhs)
{
	if (this != &rhs)
	{
		delete[] m_hand;
		m_hand = nullptr;
		m_numCards = rhs.m_numCards;
		m_continue = rhs.m_continue;
		m_bust = rhs.m_bust;
		m_blackJack = rhs.m_blackJack;
		if (rhs.m_hand != nullptr)
		{
			m_hand = new card[m_numCards];
			for (int i = 0; i < m_numCards; i++)
			{
				*(m_hand + i) = *(rhs.m_hand + i);
			}
		}
	}

	return *this;
}

/*
	add a card to the hand and also check for both blackjack and bust conditions. if bust then check to see if there is an ace in the hand and if so change its value from 11 to 1
*/
void Hand::addCard(card cardToAdd)
{
	Hand temp;
	int handTotal = 0;
	temp = *this;
	delete[] m_hand;
	m_hand = new card[m_numCards + 1];
	for (int i = 0; i < m_numCards; i++)
	{
		*(m_hand + i) = *(temp.m_hand + i);
		handTotal += (m_hand + i)->getVal();
	}
	*(m_hand + m_numCards) = cardToAdd;
	handTotal += (m_hand + m_numCards)->getVal();

	m_numCards++;

	if (handTotal > 21)
	{
		m_bust = true;
		m_continue = false;
		for (int i = 0; i < m_numCards; i++)
		{
			if ((m_hand + i)->getVal() == 11)
			{
				(m_hand + i)->setVal(ace);
				m_bust = false;
				m_continue = true;
			}
		}
	}
	else if (handTotal == 21)
	{
		m_continue = false;
		m_blackJack = true;
	}
}

/*
	subt last card from hand
*/
void Hand::subtLastCard()
{

	Hand temp;
	temp = *this;
	delete[] m_hand;
	m_hand = new card[m_numCards - 1];
	for (int i = 0; i < m_numCards - 1; i++)
	{
		*(m_hand + i) = *(temp.m_hand + i);
	}
	
	m_numCards--;
}

/*
	return the card at a specific offset in the hand
*/

card & Hand::operator[](int index) const
{
	if (index >= 0 && index < m_numCards)
	{
		return *(m_hand + index);
	}
	else
	{
		throw char("invalid index");
	}
}

card * Hand::getHand()
{
	return m_hand;
}

int Hand::getNumCards()
{
	return m_numCards;
}

/*
	display a hand objcet
*/
void Hand::display() const
{
	for (int i = 0; i < m_numCards; i++)
	{
		(m_hand + i)->display();
	}
	
}

void Hand::displayDealer()
{
	(m_hand +1)->display();
}

void Hand::setContinue(bool state)
{
	m_continue = state;
}

bool Hand::getContinue()
{
	return m_continue;
}

bool Hand::getBust()
{
	return m_bust;
}

bool Hand::getBlackJack()
{
	return m_blackJack;
}

int Hand::returnHandVal()
{
	int temp = 0;
	for (int i = 0; i < m_numCards; i++)
	{
		temp += (m_hand + i)->getVal();
	}
	
	return temp;
}

Hand::~Hand()
{
	delete[] m_hand;
	m_hand = nullptr;
	m_numCards = 0;
	m_continue = true;
}
