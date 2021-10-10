#include <iostream>
#include <array>

using namespace std;

namespace CardGame
{
	enum Rank
	{
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE,
		COUNTCARD
	};

	enum Suit
	{
		HEARTS,
		CLUBS,
		SPADES,
		CROSSES,
		COUNTSUIT
	};

	enum class Result
	{
		WIN,
		LOSE,
		DROW
	};

	const int lengthDeck = COUNTCARD * COUNTSUIT;
}

struct Card
{
	CardGame::Rank card;
	CardGame::Suit suit;
};

void printCard(const Card& game)
{
	switch (game.card)
	{
	case CardGame::TWO:
		cout << "2";
		break;
	case CardGame::THREE:
		cout << "3";
		break;
	case CardGame::FOUR:
		cout << "4";
		break;
	case CardGame::FIVE:
		cout << "5";
		break;
	case CardGame::SIX:
		cout << "6";
		break;
	case CardGame::SEVEN:
		cout << "7";
		break;
	case CardGame::EIGHT:
		cout << "8";
		break;
	case CardGame::NINE:
		cout << "9";
		break;
	case CardGame::TEN:
		cout << "10";
		break;
	case CardGame::JACK:
		cout << "J";
		break;
	case CardGame::QUEEN:
		cout << "Q";
		break;
	case CardGame::KING:
		cout << "K";
		break;
	case CardGame::ACE:
		cout << "A";
		break;
	default:
		break;
	}

	switch (game.suit)
	{
	case CardGame::HEARTS:
		cout << "H";
		break;
	case CardGame::CLUBS:
		cout << "C";
		break;
	case CardGame::SPADES:
		cout << "S";
		break;
	case CardGame::CROSSES:
		cout << "CR";
		break;
	default:
		break;
	}
}

void printDeck(const array <Card, CardGame::lengthDeck>& deck)
{
	int i = 0;
	for (const auto& var : deck)
	{
		printCard(var);
		cout << ' ';
		++i;

		if (i % 13 == 0)
		{
			cout << endl;
		}
	}
}

void swapCard(Card& a, Card& b)
{
	Card temp = a;
	a = b;
	b = temp;
}

void shuffleDeck(array <Card, CardGame::lengthDeck>& deck)
{
	int a, b, r;
	a = 0;
	b = CardGame::lengthDeck - 1;

	for (int i = 0; i < CardGame::lengthDeck; i++)
	{
		r = a + rand() % b - a + 1;
		swapCard(deck[i], deck[r]);
	}
}

int getCardValue(const Card& card, int& aceOne)
{
	switch (card.card)
	{
	case CardGame::TWO:
		return 2;
	case CardGame::THREE:
		return 3;
	case CardGame::FOUR:
		return 4;
	case CardGame::FIVE:
		return 5;
	case CardGame::SIX:
		return 6;
	case CardGame::SEVEN:
		return 7;
	case CardGame::EIGHT:
		return 8;
	case CardGame::NINE:
		return 9;
	case CardGame::TEN:
	case CardGame::JACK:
	case CardGame::QUEEN:
	case CardGame::KING:
		return 10;
	case CardGame::ACE:
		/*if (aceOne == true)
		{
			return 1;
		} else return 11;*/
		++aceOne;
		return 11;
	default:
		return 0;
	}
}

//bool cheakAce(const vector <Card> &d)
//{
//	for (const auto &var : d)
//	{
//		if (var.card == CardGame::ACE)
//		{
//			return true;
//		}
//	}
//	return false;
//}

CardGame::Result playBlackjack(const array <Card, CardGame::lengthDeck> d)
{
	int aceOne = 0;
	bool secondChance = true;

	//array <Card, 52> playerDeck;
	//vector <Card> playerDeck;
	const Card* cardPtr = &d[0];
	int dilerScore = getCardValue(*cardPtr++, aceOne);

	aceOne = 0;
	int playerScore = 0;
	//int i = 0;
	//playerDeck[i++] = *cardPtr;
	playerScore += getCardValue(*cardPtr++, aceOne);
	//playerDeck[i++] = *cardPtr;
	playerScore += getCardValue(*cardPtr++, aceOne);

	while (true)
	{
		if (playerScore > 21 && aceOne == 0) {

			/*if (!(cheakAce(playerDeck)) || secondChance == true)
			{*/
			cout << "Your score " << playerScore;
			return CardGame::Result::LOSE;
			/*}
			else
			{
				cout << "You score " << playerScore << ". You lose, but now second chance." << endl;
				aceOne = true;
				secondChance = true;
				playerScore = 0;
				const Card* playerCardPtr = &playerDeck[0];

				for (int j = 0; j < i; j++)
				{
					playerScore += getCardValue(*playerCardPtr++, aceOne);
				}
			}		*/
		}
		else if (playerScore > 21 && aceOne > 0 && secondChance == true)
		{
			cout << "You score " << playerScore << ". You lose, but now second chance." << endl;
			while (aceOne > 0)
			{
				playerScore -= 10;
				--aceOne;
			}
			secondChance = false;
		}
		else if (!secondChance)
		{
			while (aceOne > 0)
			{
				playerScore -= 10;
				--aceOne;
			}
		}

		cout << "Your score " << playerScore << ". Hit(1) or stand(2)?: ";
		int choice;
		cin >> choice;
		if (choice == 2) {
			aceOne = false;
			break;
		}
		//playerDeck[i++] = *cardPtr;
		playerScore += getCardValue(*cardPtr++, aceOne);
	}

	while (dilerScore < 17)
	{
		dilerScore += getCardValue(*cardPtr++, aceOne);
	}

	if (dilerScore <= 21) {
		cout << "Diler score " << dilerScore;
		if (dilerScore < playerScore)
		{
			return CardGame::Result::WIN;
		}
		else if (dilerScore > playerScore)
		{
			return CardGame::Result::LOSE;
		}
		else
		{
			return CardGame::Result::DROW;
		}
	}
	else {
		cout << "Diler score " << dilerScore;
		return CardGame::Result::WIN;
	}
}
//
//double MashtabDouble(double x_min, double x_max, double y_min, double y_max, double x)
//{
//	// Линейное маштабирование y(x)=kx+b
//	double y;
//	y = ((y_max - y_min) / (x_max - x_min) * (x - x_min)) + y_min;
//	return y;
//
//}
//
////Получение одномерного рандомного массива
//void getRandMassiv(int* array, const int lenght, double dmin, double dmax)
//{
//	// инициализируем Вихрь Мерсенна случайным стартовым числом
//	random_device rd;
//	mt19937 mersenne(rd());
//	// маска для усечения числа до 16 битов
//	const unsigned int lowMask = 0xFF;
//	for (int index = 0; index < lenght; ++index)
//	{
//		unsigned long long int rnd_x{ mersenne() };
//		rnd_x &= lowMask;
//		//Преобразование в Int с приведением к диапазону [dmin-dmax] и округлением
//		array[index] = (int)round(MashtabDouble(0.0, (double)lowMask, dmin, dmax, (double)rnd_x));
//	}
//
//}
//

int main()
{
	srand(static_cast<unsigned int>((time(NULL))));
	array <Card, CardGame::lengthDeck> deck;
	int k = 0;

	for (int i = 0; i < CardGame::COUNTSUIT; i++)
	{
		for (int j = 0; j < CardGame::COUNTCARD; j++)
		{
			deck[k].suit = static_cast<CardGame::Suit>(i);
			deck[k].card = static_cast<CardGame::Rank>(j);
			++k;
		}
	}

	/*Card a{ CardGame::ACE, CardGame::CLUBS};
	Card w{ CardGame::ACE, CardGame::CROSSES };
	Card s{ CardGame::ACE, CardGame::HEARTS };
	Card d{ CardGame::ACE, CardGame::SPADES };*/

	shuffleDeck(deck);

	/*deck[1] = a;
	deck[2] = w;
	deck[4] = s;
	deck[6] = s;*/

	printDeck(deck);
	int reuslt = static_cast<int>(playBlackjack(deck));
	if (reuslt == 0)
	{
		cout << ". You win!" << endl;
	}
	else if (reuslt == 1)
	{
		cout << ". You lose!" << endl;
	}
	else
	{
		cout << ". Drow." << endl;
	}
}

