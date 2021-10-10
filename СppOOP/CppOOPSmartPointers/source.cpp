#include <iostream>
#include <vector>

template<class T>
class Auto_ptr5
{
	T* m_ptr;
public:
	Auto_ptr5(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}
	~Auto_ptr5()
	{
		delete m_ptr;
	}
	//  онструктор копировани€ - запрещаем любое копирование!
	Auto_ptr5(const Auto_ptr5& x) = delete;
	//  онструктор перемещени€, который передает право собственности на x.m_ptr в m_ptr
	Auto_ptr5(Auto_ptr5&& x) noexcept
		: m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr;
	}
	// ќператор присваивани€ копированием - запрещаем любое копирование!
	Auto_ptr5& operator=(const Auto_ptr5& x) = delete;
	// ќператор присваивани€ перемещением, который передает право собственности на x.m_ptr в m_ptr
	Auto_ptr5& operator=(Auto_ptr5&& x) noexcept
	{
		// ѕроверка на самоприсваивание
		if (&x == this)
			return *this;
		// ”дал€ем всЄ, что может хранить указатель до этого момента
		delete m_ptr;
		// ѕередаем право собственности на x.m_ptr в m_ptr
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr;

		return *this;
	}
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

class Item
{
	int m_x;
public:
	Item(int x = 2) : m_x(x) { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
	int getData() const{return m_x;}
	friend std::ostream& operator<<(std::ostream& out, const Item& item)
	{
		out << "I am an Item!\n";
		return out;
	}
};

Auto_ptr5<Item> generateItem()
{
	Auto_ptr5<Item> item(new Item);
	return item; // это возвращаемое значение приведет к вызову конструктора копировани€
}

template<class T>
void myswap(T& x, T& y)
{
	T tmp{ std::move(x) }; // вызывает конструктор перемещени€
	x = std::move(y); // вызывает оператор присваивани€ перемещением
	y = std::move(tmp); // вызывает оператор присваивани€ перемещением
}

template<class T>
T&& myforward(typename std::remove_reference<T>::type& t) noexcept 
{
	return static_cast<T&&>(t);
}

struct Base 
{
std::vector<int> _v;
	Base(std::vector<int>& value1)
		:_v(value1){};
	Base(std::vector<int>&& value1)
		:_v(std::move(value1)) {};
};

template <typename T>
Base wrapper(T&& e1)
{
	//return Base(e1);
	return Base(std::forward<T>(e1));
}

std::unique_ptr<Item> createItem()
{
	return std::make_unique<Item>();
}

class Fraction
{
private:
	int m_numerator = 0;
	int m_denominator = 1;

public:
	Fraction(int numerator = 0, int denominator = 1) :
		m_numerator(numerator), m_denominator(denominator)
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
	{
		out << f1.m_numerator << "/" << f1.m_denominator;
		return out;
	}
};

void printFraction(const Fraction* const ptr)
{
	if (ptr)
		std::cout << *ptr;
}

class ItemW
{
public:
	std::weak_ptr<ItemW> m_ptr; // изначально пустой
	ItemW() { std::cout << "Item acquired\n"; }
	~ItemW() { std::cout << "Item destroyed\n"; }
};

class MoveClass
{
private:
	int* m_resource{};
public:
	MoveClass() = default;
	MoveClass(int resource)
		: m_resource{ new int{ resource } }
	{}
	//  онструктор копировани€
	MoveClass(const MoveClass& that)
	{
		// √лубокое копирование
		if (that.m_resource != nullptr)
		{
			m_resource = new int{ *that.m_resource };
		}
	}
	//  онструктор перемещени€
	MoveClass(MoveClass&& that) noexcept
		: m_resource{ that.m_resource }
	{
		that.m_resource = nullptr;
	}
	~MoveClass()
	{
		std::cout << "destroying " << *this << '\n';
		delete m_resource;
	}
	friend std::ostream& operator<<(std::ostream& out, const MoveClass& moveClass)
	{
		out << "MoveClass(";
		if (moveClass.m_resource == nullptr)
		{
			out << "empty";
		}
		else
		{
			out << *moveClass.m_resource;
		}
		out << ')';
		return out;
	}
};

class CopyClass
{
public:
	bool m_throw{};
	CopyClass() = default;
	//  онструктор копировани€ выбрасывает исключение при выполнении копировани€ из объекта CopyClass, где его переменна€ m_throw имеет значение 'true'
	/*CopyClass(const CopyClass& that)
		: m_throw{ that.m_throw }
	{
		if (m_throw)
		{
			throw std::runtime_error{ "abort!" };
		}
	}*/
};

template <class T>
const T& my_move_if_noexcept(T& _Arg) noexcept { // forward _Arg as movable, sometimes
	return  std::move(_Arg);
}

int main()
{
	bool a = std::is_nothrow_constructible<MoveClass>::value;
	bool b = __is_nothrow_constructible(MoveClass, MoveClass);

	// ћы можем создать объект std::pair без каких-либо проблем
	std::pair my_pair{ MoveClass{ 13 }, CopyClass{} };
	std::cout << "my_pair.first: " << my_pair.first << '\n';
	// Ќо проблемы начинают по€вл€тьс€, когда мы пытаемс€ переместить объекты одной пары в другую пару
	try
	{
		my_pair.second.m_throw = true; // чтобы спровоцировать генерацию исключени€ конструктором копировани€
		// —ледующа€ строка выбросит исключение
		//std::pair moved_pair{ std::move(my_pair) }; // мы закомментируем эту строку чуть позже
		std::pair moved_pair{std::move_if_noexcept(my_pair)}; // мы раскомментируем эту строку чуть позже
		std::cout << "moved pair exists\n"; // никогда не выведетс€
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error found: " << ex.what() << '\n';
	}
	std::cout << "my_pair.first: " << my_pair.first << '\n';

	/*auto ptr1 = std::make_shared<ItemW>();
	ptr1->m_ptr = ptr1;*/

	/*Item* item = new Item;
	std::shared_ptr<Item> ptr1(item);
	{
		std::shared_ptr<Item> ptr2(ptr1);
	}
	std::make_shared<Item>();*/

	////Fraction* ptr = new Fraction(7, 9);
	//auto ptr{ std::make_unique<Fraction>(7, 9) };
	//printFraction(ptr.get());
	////delete ptr;

	/*auto ptr{ createItem() };*/

	/*std::unique_ptr<Fraction> f1 = std::make_unique<Fraction>(7, 9);
	std::cout << *f1 << '\n';
	auto f2 = std::make_unique<Fraction[]>(5);
	std::cout << f2[0] << '\n';

	std::vector<int> v{ 32, 53 };
	wrapper(v);
	wrapper(std::vector<int>{23, 35});*/

	//int b = 10;
	//int& bb = b;
	//int&& a = 10;
	//myforward<int>(a);
	//myforward<int&>(bb);
	//std::forward<int>(10);
	////std::forward<int&>(10); // bad forward call

	//std::unique_ptr<Item> item(new Item);
	//if (item) // используем не€вное преобразование item в тип bool, чтобы убедитьс€, что item владеет Item-ом
	//	std::cout << *item; // выводим Item, которым владеет item

	//std::string x{ "Anton" };
	//std::string y{ "Max" };
	//myswap(x, y);

	/*Auto_ptr5<Item> mainItem;
	mainItem = generateItem();*/

	return 0;
}