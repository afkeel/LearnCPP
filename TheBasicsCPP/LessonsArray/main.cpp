#include <iostream>
#include <algorithm>
#include <string_view>
#include <string>
#include <array>
#include <time.h>
#include <vector>
#include <random>
#include <functional>

using namespace std;

struct Student
{
	string name;
	int score;
};

void sortVibor(Student* arr, int length)
{
	for (int startIndex = 0; startIndex < length - 1; ++startIndex)
	{
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
		// Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		int smallestIndex = startIndex;

		// Затем ищем элемент поменьше в остальной части массива
		for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			// Если мы нашли элемент, который меньше нашего наименьшего элемента,
			if (arr[currentIndex].score > arr[smallestIndex].score)
				// то запоминаем его
				smallestIndex = currentIndex;
		}

		// smallestIndex теперь наименьший элемент. 
				// Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
		std::swap(arr[startIndex], arr[smallestIndex]);

	}
}

void show(Student* arrStudents, int count_students)
{
	for (int i = 0; i < count_students; i++)
	{
		cout << arrStudents[i].name << " got a grade of " << arrStudents[i].score << endl;
	}
}

namespace Items
{
	enum Items
	{
		HEALTH_POTION,
		ARROW,
		TORCH,
		COUNT_ITEM
	};
}

int countTotalItems(int arr[])
{
	int count = 0;
	for (int i = 0; i < Items::COUNT_ITEM; i++)
	{
		count += arr[i];
	}
	return count;
}

bool ascending(int a, int b)
{
	return a > b; // меняем местами, если первый элемент больше второго
}

bool evensFirst(int a, int b)
{
	// Если a - чётное число, а b - нечётное число, то a идет первым (никакой замены местами не требуется)
	if ((a % 2 == 0) && !(b % 2 == 0))
		return false;

	// Если a - нечётное число, а b - чётное число, то b идет первым (здесь уже требуется замена местами)
	if (!(a % 2 == 0) && (b % 2 == 0))
		return true;

	// В противном случае, сортируем в порядке возрастания
	return ascending(a, b);
}

void selectionSort(int arr[], int length, function<bool(int, int)>ptr)
{
	// Перебираем каждый элемент массива
	for (int startIndex = 0; startIndex < length; ++startIndex)
	{
		// bestIndex - это индекс наименьшего/наибольшего элемента, который мы обнаружили до этого момента
		int bestIndex = startIndex;

		// Ищем наименьший/наибольший элемент среди оставшихся в массиве (начинаем со startIndex+1)
		for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
		{
			// Если текущий элемент меньше/больше нашего предыдущего найденного наименьшего/наибольшего элемента,
			if (ptr(arr[bestIndex], arr[currentIndex])) // СРАВНЕНИЕ ВЫПОЛНЯЕТСЯ ЗДЕСЬ
				// то это наш новый наименьший/наибольший элемент в этой итерации
				bestIndex = currentIndex;
		}

		// Меняем местами наш стартовый элемент с найденным наименьшим/наибольшим элементом
		std::swap(arr[startIndex], arr[bestIndex]);
	}
}

struct Season
{
	string_view name{};
	double averageTemperature{};
};

int main()
{
	/*array<Season, 4> seasons{
	{ { "Spring", 285.0 },
	  { "Summer", 296.0 },
	  { "Fall", 288.0 },
	  { "Winter", 263.0 } }
	};
	sort(seasons.begin(), seasons.end(), [](const auto& a, const auto& b) {
		return a.averageTemperature < b.averageTemperature;
		});
	for (const auto& season : seasons)
	{
		cout << season.name << '\n';
	}*/

	/*int numb;
	do
	{
		cout << "Enter numb: ";
		cin >> numb;

		if (!(numb >= 1 && numb <= 9)) {

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
			}
		}
		else {
			cin.ignore(32767, '\n');
			break;
		}

	} while (true);
	int array[] = { 7, 5, 6, 4, 9, 8, 2, 1, 3 };
	const unsigned int length = sizeof(array) / sizeof(array[0]);
	for (size_t i = 0; i < length; i++)
	{
		if (array[i] == numb)
		{
			cout << i << endl;
			break;
		}
	}*/

	//int students[] = { 73, 85, 84, 44, 178 };
	//const int numStudents = sizeof(students) / sizeof(students[0]);

	//int maxScore = 0; // отслеживаем самую высокую оценку
	//int maxIndex = 0;

	//for (int person = 0; person < numStudents; ++person)
	//	if (students[person] > maxScore) {

	//		maxScore = students[person];
	//		maxIndex = person;
	//	}

	//std::cout << "The best score was " << maxScore << '\n';
	//std::cout << "The best score index " << maxIndex << '\n';

	/*int arr[] = { 4, 8, 6, 3, 1, 2, 5, 7 };
	const int length = sizeof(arr)/sizeof(arr[0]);

	selectionSort(arr, length, evensFirst);
	for (int index = 0; index < length; index++)
		std::cout << arr[index] << ' ';
	cout << endl;*/

	/*int arrItemsCount[Items::COUNT_ITEM];
	arrItemsCount[Items::HEALTH_POTION] = 3;
	arrItemsCount[Items::ARROW] = 12;
	arrItemsCount[Items::TORCH] = 6;

	cout << countTotalItems(arrItemsCount)<<endl;*/

	cout << "Enter a count students: ";
	int count_students;
	cin >> count_students;
	Student* arrStudents = new Student[count_students];
	cout << "Enter a name and score student: " << endl;

	for (int i = 0; i < count_students; i++)
	{
	cin >> arrStudents[i].name;
	cin >> arrStudents[i].score;
	}

	sortVibor(arrStudents, count_students);
	show(arrStudents, count_students);
	delete[] arrStudents;

	return 0;
}