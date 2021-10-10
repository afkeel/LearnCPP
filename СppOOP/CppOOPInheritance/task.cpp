#include <iostream> 
#include <string>
#include <vector>
#include <cassert>
#include <array>

class Worker
{
private:
    std::string m_name;
public:
    Worker(std::string name)
        : m_name(name)
    {
    }
    std::string getName() const { return m_name; }
};

class Department
{
private:
    std::vector<Worker*> m_group;
public:
    Department()
    {
    }
    void add(Worker* worker)
    {
        m_group.push_back(worker);
    }
    friend std::ostream& operator<<(std::ostream& out, const Department& d)
    {
        out << "Department: ";
        for (auto& var : d.m_group)
        {
            out << var->getName() << " ";
        }
        out << "\n";
        return out;
    }
};

class ArrayInt
{
private:
    int m_length;
    int* m_data;
public:
    ArrayInt() :
        m_length(0), m_data(nullptr)
    {
    }
    ArrayInt(int length) :
        m_length(length)
    {
        m_data = new int[length];
    }
    ArrayInt(const std::initializer_list<int>& list) : // позвол€ем инициализацию ArrayInt через список инициализации
        ArrayInt(list.size()) // используем концепцию делегировани€ конструкторов дл€ создани€ начального массива, в который будет выполн€тьс€ копирование элементов
    {
        // »нициализаци€ нашего начального массива значени€ми из списка инициализации
        int count = 0;
        for (auto& element : list)
        {
            m_data[count] = element;
            ++count;
        }
    }
    ~ArrayInt()
    {
        delete[] m_data;
        // Ќам не нужно здесь присваивать значение null дл€ m_data или выполн€ть m_length = 0, так как объект будет уничтожен сразу же после выполнени€ этой функции
    }
    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
    ArrayInt& operator= (const std::initializer_list<int>& list)
    {
        if (list.size() != static_cast<size_t>(m_length))
        {
            delete[] m_data;
            m_length = list.size();
            m_data = new int[m_length];
        }       
        int count = 0;
        for (auto& element : list)
        {
            m_data[count++] = element;
        }
        return *this;
    }
    int getLength() { return m_length; }
};

class Fruit
{
private:
    std::string _name;
    std::string _color;
public:
    Fruit(std::string name, std::string color)
        : _name(name), _color(color)
    {
    }
    std::string getName() const { return _name; }
    std::string getColor() const { return _color; }
    friend std::ostream& operator<< (std::ostream& out, const Fruit& fruit)
    {
        out << fruit.getName() << ", " << fruit.getColor();
        return out;
    }
};

class Apple : public Fruit
{
private:
    double _fiber = 0.0;
public:
    Apple(std::string name, std::string color, double fiber) : Fruit(name, color),
    _fiber(fiber)
    {
    }
    Apple() : Fruit("apple", "green")
    {
    }
    Apple(std::string color) : Fruit("apple", color)
    {
    }
    double getFiber() const { return _fiber; }
    friend std::ostream& operator<< (std::ostream& out, const Apple& apple)
    {
        out << "Apple("  << static_cast<Fruit>(apple) <<  ", " << apple.getFiber() << ")\n";
        return out;
    }
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple("GrannySmith apple", "green", 0.0)
    {
    }
};

class Banana : public Fruit
{
public:
    Banana(std::string name = "banana", std::string color = "yellow") : Fruit(name, color)
    {
    }
    friend std::ostream& operator<< (std::ostream& out, const Banana& banana)
    {
        out << "Banana(" << static_cast<Fruit>(banana) << ")\n";
        return out;
    }
};

int main()
{
    Apple a1("red");
    Apple a2;
    Banana b1;
    GrannySmith c;
    std::cout << "My " << a1.getName() << " is " << a1.getColor() << ".\n";
    std::cout << "My " << a2.getName() << " is " << a2.getColor() << ".\n";
    std::cout << "My " << b1.getName() << " is " << b1.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
    const Apple a("Red delicious", "red", 7.3);
    std::cout << a;
    const Banana b("Cavendish", "yellow");
    std::cout << b;

    //// —оздаем –аботников вне области видимости класса Department
    //Worker* w1 = new Worker("Anton");
    //Worker* w2 = new Worker("Ivan");
    //Worker* w3 = new Worker("Max");
    //{
    //    // —оздаем ќтдел и передаем –аботников в качестве параметров конструктора
    //    Department department; // содаем пустой ќтдел
    //    department.add(w1);
    //    department.add(w2);
    //    department.add(w3);
    //    std::cout << department;
    //} // department выходит из области видимости и уничтожаетс€ здесь
    //std::cout << w1->getName() << " still exists!\n";
    //std::cout << w2->getName() << " still exists!\n";
    //std::cout << w3->getName() << " still exists!\n";
    //delete w1;
    //delete w2;
    //delete w3;

    //ArrayInt array{ 7, 6, 5, 4, 3, 2, 1 }; // список инициализации
    //for (int count = 0; count < array.getLength(); ++count)
    //    std::cout << array[count] << ' ';

    //std::cout << '\n';

    //array = { 1, 4, 9, 12, 15, 17, 19, 21};

    //for (int count = 0; count < array.getLength(); ++count)
    //    std::cout << array[count] << ' ';

    return 0;
}

