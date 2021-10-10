#include <iostream>
#include "Header.h"

template <class T>
class Pair1
{
public:
	Pair1(const T& f, const T& s):_first(f),_second(s)
	{}
	T& first() { return _first; }
	const T& first() const { return _first; }
	T& second() { return _second; }
	const T& second() const { return _second; }
private:
	T _first;
	T _second;
};

template <class T1, class T2>
class Pair
{
public:
	Pair(const T1& f, const T2& s) :_first(f), _second(s)
	{}
	T1& first() { return _first; }
	const T1& first() const { return _first; }
	T2& second() { return _second; }
	const T2& second() const { return _second; }
private:
	T1 _first;
	T2 _second;
};

template <class T1, class T2>
class Pa
{
public:
	Pa(const T1& name, const T2& len) :_name(name), _len(len)
	{}
	T1& first() { return _name; }
	const T1 first() const { return _name; }
	T2& second() { return _len; }
	const T2& second() const { return _len; }
private:
	T1 _name;
	T2 _len;
};

template<class S>
class StringValuePair : public Pa<std::string, S>
{
public:
	StringValuePair(const std::string& s, const S& l):Pa<std::string, S>(s, l){}
};

// Отдельная функция вычисления квадратного корня числа
double mySqrt(double a)
{
	// Если пользователь ввел отрицательное число,
	if (a < 0.0)
		throw "Can not take sqrt of negative number"; // то выбрасывается исключение типа const char*

	return sqrt(a);
}

class Member
{
public:
	int* _m;
	Member()
	{
		_m = new int[10];
		std::cerr << "Member allocated some resources\n";
	}
	~Member()
	{
		delete[] _m;
		std::cerr << "Member cleaned up\n";
	}
};

class A
{	
protected:
	//int* _data;
	Member _member;
public:
	A(int x)
	{
		//_data = new int[5];
		if (x <= 0)
			//delete[] _data;
			throw 1;
	}
	~A() { /*delete[] _data;*/ }
};

class B : public A
{
public:
	B(int x) try : A(x)
	{
	}
	catch (...)
	{
		std::cerr << "Construction of A failed\n";
	}
	~B(){}
};

class Fraction
{
public:
	Fraction(int num, int den) : _num(num), _den(den)
	{
		if (den == 0)
		{			
			throw std::runtime_error("Invalid denominator");
		}
	}
	friend std::ostream& operator<< (std::ostream& out, const Fraction& f)
	{
		out << f._num << "/" << f._den;
		return out;
	}
	~Fraction(){}

private:
	int _num;
	int _den;
};

int main()
{
	groop<int*>gp;
	int a = 5;
	int* pa = &a;
	gp.push_back(pa);

	/*int numerator, denominator;
	std::cout << "Enter the numerator: ";
	std::cin >> numerator;
	std::cout << "Enter the denominator: ";
	std::cin >> denominator;
	try
	{
		Fraction fr(numerator, denominator);
		std::cout << fr << std::endl;
	}
	catch (const std::exception& err)
	{
		std::cout << "Your fraction has an: "<< err.what() <<".\n";
	}*/

	/*try
	{
		B b(0);
	}
	catch (...)
	{
		std::cout << "Oops!\n";
	}*/

	//std::cout << "Enter a number: ";
	//double a;
	//std::cin >> a;
	//// Здесь нет никакого обработчика исключений!
	//try
	//{
	//	std::cout << "The sqrt of " << a << " is " << mySqrt(a) << '\n';
	//}
	//catch (...) // обработчик catch-all
	//{
	//	std::cout << "We caught an exception of an undetermined type!\n";
	//}

	/*StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';*/

	/*Pair<int, double> p1(6, 7.8);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
	const Pair<double, int> p2(3.4, 5);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';*/

	/*Pair1<int> p1(6, 9);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
	const Pair1<double> p2(3.4, 7.8);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';*/

    return 0;
}