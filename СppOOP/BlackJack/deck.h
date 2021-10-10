#include <iostream>
#include <array>
#include "card.h"

#ifndef DECK_H
#define DECK_H

class Deck
{
public:
	Deck();
	void printDeck() const;
	void shuffleDeck();
	const Card& dealCard();
private:
	std::array <Card, 52> m_deck;
	int m_cardIndex = 0;
	static int getRandomNumber(int min, int max);
	static void swapCard(Card& a, Card& b);
};
#endif // !DECK_H
