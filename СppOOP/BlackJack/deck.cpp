#include <iostream>
#include <cassert>
#include "deck.h"
#include "card.h"

Deck::Deck()
{
	int card = 0;
	for (int suit = 0; suit < Card::MAX_SUITS; ++suit)
		for (int rank = 0; rank < Card::MAX_RANKS; ++rank)
		{
			m_deck[card] = Card(static_cast<Card::CardRank>(rank), static_cast<Card::CardSuit>(suit));
			++card;
		}
}

void Deck::printDeck() const
{
	for (const auto& card : m_deck)
	{
		card.printCard();
		std::cout << ' ';
	}
	std::cout << '\n';
}

void Deck::shuffleDeck()
{
	// ���������� ������ ����� � ������
	for (int index = 0; index < 52; ++index)
	{
		// �������� ����� ��������� �����
		int swapIndex = getRandomNumber(0, 51);
		// ������ ������� � ����� ������� ������
		swapCard(m_deck[index], m_deck[swapIndex]);
	}
	m_cardIndex = 0;
}

const Card& Deck::dealCard()
{
	assert(m_cardIndex < 52);
	return m_deck[m_cardIndex++];	
}

int Deck::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); // ���������� static, ��� ��� ��� �������� ����� ��������� ��������
	// ���������� ������������ ���������� �������� �� ������ ���������
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Deck::swapCard(Card& a, Card& b)
{
	Card temp = a;
	a = b;
	b = temp;
}