#include "Player.h"



Player::Player() : m_main(), m_split(), m_betMain(0), m_bankroll(100), m_isSplit(false), m_betSplit(0)
{
	m_split.setContinue(false);
}

Player::Player(Player & pl) : m_main(), m_split(), m_bankroll(100), m_isSplit(false)
{
	m_main = pl.m_main;
	m_split = pl.m_split;
	m_betMain = pl.m_betMain;
	m_betSplit = pl.m_betSplit;
	m_bankroll = pl.m_bankroll;
	m_isSplit = pl.m_isSplit;
	
}

Player & Player::operator=(Player & rhs)
{
	if (this != &rhs)
	{
		m_main = rhs.m_main;
		m_split = rhs.m_split;
		m_betMain = rhs.m_betMain;
		m_bankroll = rhs.m_bankroll;
		m_isSplit = rhs.m_isSplit;
		m_betSplit = rhs.m_betSplit;
	}

	return *this;
}

/*
	split hand between main hand and split hand
*/
void Player::split()
{
	m_split.addCard(m_main[1]);
	m_main.subtLastCard();
	m_isSplit = true;
}

/*
	add card to main hand
*/
void Player::hitMain(card hit)
{
	m_main.addCard(hit);
}


Hand & Player::getMain()
{
	return m_main;
}

/*
	add card to split hand
*/
void Player::hitSplit(card hit)
{
	m_split.addCard(hit);
}

Hand & Player::getSplit()
{
	return m_split;
}

/*
	bet on main hand by subtracting from total bankroll
*/
void Player::playerBetMain(float bet)
{
	m_betMain += bet;
	m_bankroll -= bet;
}

/*
	bet on split hand by subtracting from total bankroll
*/
void Player::playerBetSplit(float bet)
{
	m_betSplit += bet;
	m_bankroll -= bet;
}

float Player::getPlayerBetMain()
{
	return m_betMain;
}

float Player::getPlayerBetSplit()
{
	return m_betSplit;
}

/*
	collect winnings and add then to the bankroll
*/
void Player::playerCollect(float winnings)
{
	m_bankroll += winnings;
	m_betMain = 0;
}

float Player::getBankroll()
{
	return m_bankroll;
}

/*
	check if hand is split
*/
bool Player::getIsSplit()
{
	return m_isSplit;
}

/*
	reset hands to default.
*/
void Player::purgeHand()
{
	Hand start;
	m_main;
	m_split = start;
}

Player::~Player()
{
}