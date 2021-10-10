#include <iostream>
#include <cmath>
#include "point3D.h"
#include "vector3D.h"
#include <time.h>
#include <chrono>
#include <algorithm>
#include <array>
#include <vector>

//class Point
//{
//public:
//	Point(double a = 0.0, double b = 0.0);
//	~Point();
//	void print() const;
//	double distanceTo(const Point& p) const;
//	friend double distanceFrom(const Point& p1, const Point& p2);
//
//private:
//	double m_a;
//	double m_b;
//};
//
//Point::Point(double a, double b) : m_a(a), m_b(b)
//{
//}
//
//Point::~Point()
//{
//}
//
//void  Point::print() const
//{
//	std::cout << "Point(" << m_a << ", " << m_b << ")\n";
//}
//
//double Point::distanceTo(const Point& p) const
//{
//	return sqrt(pow((m_a - p.m_a), 2) + pow((m_b - p.m_b), 2));
//}
//
//double distanceFrom(const Point& p1, const Point& p2)
//{
//	return sqrt(pow((p1.m_a - p2.m_a), 2) + pow((p1.m_b - p2.m_b), 2));
//}

class Monster
{
public:
	enum MonsterType
	{
		DRAGON, 
		GOBLIN, 
		OGRE, 
		ORC, 
		SKELETON, 
		TROLL, 
		VAMPIRE,
		ZOMBIE,
		MAX_MONSTER_TYPES
	};
	Monster(MonsterType type, std::string name, int health): m_type(type), m_name(name) , m_health(health){}
	std::string getTypeString() const
	{
		switch (m_type)
		{
		case DRAGON:
			return "dragon";
			break;
		case GOBLIN:
			return "goblin";
			break;
		case OGRE:
			return "ogre";
			break;
		case ORC:
			return "orc";
			break;
		case SKELETON:
			return "skeleton";
			break;
		case TROLL:
			return "troll";
			break;
		case VAMPIRE:
			return "vampire";
			break;
		case ZOMBIE:
			return "zombie";
			break;
		case MAX_MONSTER_TYPES:
		default:
			return "ERROR TYPE!";
			break;
		}
	}
	void print() const
	{
		std::cout << m_name <<" is the "<< getTypeString() << " that has "<< m_health << " health points.\n";
	}
private:
	MonsterType m_type;
	std::string m_name;
	int m_health;
};

class MonsterGenerator
{
public:
	
	static int getRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); // используем static, так как это значение нужно вычислить единожды
		// Равномерно распределяем вычисление значения из нашего диапазона
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}
	static Monster generateMonster()
	{
		static std::string s_names[6] { "Leo", "Mike", "Don", "Raf", "NoName", "Jack" };
		return Monster(static_cast<Monster::MonsterType>(getRandomNumber(0, Monster::MAX_MONSTER_TYPES - 1)), s_names[getRandomNumber(0, 5)], getRandomNumber(1, 100));
	}
};

class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;
	std::chrono::time_point<clock_t> m_beg;
public:
	Timer() : m_beg(clock_t::now())
	{
	}
	void reset()
	{
		m_beg = clock_t::now();
	}
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

const int g_arrayElements = 10000;
void sortArray(std::array<int, g_arrayElements>& array)
{
	// Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
	for (int startIndex = 0; startIndex < g_arrayElements - 1; ++startIndex)
	{
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
		// Начнем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		int smallestIndex = startIndex;
		// Затем ищем элемент меньше нашего smallestIndex в оставшейся части массива
		for (int currentIndex = startIndex + 1; currentIndex < g_arrayElements; ++currentIndex)
		{
			// Если нашли элемент, который меньше нашего наименьшего элемента,
			if (array[currentIndex] < array[smallestIndex])
				// то записываем/запоминаем его
				smallestIndex = currentIndex;
		}
		// smallestIndex теперь наименьший элемент в оставшейся части массива.
		// Меняем местами наше стартовое наименьшее значение с тем, которое мы обнаружили
		std::swap(array[startIndex], array[smallestIndex]);
	}
}

class Employee
{
private:
	int m_id;
	std::string m_name;
public:
	Employee(int id = 0, const std::string& name = "") :
		m_id(id), m_name(name)
	{
		Employee::m_id = 5;
	}
	// Используем делегирующие конструкторы для сокращения дублированного кода
	Employee(const std::string &name) : Employee(0, name){}
};

template <int  N>
class A
{
private:
	int* _data;
public:
	A() 
	{
		static int arr[N]{0};
		for (size_t i = 0; i < N; i++)
		{
			arr[i] = i;
		}
		_data = arr;
	}
};

class Something
{
public:
	class _nested // определяем вложенный класс с именем _nested
	{
	public:
		_nested() // конструктор _nested() инициализирует нашу статическую переменную-член
		{
			s_mychars.push_back('o');
			s_mychars.push_back('a');
			s_mychars.push_back('u');
			s_mychars.push_back('i');
			s_mychars.push_back('e');
		}
		int get() { return 1; }
	};

	// Статический метод для вывода s_mychars
	static void getSomething() {
		for (auto const& element : s_mychars)
			std::cout << element << ' ';
	}
private:
	static std::vector<char> s_mychars;
	static _nested s_initializer;
};

std::vector<char> Something::s_mychars;
Something::_nested Something::s_initializer;

int main()
{
	/*Something::getSomething();*/

	/*A<3> a;
	A<3> b = a;*/

	//Employee a;

	/*std::array<int, g_arrayElements> array;
	for (int i = 0; i < g_arrayElements; ++i)
		array[i] = g_arrayElements - i;
	Timer t;
	sortArray(array);
	std::cout << "Time taken: " << t.elapsed() << '\n';*/

	//srand(static_cast<unsigned int>(time(0))); // используем системные часы в качестве стартового значения
	//rand(); // пользователям Visual Studio: делаем сброс первого случайного числа

	//Monster m = MonsterGenerator::generateMonster();
	//m.print();
	//Monster s = MonsterGenerator::generateMonster();
	//s.print();

	/*Point3D p(3.0, 4.0, 5.0);
	Vector3D v(3.0, 3.0, -2.0);

	p.print();
	p.moveByVector(v);
	p.print();*/

	/*Point first;
	Point second(2.0, 5.0);
	first.print();
	second.print();
	std::cout << "Distance between two points: " << distanceFrom(first, second) << '\n';*/

	return 0;
}