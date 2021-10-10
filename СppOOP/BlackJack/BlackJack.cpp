#include <iostream>
#include <array>
#include <ctime> // для time()
#include <cstdlib> // для rand() и srand()
#include "card.h"
#include "deck.h"

char getPlayerChoice()
{
	std::cout << "(h) to hit, or (s) to stand: ";
	char choice;
	do
	{
		std::cin >> choice;
	} while (choice != 'h' && choice != 's');

	return choice;
}

bool playBlackjack(Deck& deck)
{
	int playerTotal = 0;
	int dealerTotal = 0;

	// Дилер получает одну карту
	dealerTotal += deck.dealCard().getCardValue();
	std::cout << "The dealer is showing: " << dealerTotal << '\n';

	// Игрок получает две карты
	playerTotal += deck.dealCard().getCardValue();
	playerTotal += deck.dealCard().getCardValue();

	// Игрок начинает
	while (1)
	{
		std::cout << "You have: " << playerTotal << '\n';
		char choice = getPlayerChoice();
		if (choice == 's')
			break;

		playerTotal += deck.dealCard().getCardValue();

		// Смотрим, не проиграл ли игрок
		if (playerTotal > 21)
			return false;
	}

	// Если игрок не проиграл (у него не больше 21), тогда дилер получает карты до тех пор, пока у него в сумме будет не меньше 17
	while (dealerTotal < 17)
	{
		dealerTotal += deck.dealCard().getCardValue();
		std::cout << "The dealer now has: " << dealerTotal << '\n';
	}

	// Если у дилера больше 21, то он проиграл, а игрок выиграл
	if (dealerTotal > 21)
		return true;

	return (playerTotal > dealerTotal);
}

int main()
{
	srand(static_cast<unsigned int>(time(0))); // используем системные часы в качестве стартового значения
	rand(); // пользователям Visual Studio: делаем сброс первого случайного числа

	Deck deck;
	deck.shuffleDeck();

	if (playBlackjack(deck))
		std::cout << "You win!\n";
	else
		std::cout << "You lose!\n";

	return 0;
}