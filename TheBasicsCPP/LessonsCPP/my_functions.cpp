#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int readNumber()
{
    int a;
    std::cout << "Введите число: " << std::endl;
    std::cin >> a;
    return a;
}

void writeAnswer(int x)
{
    std::cout << "Ответ: " << x << std::endl;
}

char enterOperator(char op) {

    std::cout << "Enter one of the following +, -, *, or /: ";
    std::cin >> op;

    if (op != '+' && op != '-' && op != '*' && op != '/') {

        std::cout << "Entered an incorrect operator!";
        system("cls");
        op = enterOperator(op);
    }
    return op;
}

double calc(double firstNumb, double secondNumb, char op) {

    switch (op)
    {
    case '+':
        return firstNumb + secondNumb;
    case '-':
        return firstNumb - secondNumb;
    case '*':
        return firstNumb * secondNumb;
    case '/':
        return firstNumb / secondNumb;
    default:
        return 0;
        break;
    }
}

double calcHeight(double heighT, int time) {

    constexpr double gravity = 9.8;
    double height;
    height = heighT - (gravity * (pow(time, 2) / 2));
    return height;
}

void showResult(double h, int time) {

    if (h > 0.0)
        std::cout << "At " << time << " seconds, the ball is at height: " << h << " meters" << std::endl;
    else std::cout << "At " << time << " seconds, the ball on the ground." << std::endl;
}