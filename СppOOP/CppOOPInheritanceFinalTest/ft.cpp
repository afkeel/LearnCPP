#include <iostream>
#include <ctime>
#include <array>
#include <vector>

// итоговое задание "Наследование"
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем генерацию значения из диапазона
	int res = max - min + 1;
	return static_cast<int>(rand() * fraction * res + min);
}

class Creature
{
public:
	Creature(std::string name, char symbol, int health, int damage, int gold) :
		_name(name), _symbol(symbol), _health(health),_damage(damage),_gold(gold)
	{}
	const std::string& getName() const { return _name; }
	char getSymbol() const { return _symbol; }
	int getHealth() const { return _health; }
	int getDamage() const { return _damage; }
	int getGold() const { return _gold; }
	void reduceHealth(int hp) { _health -= hp; }
	bool isDead() const { return _health <= 0; }
	void addGold(int g) { _gold += g; }
protected:
	std::string _name;
	char _symbol;
	int _health;
	int _damage;
	int _gold;
};

class Player : public Creature
{
public:
	Player(std::string name) : 
		Creature(name, '@', 20, 1, 0)
	{}
	int getLevel() const { return _level; }
	void levelUp()
	{
		++_level;
		++_damage;
	}
	bool hasWon() const { return _level >= 20; }
private:
	int _level = 1;
};

class Monster : public Creature
{
public:
	enum class Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};
	struct MonsterData
	{
		std::string name = "";
		char symbol = ' ';
		int health = 0;
		int damage = 0;
		int gold = 0;
	};
	static const int max_types = static_cast<int>(Type::MAX_TYPES);
	static std::array<MonsterData, max_types> monsterData;
	Monster(Type type) 
		: Creature( monsterData.at(static_cast<int>(type)).name,
					monsterData.at(static_cast<int>(type)).symbol,
					monsterData.at(static_cast<int>(type)).health,
					monsterData.at(static_cast<int>(type)).damage,
					monsterData.at(static_cast<int>(type)).gold),
		_type(static_cast<Monster::Type>(type))
	{}
	static Monster getRandomMonster();
	
private:
	Type _type;
};

std::array<Monster::MonsterData, Monster::max_types> Monster::monsterData
{ {
	{ "dragon", 'D', 20, 4, 100 },
	{ "orc", 'O', 4, 2, 25 },
	{ "slime", 'S', 1, 1, 10 }
} };

Monster Monster::getRandomMonster()
{
	int mon_type = getRandomNumber(0, Monster::max_types - 1);
	return Monster (static_cast<Type>(mon_type));
}

char get_move()
{
	char move = ' ';
	do
	{
		std::cout << "(R)un or (F)ight: ";
		std::cin >> move;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Input error!\n";
		}
		else
		{
			if (move == 'r' || move == 'f')
			{
				std::cin.ignore(32767,'\n');
				break;
			}
			std::cin.ignore(32767, '\n');
			std::cout << "Input error!\n";
		}		
	} while (true);
	return move;
}

namespace GameParameters
{
	enum GameParameters
	{
		DEAD,
		FLED,
		FIGHT = 'f',
		RUN = 'r'
	};
}

bool attackPlayer(Monster& mon, Player& player)
{
	player.reduceHealth(mon.getDamage());
	std::cout << "The " << mon.getName() << " hit you for " 
		<< mon.getDamage() << " damage.\n";
	return player.isDead();
}

bool attackMonster(Monster& mon, Player& player)
{
	std::cout << "You hit the " << mon.getName() << " for "
		<< player.getDamage() << " damage.\n";
	mon.reduceHealth(player.getDamage());
	return mon.isDead();
}

bool fightMonster(Monster& mon, Player& player)
{
	do
	{
		char pl_move = get_move();
		switch (pl_move)
		{
		case GameParameters::RUN:
			if (getRandomNumber(0, 1))
			{
				std::cout << "You successfully fled.\n";
				return GameParameters::FLED;
			}
			break;
		case GameParameters::FIGHT:
			if (attackMonster(mon, player))
			{
				std::cout << "You killed the " << mon.getName() << ".\n";
				player.levelUp();
				std::cout << "You are now level " << player.getLevel() << ".\n";
				player.addGold(mon.getGold());
				std::cout << "You found " << mon.getGold() << " gold.\n";
				return !player.hasWon();
			}
			break;
		default:
			break;
		}	
	} while (!attackPlayer(mon, player));
	return GameParameters::DEAD;
}

bool game(Player& player)
{	
	bool game_result = true;
	do
	{
		Monster mon = Monster::getRandomMonster();
		std::cout << "You have encountered a " << mon.getName() 
			<< " (" << mon.getSymbol() << ").\n";
		game_result = fightMonster(mon, player);
	} while (game_result);
	return player.hasWon();
}

// итоговое задание "Виртуальные функции"
class Shape
{
public:
	virtual std::ostream& print(std::ostream& out)const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Shape& sh)
	{
		return sh.print(out);
	}
	virtual ~Shape() {}
private:
};

class Point
{
public:
	Point(int x, int y, int z)
		: m_x(x), m_y(y), m_z(z) {}
	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
		return out;
	}
private:
	int m_x = 0;
	int m_y = 0;
	int m_z = 0;
};

class Circle : public Shape
{
public:
	Circle(const Point& p, int rad) : _center(p), _radius(rad) {}
	std::ostream& print(std::ostream& out)const override
	{
		out << "Circle(" << _center << ", radius " << _radius << ")\n";
		return out;
	}
	int getRadius() const { return _radius; }
private:
	int _radius;
	Point _center;
};

class Triangle : public Shape
{
public:
	Triangle(const Point& x, const Point& y, const Point& z) : _x(x),_y(y),_z(z){}
	std::ostream& print(std::ostream& out)const override
	{
		out << "Triangle(" << _x << ", " << _y << ", " << _z << ")\n";
		return out;
	}
private:
	Point _x;
	Point _y;
	Point _z;
};

int getLargestRadius(std::vector<Shape*>& vec)
{
	int rad = 0;
	for (auto const& var : vec)
	{
		Circle* ptr = dynamic_cast<Circle*>(var);
		if (ptr)
		{
			if (ptr->getRadius() > rad)
			{
				rad = ptr->getRadius();
			}
		}	
	}
	return rad;
}

int main()
{
	std::vector<Shape*> v;
	v.push_back(new Circle(Point(1, 2, 3), 7));
	v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
	v.push_back(new Circle(Point(4, 5, 6), 3));
	// Вывод элементов вектора v здесь
	for(auto const& var : v)
	{
		std::cout << *var;
	}
	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // реализуйте эту функцию
	// Удаление элементов вектора v здесь
	for (auto const& element : v)
		delete element;

	/*Circle c(Point(1, 2, 3), 7);
	std::cout << c << '\n';
	Triangle t(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9));
	std::cout << t << '\n';*/

	/*Creature o("orc", 'o', 4, 2, 10);
	o.addGold(5);
	o.reduceHealth(1);
	std::cout << "The " << o.getName() << " has " << o.getHealth() << " health and is carrying " << o.getGold() << " gold.";*/
	/*std::string player_name;
	std::cout << "Enter your name: ";
	std::cin >> player_name;
	Player player(player_name);
	std::cout << "Welcome, "<<player.getName()<<".\n";
	std::cout << "You have "<<player.getHealth()<<" health and are carrying "<<player.getGold()<<" gold.\n";*/
	/*Monster m(static_cast<int>(Monster::Type::ORC));
	std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";*/
	//srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
	//rand(); // сбрасываем первый результат
	//for (int i = 0; i < 10; ++i)
	//{
	//	Monster m = Monster::getRandomMonster();
	//	std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
	//}

	//srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа
	//rand(); // сбрасываем первый результат
	//std::string player_name;
	///*std::cout << "Enter your name: ";
	//std::cin >> player_name;*/
	//Player player("Artem");
	//std::cout << "Welcome, " << player.getName() << ".\n";
	//std::cout << "You have " << player.getHealth() << " health and are carrying " 
	//	<< player.getGold() << " gold.\n";
	//if (game(player))
	//{
	//	std::cout << "You win! ";
	//	std::cout << "You are level " << player.getLevel() << " and with " 
	//		<< player.getGold() << " gold.\n";
	//}
	//else
	//{
	//	std::cout << "You died at level " << player.getLevel() << " and with " 
	//		<< player.getGold() << " gold.\n";	
	//}
	return 0;
}