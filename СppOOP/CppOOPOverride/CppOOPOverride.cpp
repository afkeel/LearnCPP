#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <array>

class Number
{
private:
    int m_number;
public:
    Number(int number = 0)
        : m_number(number)
    {
    }
    Number(const Number& oth)
    {
        m_number = oth.m_number;
    }
    Number& operator++(); // версия префикс
    Number& operator--(); // версия префикс
    Number operator++(int); // версия постфикс
    Number operator--(int); // версия постфикс
    friend std::ostream& operator<< (std::ostream& out, const Number& n);
    friend Number operator+ (Number& n1, const Number& n2);
};

Number& Number::operator++()
{
    // Если значением переменной m_number является 8, то выполняем сброс значения m_number на 0
    if (m_number == 8)
        m_number = 0;
    // В противном случае, просто увеличиваем m_number на единицу
    else
        ++m_number;

    return *this;
}

Number& Number::operator--()
{
    // Если значением переменной m_number является 0, то присваиваем m_number значение 8
    if (m_number == 0)
        m_number = 8;
    // В противном случае, просто уменьшаем m_number на единицу
    else
        --m_number;

    return *this;
}

Number Number::operator++(int)
{
    // Создаем временный объект класса Number с текущим значением переменной m_number
    Number temp(m_number);

    // Используем оператор инкремента версии префикс для реализации перегрузки оператора инкремента версии постфикс
    ++(*this); // реализация перегрузки

    // Возвращаем временный объект
    return temp;
}

Number Number::operator--(int)
{
    // Создаем временный объект класса Number с текущим значением переменной m_number
    Number temp(m_number);

    // Используем оператор декремента версии префикс для реализации перегрузки оператора декремента версии постфикс
    --(*this); // реализация перегрузки

    // Возвращаем временный объект
    return temp;
}

Number operator+(Number& n1, const Number& n2)
{
    Number temp;
    temp.m_number = n1.m_number + n2.m_number;
    return temp;
}

std::ostream& operator<< (std::ostream& out, const Number& n)
{
    out << n.m_number;
    return out;
}

struct StudentGrade
{
    std::string name;
    char score = ' ';
};

class GradeMap
{
public:
    GradeMap(){};
    char& operator[](const std::string n)
    {
        for (auto& sg : m_map)
        {
            if (sg.name == n)
            {
                return sg.score;
            }
        }
        m_map.push_back({n});
        return m_map.back().score;
    }
    void sort_grade_map()
    {
        sort(m_map.begin(), m_map.end(), [](StudentGrade& a, StudentGrade& b) {
            return a.name < b.name; });
    }
private:
    std::vector<StudentGrade> m_map;
};

class Mystring
{
public:
    Mystring(const std::string str = ""):m_str(str) {};
    std::string operator()(int a, int b)
    {
        std::string temp_str = "";
        for (int i = 0; i < b; i++)
        {
            temp_str += m_str[a++];
        }       
        return temp_str;
    }
private:
    std::string m_str;
};
 
class Drob
{
private:
    int m_numerator;
    int m_denominator;

public:
    // Конструктор по умолчанию
    Drob(int numerator = 0, int denominator = 1) :
        m_numerator(numerator), m_denominator(denominator)
    {
        assert(denominator != 0);
    }

    // Конструктор копирования
    Drob(const Drob& copy) :
        m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
    {
        // Нет необходимости выполнять проверку denominator здесь, так как она осуществляется в конструкторе по умолчанию
        std::cout << "Copy constructor worked here!\n"; // просто чтобы показать, что это работает
    }
    friend bool operator==(const Drob& left, const Drob& right)
    {
        return left.m_denominator == right.m_denominator && left.m_numerator == right.m_numerator;
    }
    friend std::ostream& operator<<(std::ostream& out, const Drob& d1);
    int getNumerator() { return m_numerator; }
    void setNumerator(int numerator) { m_numerator = numerator; }
};

std::ostream& operator<<(std::ostream& out, const Drob& d1)
{
    out << d1.m_numerator << "/" << d1.m_denominator;
    return out;
}

Drob makeNegative(Drob d = 10) // правильно было бы здесь использовать константную ссылку
{
    Drob* pd = &d;
    std::cout << pd;
    d.setNumerator(-d.getNumerator());
    return d;
}

class SomeString
{
private:
    std::string m_string;
public:
    SomeString(char) = delete;
    explicit SomeString(int a) // выделяем строку размером a
    {
        m_string.resize(a);
    }
    SomeString(const char* string) // выделяем строку для хранения значения типа string
    {
        m_string = string;
    }
    friend std::ostream& operator<<(std::ostream& out, const SomeString& s);
};

std::ostream& operator<<(std::ostream& out, const SomeString& s)
{
    out << s.m_string;
    return out;
}

int main()
{
    /*std::array< std::array<int, 5>,5> arr;
    arr[2][4] = 4;*/

    /*Number a(1);
    Number c = ++a;
    Number b = a++;*/

    /*Number a(2);
    Number b(3);
    Number c = a + b;*/

    /*GradeMap grades;
    grades["John"] = 'A';
    grades["Martin"] = 'B';
    grades["Art"] = 'A';
    grades["Zert"] = 'B';
    grades["Fsde"] = 'A';
    grades["Uass"] = 'B';
    grades.sort_grade_map();
    std::cout << "John has a grade of " << grades["John"] << '\n';
    std::cout << "Martin has a grade of " << grades["Martin"] << '\n';*/

    /*Mystring string("Hello, world!");
    std::cout << string(7, 6);*/

    //Drob sixSeven(6, 7);
    //Drob* p = &sixSeven;
    //std::cout << makeNegative(sixSeven);
    //std::cout << makeNegative();
    
    //SomeString mystring = 10;
    //SomeString mystring(5);
    //mystring = "asfaf"; // выполняется копирующая инициализация
    //SomeString str = 'a';
    //std::cout << mystring;

	return 0;
}