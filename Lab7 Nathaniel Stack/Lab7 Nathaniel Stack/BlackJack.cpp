#include "BlackJack.h"



/*
	BlackJack constructor that creates a default player object for the dealer and then creates the desired number of player objects depending on user input
	along with a single deck object for the game and then calls the blackjack play function with those objects.
*/
BlackJack::BlackJack(int numPlayers) : m_players(nullptr), m_playableDeck(), m_numPlayers(0), m_dealer()
{
	if (numPlayers > 0)
	{
		m_numPlayers = numPlayers;
		m_players = new Player[m_numPlayers];
		m_playableDeck.shuffle();
		Play();
	}
}

/*
	copy constructor for blackjack object.
*/
BlackJack::BlackJack(BlackJack & copy) : m_players(nullptr), m_playableDeck(copy.m_playableDeck), m_dealer(copy.m_dealer)
{
	m_players = new Player[copy.m_numPlayers];
	m_numPlayers = copy.m_numPlayers;
	for (int i = 0; i < m_numPlayers; i++)
	{
		*(m_players + i) = *(copy.m_players + i);
	}
	m_playableDeck.shuffle();
}

/*
	blackjack op=
*/
BlackJack & BlackJack::operator=(BlackJack & rhs)
{
	if (this != &rhs)
	{
		delete[] m_players;
		m_players = new Player[rhs.m_numPlayers];
		m_numPlayers = rhs.m_numPlayers;
		for (int i = 0; i < m_numPlayers; i++)
		{
			*(m_players + i) = *(rhs.m_players + i);
		}
		m_playableDeck.shuffle();
		m_dealer = rhs.m_dealer;
	}
	return *this;
}

/*
	this function overloads the [] operator the return a specific player from the array of players pointed to by m_players
*/
Player & BlackJack::operator[](int index)
{
	if (index >= 0 && index < m_numPlayers)
	{
		return *(m_players + index);
	}
	else
	{
		throw char("invalid index");
	}
}

/*
	returns the number of players in the game
*/
int BlackJack::getNumPlayers() const
{
	return m_numPlayers;
}

/*
	
*/
Player * BlackJack::getPlayers()
{
	return m_players;
}

Player & BlackJack::getDealer()
{
	return m_dealer;
}

Deck& BlackJack::getDeck()
{
	return m_playableDeck;
}

void BlackJack::Play()
{
	char temp;
	bool nextHand = true;
	Hand start;
	while (nextHand)
	{
		for (int i = 0; i < m_numPlayers; i++)
		{
			(m_players + i)->getMain() = start;
			(m_players + i)->getSplit() = start;
			(m_players + i)->getSplit().setContinue(false);
		}
		m_dealer.getMain() = start;
		m_playableDeck.shuffle();
		dealStartingHands();
		playHand();

		cout << "play another hand? y/n" << endl;
		cin >> temp;

		if (temp == 'N' || temp == 'n')
		{
			nextHand = false;
		}
	}
}

void BlackJack::dealStartingHands()
{
	const int blackJack = 21;
	int playerCount = m_numPlayers;
	card temp;
	card dealerTemp;
	float bet;
	for (int i = 0; i < playerCount; i++)
	{
		cout << "player " << i << " enter you dollar amount wager" << endl;
		bet = 0;
		cin >> bet;

		if (bet < 2)
		{
			cout << "bet too small minimum bet of 2 placed" << endl;
			(m_players + i)->playerBetMain(2);
		}
		else
		{
			(m_players + i)->playerBetMain(bet);
		}

	}

	for (int j = 0; j < 2; j++)                       //deal cards to players
	{
		for (int i = 0; i < playerCount; i++)
		{
			temp = (m_playableDeck.deal());
			(m_players + i)->hitMain(temp);
		}
		dealerTemp = (m_playableDeck.deal());         //deal to dealer
		m_dealer.hitMain(dealerTemp);
	}
}

void BlackJack::playHand()
{
	int roundCount = 1;
	const int blackJack = 21;
	int playerCount = m_numPlayers;
	card temp;
	card dealerTemp;
	float bet;
	int handNotDone = 1;
	/**********************start of player phase********************************/
	while (handNotDone != 0)
	{
		handNotDone = 0;
		for (int i = 0; i < playerCount; i++)             //player decisions
		{


			char decision;
			cout << "dealer has ";
			m_dealer.getMain().displayDealer();
			cout << endl;
			cout << "player " << i << "cards= ";
			(m_players + i)->getMain().display();                  //display what cards a player recieved
			cout << endl;
			cout << "Bankroll remaining = " << ((m_players + i)->getBankroll()) << endl;           //display remaining bankroll to help with decisions

			/*****************************check split condition ******************************************/

			if (m_players->getMain()[0] == m_players->getMain()[1])           //if a split is possible
			{
				cout << "would you like to split? y/n" << endl;                        //prompt user to make decision

				cin >> decision;
				if (decision == 'Y' || decision == 'y')                    //if yes handle split condition
				{
					bet = (m_players + i)->getPlayerBetMain();        // double bet
					(m_players + i)->playerBetSplit(bet);
					(m_players + i)->split();                    //split hands
					temp = (m_playableDeck.deal());
					(m_players + i)->hitMain(temp);                //hit each hand once since both hands must have at least 2 cards
					temp = (m_playableDeck.deal());
					(m_players + i)->hitSplit(temp);



					cout << "player " << i << "main hand cards= ";             //display both hands following the hits
					(m_players + i)->getMain().display();
					cout << endl;
					cout << "player " << i << "split hand cards= ";
					(m_players + i)->getSplit().display();
					cout << endl;

					(m_players + i)->getSplit().setContinue(true);
				}
			}
			/*******************************check double down decisions**************************************/
			if (roundCount == 1)
			{
				if ((m_players + i)->getIsSplit())
				{
					cout << "Would you like to double down on main hand? y/n" << endl;
					cin >> decision;
					if (decision == 'Y' || decision == 'y')                          //if yes
					{
						bet = (m_players + i)->getPlayerBetMain();              //double bet
						(m_players + i)->playerBetMain(bet);
					}

					cout << "Would you like to double down on split hand? y/n" << endl;
					cin >> decision;
					if (decision == 'Y' || decision == 'y')                          //if yes
					{
						bet = (m_players + i)->getPlayerBetSplit();              //double bet
						(m_players + i)->playerBetSplit(bet);
					}
				}
				else
				{
					cout << "Would you like to double down on main hand? y/n" << endl;
					cin >> decision;
					if (decision == 'Y' || decision == 'y')                          //if yes
					{
						bet = (m_players + i)->getPlayerBetMain();              //double bet
						(m_players + i)->playerBetMain(bet);
					}
				}
			}

			/****************************************check Player hit decisions***********************************/
			if ((m_players + i)->getIsSplit())
			{
				if (((m_players + i)->getMain().getContinue()))              //if hand not in stay state
				{
					cout << "would you like to hit your main hand? y/n" << endl;       //prompt for decision
					cin >> decision;
					if (decision == 'Y' || decision == 'y')                          //if yes
					{
						temp = (m_playableDeck.deal());                             //deal card and add to main hand
						(m_players + i)->hitMain(temp);
						if ((m_players + i)->getMain().getBlackJack())              //check for blackjack
						{
							cout << "BLACKJACK!!!!!!!!!" << endl;
						}
						else if ((m_players + i)->getMain().getBust())              //check for bust
						{
							cout << "BUST" << endl;
						}
					}
					else
					{
						(m_players + i)->getMain().setContinue(false);              //set stay state on hand
					}
				}


				if (((m_players + i)->getSplit().getContinue()))
				{
					cout << "would you like to hit your split hand? y/n" << endl;       //prompt for decision
					cin >> decision;
					if (decision == 'Y' || decision == 'y')                          //if yes
					{
						temp = (m_playableDeck).deal();                             //deal card and add to split hand
						(m_players + i)->hitSplit(temp);

						if ((m_players + i)->getMain().getBlackJack())               //check for blackjack
						{
							cout << "BLACKJACK!!!!!!!!!" << endl;
						}
						else if ((m_players + i)->getMain().getBust())				//check for bust
						{
							cout << "BUST" << endl;
						}
					}
					else
					{
						(m_players + i)->getSplit().setContinue(false);                    //set stay state on hand
					}
				}
			}
			else                                                                     //if player has not split hand
			{
				if (((m_players + i)->getMain().getContinue()))              //if hand not in stay state
				{
					cout << "would you like to hit? y/n" << endl;                     //prompt for decision
					cin >> decision;

					if (decision == 'Y' || decision == 'y')                          // if yes
					{
						temp = (m_playableDeck.deal());                             //deal card and add to players hand
						(m_players + i)->getMain().addCard(temp);

						if ((m_players + i)->getMain().getBlackJack())               //check for blackjack
						{
							cout << "BLACKJACK!!!!!!!!!" << endl;
						}
						else if ((m_players + i)->getMain().getBust())				//check for bust
						{
							cout << "BUST" << endl;
						}
					}
					else
					{
						(m_players + i)->getMain().setContinue(false);
					}
				}
			}
		}
		roundCount++;
		for (int i = 0; i < playerCount; i++)
		{
			handNotDone += (m_players + i)->getMain().getContinue();
			handNotDone += (m_players + i)->getSplit().getContinue();
		}
	}


	/****************Automated Dealer Code***************/
	handNotDone = 1;

	while (handNotDone)
	{
		m_dealer.getMain().display();
		cout << endl;
		if (m_dealer.getMain().getContinue())
		{
			if ((m_dealer.getMain().getBlackJack()))
			{
				cout << "dealer delt blackjack" << endl;
				m_dealer.getMain().setContinue(false);                    //set stay state on hand
			}
			else
			{
				if (m_dealer.getMain().returnHandVal() < 17)
				{
					temp = (m_playableDeck.deal());                             //deal card and add to main hand
					m_dealer.hitMain(temp);

					if (m_dealer.getMain().getBlackJack())               //check for blackjack
					{
						cout << "BLACKJACK!!!!!!!!!" << endl;
					}
					else if (m_dealer.getMain().getBust())				//check for bust
					{
						cout << "BUST" << endl;
					}
				}
				else
				{
					m_dealer.getMain().setContinue(false);                    //set stay state on hand
				}
			}
		}
		handNotDone = m_dealer.getMain().getContinue();
		cout << "dealer has ";
		m_dealer.getMain().display();
		cout << endl;
	}

	/***********************Payout Code**************************/
	for (int i = 0; i < m_numPlayers; i++)
	{
		//if dealer got blackjack
		if (m_dealer.getMain().getBlackJack())                                     
		{
			if ((m_players + i)->getIsSplit())                             //if player split hand
			{
				if ((m_players + i)->getMain().getBlackJack())                        //if player main also got blackjack
				{
					(m_players + i)->playerCollect((m_players + i)->getPlayerBetMain());      //push
				}
				else if ((m_players + i)->getSplit().getBlackJack())						//if player split also got blackjack
				{
					(m_players + i)->playerCollect((m_players + i)->getPlayerBetSplit());    //push
				}	
			}	
			else
			{
				if ((m_players + i)->getMain().getBlackJack())                        //if player main also got blackjack
				{
					(m_players + i)->playerCollect((m_players + i)->getPlayerBetMain());      //push
				}
			}
		}   //if dealer busted
		else if (m_dealer.getMain().getBust())
		{
			if ((m_players + i)->getIsSplit())                                      //if player split hand
			{
				if (!((m_players + i)->getMain().getBust()))                        //if player main did not bust
				{
					if ((m_players + i)->getMain().getBlackJack())                     //if player main got blackjack
					{
						(m_players + i)->playerCollect(2.5 * ((m_players + i)->getPlayerBetMain()));      //pay him for blackjack
					}
					else
					{
						(m_players + i)->playerCollect(2 * ((m_players + i)->getPlayerBetMain()));      //pay him
					}
					
				}
				if (!((m_players + i)->getSplit().getBust()))                        //if player split did not bust
				{
					if ((m_players + i)->getSplit().getBlackJack())                     //if player split got blackjack
					{
						(m_players + i)->playerCollect(2.5 * ((m_players + i)->getPlayerBetSplit()));      //pay him for blackjack
					}
					else
					{
						(m_players + i)->playerCollect(2 * ((m_players + i)->getPlayerBetSplit()));      //pay him
					}
				}
			}
			else
			{
				if (!((m_players + i)->getMain().getBust()))                              //if player did not bust
				{
					if ((m_players + i)->getMain().getBlackJack())                     //if play got blackjack
					{
						(m_players + i)->playerCollect(2.5 * ((m_players + i)->getPlayerBetMain()));      //pay him for blackjack
					}
					else
					{
						(m_players + i)->playerCollect(2 * ((m_players + i)->getPlayerBetMain()));      //pay him
					}
				}
			}
		}
		else   //dealer does not have blackjack and did not bust
		{
			if ((m_players + i)->getIsSplit())                                //if player split hands
			{
				if (!((m_players + i)->getMain().getBust()))                          //if player main has not busted
				{
					if ((m_players + i)->getMain().returnHandVal() > m_dealer.getMain().returnHandVal())         //if player main has higher hand then dealer
					{
						if ((m_players + i)->getMain().getBlackJack())                     //if play got blackjack
						{
							(m_players + i)->playerCollect(2.5 * ((m_players + i)->getPlayerBetMain()));      //pay him for blackjack
						}
						else
						{
							(m_players + i)->playerCollect(2 * ((m_players + i)->getPlayerBetMain()));      //pay him
						}
					}
					else if ((m_players + i)->getMain().returnHandVal() == m_dealer.getMain().returnHandVal())      //if player main hand equals dealer
					{
						(m_players + i)->playerCollect((m_players + i)->getPlayerBetMain());                           //push
					}
				}
				if (!((m_players + i)->getSplit().getBust()))								 //if player split has not busted
				{
					if ((m_players + i)->getSplit().returnHandVal() > m_dealer.getMain().returnHandVal())    //if player split has higher hand then dealer
					{
						if ((m_players + i)->getSplit().getBlackJack())                     //if player split got blackjack
						{
							(m_players + i)->playerCollect(2.5 * ((m_players + i)->getPlayerBetSplit()));      //pay him for blackjack
						}
						else
						{
							(m_players + i)->playerCollect(2 * ((m_players + i)->getPlayerBetSplit()));      //pay him
						}
					}
					else if ((m_players + i)->getSplit().returnHandVal() == m_dealer.getMain().returnHandVal())       //if player split hand equals dealer
					{
						(m_players + i)->playerCollect((m_players + i)->getPlayerBetSplit());                     //push
					}
				}
			}
			else
			{
				if (!((m_players + i)->getMain().getBust()))                          //if player main has not busted
				{
					if ((m_players + i)->getMain().returnHandVal() > m_dealer.getMain().returnHandVal())         //if player main has higher hand then dealer
					{
						if ((m_players + i)->getMain().getBlackJack())                     //if play got blackjack
						{
							(m_players + i)->playerCollect(2.5 * ((m_players + i)->getPlayerBetMain()));      //pay him for blackjack
						}
						else
						{
							(m_players + i)->playerCollect(2 * ((m_players + i)->getPlayerBetMain()));      //pay him
						}
					}
					else if ((m_players + i)->getMain().returnHandVal() == m_dealer.getMain().returnHandVal())      //if player main hand equals dealer
					{
						(m_players + i)->playerCollect((m_players + i)->getPlayerBetMain());               //push
					}
				}
			}
		}
	}

	/****************display remaining bankroll****************/
	for (int i = 0; i < m_numPlayers; i++)
	{
		cout << "player " << i + 1 << "bankroll remaining = ";
		cout << (m_players + i)->getBankroll();
		cout << endl;
	}
}

BlackJack::~BlackJack()
{
	delete[] m_players;
	m_players = nullptr;
	m_numPlayers = 0;
}
