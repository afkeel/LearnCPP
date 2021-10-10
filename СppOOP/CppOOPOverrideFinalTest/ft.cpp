#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class Average
{
public:
	Average& operator+= (int a);
	friend std::ostream& operator<< (std::ostream& out, const Average& avg);

private:
	int32_t m_sum = 0;
	int8_t m_count = 0;
};

Average& Average::operator+= (int a)
{
	++m_count;
	m_sum += a;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Average& avg)
{
	out << static_cast<double>(avg.m_sum) / avg.m_count;
	return out;
}

class IntArray
{
public:
	IntArray(size_t l = 0):m_lenght(l)
	{	
		size_t size = static_cast<size_t>(-1) / sizeof(size_t);
		assert(m_lenght < size);
		assert(m_lenght > 0 && "IntArray length should be a positive integer");
		m_arr = new int[m_lenght] {0};
	}
	IntArray(const IntArray& arr)
	{
		m_lenght = arr.m_lenght;
		m_arr = new int[m_lenght];
		for (size_t i = 0; i < arr.m_lenght; i++)
		{
			m_arr[i] = arr.m_arr[i];
		}
	}
	~IntArray()
	{
		delete[] m_arr;
	}
	IntArray& operator= (const IntArray& arr)
	{
		if (this == &arr)
		{
			return *this;
		}
		delete[] m_arr;
		m_lenght = arr.m_lenght;
		m_arr = new int[m_lenght];		
		for (size_t i = 0; i < arr.m_lenght; i++)
		{
			m_arr[i] = arr.m_arr[i];
		}
		return *this;
	}
	int& operator[] (const size_t index)
	{
		assert(index >= 0 && index < m_lenght);		
		return m_arr[index];
	}
	const int& operator[] (const size_t index) const
	{
		assert(index >= 0 && index <= m_lenght);
		return m_arr[index];
	}
	friend std::ostream& operator<< (std::ostream& out, const IntArray& mas)
	{
		for (size_t i = 0; i < mas.m_lenght; i++)
		{
			out << mas.m_arr[i] << " ";
		}
		return out;
	}
private:
	int* m_arr;
	size_t m_lenght;
};

IntArray fillArray()
{
	IntArray a(6);
	
	a[0] = 6;
	a[1] = 7;
	a[2] = 3;
	a[3] = 4;
	a[4] = 5;
	a[5] = 8;

	return a;
}

class FixedPoint
{
public:
	FixedPoint(int16_t integer, int8_t fraction);
	FixedPoint(double numb);
	~FixedPoint();
	operator double() const;
	FixedPoint operator- () const;
	friend std::ostream& operator<<(std::ostream& out, const FixedPoint& ob);
	friend std::istream& operator>>(std::istream& in, FixedPoint& ob);
	friend FixedPoint operator+(const FixedPoint& l, const FixedPoint& r);
	friend bool operator==(const FixedPoint& l, const FixedPoint& r);

private:
	int16_t m_integer;
	int8_t m_fraction;
};

FixedPoint::FixedPoint(int16_t integer = 0, int8_t fraction = 0)
{
	assert(fraction > -100 && fraction < 100);
	m_integer = integer;
	m_fraction = fraction;
}

FixedPoint::FixedPoint(double numb)
{
	int16_t a = static_cast<int16_t>(numb);
	int8_t b = static_cast<int8_t>(round((numb - a) * 100));
	if ( b > -100 && b < 100)
	{
		m_integer = a;
		m_fraction = b;		
	}
	else
	{
		m_integer = a + b/100;
		m_fraction = 0;
	}
}

FixedPoint::~FixedPoint()
{
}

FixedPoint::operator double() const
{
	double numb = abs(m_integer) + static_cast<double>(abs(m_fraction)) / 100;
	if (m_integer < 0 || m_fraction < 0)
	{
		numb = -numb;
	}
	return numb;
}

std::ostream& operator<<(std::ostream& out, const FixedPoint& ob)
{	
	out << static_cast<double>(ob);
	return out;
}

std::istream& operator>>(std::istream& in, FixedPoint& ob)
{
	double n;
	in >> n;
	ob = n;
	return in;
}

FixedPoint operator+(const FixedPoint& l, const FixedPoint& r)
{
	return FixedPoint(static_cast<double>(l) + static_cast<double>(r));
}

bool operator==(const FixedPoint& l, const FixedPoint& r)
{
	return static_cast<double>(l) == static_cast<double>(r);
}

FixedPoint FixedPoint::operator-() const
{
	return FixedPoint(-m_integer, -m_fraction);
}

void SomeTest()
{
	std::cout << std::boolalpha;
	std::cout << (FixedPoint(0.75) + FixedPoint(1.23) == FixedPoint(1.98)) << '\n'; // оба значения положительные, никакого переполнения
	std::cout << (FixedPoint(0.75) + FixedPoint(1.50) == FixedPoint(2.25)) << '\n'; // оба значения положительные, переполнение
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.23) == FixedPoint(-1.98)) << '\n'; // оба значения отрицательные, никакого переполнения
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.50) == FixedPoint(-2.25)) << '\n'; // оба значения отрицательные, переполнение
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.23) == FixedPoint(-0.48)) << '\n'; // второе значение отрицательное, никакого переполнения
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.50) == FixedPoint(-0.75)) << '\n'; // второе значение отрицательное, возможно переполнение
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.23) == FixedPoint(0.48)) << '\n'; // первое значение отрицательное, никакого переполнения
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.50) == FixedPoint(0.75)) << '\n'; // первое значение отрицательное, возможно переполнение
}

int main()
{
	//Average avg;
	//avg += 5;
	//std::cout << avg << '\n'; // 5 / 1 = 5
	//avg += 9;
	//std::cout << avg << '\n'; // (5 + 9) / 2 = 7
	//avg += 19;
	//std::cout << avg << '\n'; // (5 + 9 + 19) / 3 = 11
	//avg += -9;
	//std::cout << avg << '\n'; // (5 + 9 + 19 - 9) / 4 = 6
	//(avg += 7) += 11; // выполнение цепочки операций
	//std::cout << avg << '\n'; // (5 + 9 + 19 - 9 + 7 + 11) / 6 = 7

	//Average copy = avg;
	//std::cout << copy << '\n';
	
	IntArray a = fillArray();
	std::cout << a << '\n';

	IntArray b(1);
	a = a;
	b = a;

	std::cout << b << '\n';

	//FixedPoint a(37, 58);
	//std::cout << a << '\n';
	//FixedPoint b(-3, 9);
	//std::cout << b << '\n';
	//FixedPoint c(4, -7);
	//std::cout << c << '\n';
	//FixedPoint d(-5, -7);
	//std::cout << d << '\n';
	//FixedPoint e(0, -3);
	//std::cout << e << '\n';
	//std::cout << static_cast<double>(e) << '\n';

	//FixedPoint a(0.03);
	//std::cout << a << '\n';
	//FixedPoint b(-0.03);
	//std::cout << b << '\n';
	//FixedPoint c(4.01); // сохранится, как 4.0099999..., поэтому нам нужно это всё округлить
	//std::cout << c << '\n';
	//FixedPoint d(-4.01); // сохранится, как -4.0099999..., поэтому нам нужно это всё округлить
	//std::cout << d << '\n';

	//SomeTest();
	//FixedPoint a(-0.9999);
	//std::cout << a << '\n';
	//std::cout << -a << '\n';
	//std::cout << "Enter a number: "; // введите 5.678
	//std::cin >> a;
	//std::cout << "You entered: " << a << '\n';

	return 0;
}
