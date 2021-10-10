#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <array>

using namespace std;

int getRandomInt(int min, int max)
{
    static mt19937 mt{ random_device{}() };
    return uniform_int_distribution{ min, max } (mt);
}

int binarySearchMy(int* array, int target, int min, int max)
{
    int mid = 0;
    while (array[mid] != target)
    {
        mid = (max + min) / 2;
        if (min != max)
        {
            if (array[mid] > target)
            {
                max = mid - 1;
            }
            else min = mid + 1;
        }
        else break;
    }

    return mid;
}

int binarySearch(int* array, int target, int min, int max)
{
    while (min <= max)
    {
        // Итеративная реализация
        int midpoint = min + ((max - min) / 2); // такой способ вычисления середины массива избегает вероятность возникновения переполнения

        if (array[midpoint] > target)
        {
            // Если array[midpoint] > target, то тогда понимаем, что искомое число не находится в правой половине массива.
            // Мы можем использовать midpoint - 1 в качестве индекса максимальной границы, так как в следующей итерации этот индекс вычислять не нужно
            max = midpoint - 1;
        }
        else if (array[midpoint] < target)
        {
            // Если array[midpoint] < target, то тогда понимаем, что искомое число не находится в левой половине массива.
            // Мы можем использовать midpoint + 1 в качестве индекса минимальной границы, так как в следующей итерации этот индекс вычислять не нужно
            min = midpoint + 1;
        }
        else
            return midpoint;
    }

    return -1;
}

int binarySearchRecMy(int* array, int target, int min, int max)
{
    int mid = 0;
    if (array[max] == target)
    {
        return max;
    }
    else if (array[min] == target)
    {
        return min;
    }
    else if (array[min] <= target && array[max] > target)
    {
        if (min != max - 1)
        {
            mid = (max + min) / 2;
            if (array[mid] > target)
            {
                max = mid;
            }
            else min = mid;

            return  binarySearchRecMy(array, target, min, max);
        }
    }
    return mid;
}

int binarySearchRec(int* array, int target, int min, int max)
{
    // Рекурсивная реализация

    if (min > max)
        return -1;

    int midpoint = min + ((max - min) / 2); // такой способ вычисления середины массива избегает вероятность возникновения переполнения

    if (array[midpoint] > target)
    {
        return binarySearchRec(array, target, min, midpoint - 1);
    }
    else if (array[midpoint] < target)
    {
        return binarySearchRec(array, target, midpoint + 1, max);
    }
    else
        return midpoint;
}

int main()
{
    int array[] = { 4, 7, 9, 13, 15, 19, 22, 24, 28, 33, 37, 41, 43, 47, 50 };

    std::cout << "Enter a number: ";
    int x;
    std::cin >> x;

    int index = binarySearchRecMy(array, x, 0, 14);

    if (array[index] == x)
        std::cout << "Good! Your value " << x << " is on position " << index << " in array!\n";
    else
        std::cout << "Fail! Your value " << x << " isn't in array!\n";

    //const int min = 2;
    //const int max = 4;
    //int startNumb, countNumb, n;
    //cout << "Start where? ";
    //cin >> startNumb;
    //cout << "How many? ";
    //cin >> countNumb;
    //int countPow = getRandomInt(min, max);
    //vector <int> arr(static_cast<vector<int>::size_type>(countNumb));
    //
    //for (int i = 0; i < countNumb; i++)
    //{
    //    arr.at(i) = startNumb * startNumb * countPow;
    //    ++startNumb;
    //}
    //cout << "I generated " << countNumb << " square numbers. Do you know what each number is after multiplying it by " << countPow << "?\n";

    //while (!(arr.empty()))
    //{
    //    cin >> n;
    //    auto found = find(arr.begin(), arr.end(), n);
    //    if (found != arr.end())
    //    {
    //        arr.erase(found);
    //        if (!(arr.empty()))
    //        {
    //            cout << "Nice! " << arr.size() << " number(s) left.\n";
    //        }
    //        else
    //        {
    //            cout << "Nice! You found all numbers, good job!\n";
    //            break;
    //        }
    //    }
    //    else
    //    {
    //        cout << n << " is wrong!";
    //        auto foundMin = min_element(arr.begin(), arr.end(), [n](auto &a, auto &b) {
    //            return abs(a - n) < abs(b - n);
    //            });
    //        if (foundMin != arr.end())
    //        {
    //            int dist = abs(*foundMin - n);
    //            if (dist <= 4)
    //            {
    //                cout << " Try " << *foundMin << " next time.\n";
    //                break;
    //            }
    //        }
    //        /*int dist;
    //        for (auto &element : arr)
    //        {
    //            dist = abs(element - n);
    //            if (dist < 4 )
    //            {
    //                cout << " Try "<< element <<" next time.\n";
    //                break;
    //            }
    //        }
    //        cout << endl;
    //        break;*/
    //        cout << endl;
    //        break;
    //    }       
    //}
    return 0;
}
