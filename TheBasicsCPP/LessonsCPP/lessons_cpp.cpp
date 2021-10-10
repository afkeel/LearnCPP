#include <iostream>
#include <string>
#include "my_functions.h"
#include <ctime>

using namespace std;

enum class MyMonsters
{
    ORC,
    GOBLIN,
    TROLL,
    SKELETON,
    OGRE,
};

struct Monstr
{
    MyMonsters type;
    int health;
    string name;
};

void printMonster(Monstr mon) {

    string name = "NoName";

    if (mon.type == MyMonsters::ORC) {
        name = "Orc";
    }

    if (mon.type == MyMonsters::GOBLIN) {
        name = "Goblin";
    }

    std::cout << "This " << name << " is named " << mon.name << " and has " << mon.health << " health." << endl;
}

bool cmpNumber(int x, int y)
{
    if (x == y) {
        cout << "Correct! You win!" << endl;
        return true;
    }
    else if (x > y) {
        cout << "Your guess is too high." << endl;
        return false;
    }
    else {
        cout << "Your guess is too low." << endl;
        return false;
    }
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int game(const int a)
{
    int y = getRandomNumber(1, 100);
    int x;
    cout << "Let's play a game. I'm thinking of a number. You have " << a << " tries to guess what it is." << endl;

    for (int i = 1; i <= a; i++)
    {
        cout << "Guess #" << i << ": ";
        cin >> x;

        if (std::cin.fail()) // если предыдущее извлечение было неудачным,    
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы    
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера    
        }
        else cin.ignore(32767, '\n');

        if (cmpNumber(x, y))
        {
            return 1;
        }
    }

    cout << "Sorry, you lose. The correct number was " << y << "." << endl;
    return 0;
}

int main()
{
    /*int a = 5.2;
    setlocale(0, "Ru");
    int first = readNumber();
    int second = readNumber();
    writeAnswer(first + second);
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << std::endl;*/

    /*double firstNumb, secondNumb;
    char operate = 0;
    std::cout << "Enter a double value: ";
    std::cin >> firstNumb;
    std::cout << "Enter a second double value: ";
    std::cin >> secondNumb;
    operate = enterOperator(operate);
    std::cout << firstNumb << operate << secondNumb << "=" << calc(firstNumb, secondNumb, operate) << endl;*/

     /*double hgt;
     int time = 0;
     std::cout << "Enter a height tower: ";
     std::cin >> hgt;
     const double heightTower = hgt;
     double h;
     do
     {
         h = calcHeight(heightTower, time);
         showResult(h, time);
         time++;
     } while (h > 0);*/

     //Monstr goblin = { MyMonsters::GOBLIN, 170, "John"};
     //Monstr orc = { MyMonsters::ORC, 35, "James" };
     //printMonster(goblin);
     //printMonster(orc);

     //int outer = 1;
     //while (outer <= 5)
     //{
     //    int inner = 5;
     //    while (inner >= 1) {
     //        if (inner > outer) {
     //            std::cout << "  ";
     //            --inner;
     //        } else std::cout << inner-- << " ";
     //    }
     //    // Вставляем символ новой строки в конце каждого рядка
     //    std::cout << "\n";
     //    ++outer;
     //    
     //}

     rand();
     const int attempt = 7;
     game(attempt);
     do
     {
         char start;
         cout << "Would you like to play again (y/n)?";
         cin >> start;
         if (start == 'y') {

             cin.ignore(32767, '\n');
             game(attempt);
            
         }
         else if (start == 'n') {

             cin.ignore(32767, '\n');
             cout << "Thank you for playing." << endl;
             break;
         }
         else {
             if (std::cin.fail()) // если предыдущее извлечение было неудачным,
             {
                 std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
                 std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
             }
             else cin.ignore(32767, '\n');
         }

     } while (true);

    return 0;
}