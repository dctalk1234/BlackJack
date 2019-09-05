#pragma once
#include "BlackJack.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int selection = 0;
	cout << "enter number of Players?" << endl;       //ask user to enter number of players
	int numberOfPlayers = 0;
	cin >> numberOfPlayers;

	cout << "What game would you like to play" << endl;
	cin >> selection;

	switch (selection)
	{
		case 1:
			BlackJack playGame(numberOfPlayers);            //start a game of blackjack with that number of players
		break;
	}
	
	return 0;
}