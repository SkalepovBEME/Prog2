#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <chrono>
using namespace std;
using namespace chrono;
void newArr(int N, int *arr, bool *sorted){
	setlocale(0, "");
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 199 - 99;
	*sorted = false;
	}
}
void maxMin(int N, int* arr, bool sorted, int *max, int *min) {
	if (!sorted) {
		for (int i = 0; i < N; i++) {
			if (arr[i] < *min)
				*min = arr[i];
			if (arr[i] > *max)
				*max = arr[i];
		}
	}
	if (sorted) {
		*max = arr[N - 1];
		*min = arr[0];
	}
}
void searchAverages(int N, int* arr, bool sorted, int max, int min, int average) {
	int count = 0;
	cout << "\nИндексы элементов, равных среднему значению: ";
		for (int i = 0; i < N; i++) {
			if (arr[i] == average) {
				cout << i << ' ';
				count += 1;
			}
		}
		cout << endl << "Количество таких элементов в массиве: " << count << endl;
}
void bubbleSort(int* arr,int N, bool *sorted) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
		}
	}
	*sorted = true;
}
void shakerSort(int* arr, int N, bool* sorted) {
	bool swapped = true;
	int start = 0;
	int end = N - 1;
	while (swapped) {
		swapped = false;
		for (int i = start; i < end; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
		swapped = false;
		end--;
		for (int i = end-1; i >= start; i--) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}
		++start;
	}
	*sorted = true;
}
void insertSort(int* arr, int N, bool* sorted) {
	int i, key, j;
	for (i = 1; i < N; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) { 
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
	*sorted = true;
}
void quickSort(int* arr, int N, bool* sorted, int end, int begin) {
	int mid;
	int f = begin;
	int l = end;
	mid = arr[(f + l) / 2];
	while (f < l)
	{
		while (arr[f] < mid) f++;
		while (arr[l] > mid) l--;
		if (f <= l)
		{
			swap(arr[f], arr[l]);
			f++;
			l--;
		}
	}
	if (begin < l) quickSort( arr, N, sorted, l, begin);
	if (f < end) quickSort( arr, N, sorted, end,  f);
	*sorted = true;
}
void combSort(int* arr, int N, bool* sorted) {
	float k = 1.247, S = N - 1;
	int count = 0, swap;
	while (S >= 1){
		for (int i = 0; i + S < N; i++){
			if (arr[i] > arr[int(i + S)]){
				swap = arr[int(i + S)];
				arr[int(i + S)] = arr[i];
				arr[i] = swap;
			}
		}
		S /= k;
	}
	while (true){
		for (int i = 0; i < N - 1; i++){
			if (arr[i] > arr[i + 1]){
				swap = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = swap;
			}
			else count++;
		}
		if (count == N - 1)
			break;
		else
			count = 0;
	}
}
void arrayOutput(int arr[], int N) {
	for (int i = 0; i < N; i++) {
		if (i == 0)
			cout << "{" << arr[i] << ' ';
		else if (i == N - 1)
			cout << arr[i] << "}";
		else
			cout << arr[i] << ' ';
	}
	cout << endl << endl;
}
int binarySearch(int arr[], int value, int start, int end) {
	if (end >= start) {
		int mid = start + (end - start) / 2;
		if (arr[mid] == value) {
			return mid;
		}
		if (arr[mid] > value) {
			return binarySearch(arr, value, start, mid - 1);
		}
		return binarySearch(arr, value, mid + 1, end);
	}
	return -1;
}
int main()
{
	auto start1 = steady_clock::now();
	auto end1 = steady_clock::now();        
	auto result1 = duration_cast<nanoseconds>(end1 - start1);
	setlocale(0, "");
	const int N = 100;
	int arr[N];
	int count;
	int resault;
	bool sorted = false;
	newArr(N, arr, &sorted);
	int min = arr[0], max = arr[N - 1];
	int average = (min + max) / 2;
	int choice = 1;
	int secondChoice = 1;
	while (choice && secondChoice) {
		if (!sorted) {
			cout << "1. Создать новый рандомный, неотсортированный массив.\n"\
				<< "2. Отсортировать массив.\n"\
				<< "3. Найти максимальный и минимальный элемент.\n"\
				<< "4. Вывести среднее значение максимального и минимального значения и вывести индексы элементов, равных этому значению, их количество.\n"\
				<< "5. Вывести массив \n"\
				<< "Введите номер функции, которой хотите вопользоваться или же 0 для окончания работы программы: ";
			cin >> choice;
			switch (choice) {
			case 0: return(0);
			case 1: cout << endl;
					newArr(N, arr, &sorted);
					min = arr[0], max = arr[N - 1];
					average = (min + max) / 2;
					break;
			case 2: cout << "\nВы хотите \"прочесать\" массив (Comb sort) перед другими сортировками? \n" \
						 << "Введите любое число, если хотите. Введите 0, если не хотите: ";
					int combSortChoice;
					cin >> combSortChoice;
					if (combSortChoice) {
						start1 = steady_clock::now();
						combSort(arr, N, &sorted);
						end1 = steady_clock::now();
						result1 = duration_cast<nanoseconds>(end1 - start1);
						cout << "\nВремени потрачено на данную сортировку: " << result1.count() << endl << "Массив отсортирован. Но отсортируйте его ещё раз, для уверенности.) \n\n";
					}
					cout << "\n1. Bubble sort \n" \
						 << "2. Shaker sort \n" \
						 << "3 Insert sort \n" \
						 << "4 Quick sort \n" \
				         <<"Введите номер сортировки, с помощью которой вы хотите отсортировать массив и узнать время этой сортировки: ";
					int nestedSelection;
					cin >> nestedSelection;
					cout << endl;
					switch (nestedSelection) {
					case 1: start1 = steady_clock::now();
							bubbleSort(arr, N, &sorted);
							end1 = steady_clock::now();
							result1 = duration_cast<nanoseconds>(end1 - start1);
							cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (Bubble sort)" << endl << endl;
							break;
					case 2: start1 = steady_clock::now();
							shakerSort(arr, N, &sorted);
							end1 = steady_clock::now();
							result1 = duration_cast<nanoseconds>(end1 - start1);
							cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (shaker sort)" << endl << endl;
							break;
					case 3: start1 = steady_clock::now();
							insertSort(arr, N, &sorted);
							end1 = steady_clock::now();
							result1 = duration_cast<nanoseconds>(end1 - start1);
							cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (insert sort)" << endl << endl;
							break;
					case 4: start1 = steady_clock::now();
							quickSort(arr, N, &sorted, N - 1, 0);
							end1 = steady_clock::now();
							result1 = duration_cast<nanoseconds>(end1 - start1);
							cout << "Массив отсортирован. \n" << "Время потраченное на сортировку: " << result1.count() << " (quick sort)" << endl << endl;
							break;
					}		
					break;
			case 3: start1 = steady_clock::now();
					maxMin(N, arr, sorted, &max, &min);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "\nmax = " << max << ',' << " min = " << min << endl \
					<< "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			case 4: average = (min + max) / 2;
					cout << "\nСреднее значение: " << average;
					start1 = steady_clock::now();
					searchAverages(N, arr, sorted, max, min, average);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			case 5: arrayOutput(arr, N);
					break;
			}
		}
		if (sorted) {
			cout << "1. Создать новый рандомный, неотсортированный массив.\n"\
				<< "2. Вывести количество элементов, меньших заданного вами числа А \n"\
				<< "3. Вывести количество элементов, больших заданного вами числа B \n"\
				<< "4. Наличие введённого вами числа в массиве (поиск) \n"\
				<< "5. Поменять местами элементы, индексы которых вы введёте \n"\
				<< "6. Вывести массив \n"\
				<< "7. Найти максимальный и минимальный элемент \n"\
				<< "8. Вывести среднее значение максимального и минимального значения и вывести индексы элементов, равных этому значению, их количество.\n"\
				<< "Введите номер функции, которой хотите воспользоваться или же 0 для окончания работы програмы: ";
			cin >> secondChoice;
			switch (secondChoice) {
			case 0: break;
			case 1:	cout << endl;
				newArr(N, arr, &sorted);
				min = arr[0], max = arr[N - 1];
				average = (min + max) / 2;
				break;
			case 2: int A;
				cout << "\nВведите нужное вам число А: ";
				cin >> A;
				count = 0;
				for (int i = 0; arr[i] < A && i < N; i++)
						count += 1;
				cout << "Количество чисел в массиве, меньших А: " << count << endl << endl;
				break;
			case 3: int B;
				cout << "\nВведите нужное вам число B: ";
				cin >> B;
				count = 0;
				for (int i = N-1; arr[i] > B; i--)
					count += 1;
				cout << "Количество чисел в массиве, больших B: " << count << endl << endl;
				break;
			case 4: int value;
				cout << "\nВведите число, наличие которого в массиве вы хотите узнать: ";
				cin >> value;
				start1 = steady_clock::now();
				resault = binarySearch(arr, value, 0, N - 1);
				end1 = steady_clock::now();
				result1 = duration_cast<nanoseconds>(end1 - start1);
				if (resault == -1)
					cout << "Вашего числа нет в массиве :(" << endl << endl;
				else{
					cout << "Ваше число есть в массиве и оно находится под индексом " << resault << endl << "Время потраченное на его поиск: " << result1.count() << endl;
					start1 = steady_clock::now();
					for (int i = 0; i < N; i++) {
						if (arr[i] == value)
							break;
					}
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Время потраченное на его поиск простым перебором: " << result1.count() << endl << endl;
			}
					break;
			case 5: int change, secondChange;
					cout << "\nВведите два индекса, элементов, которых вы хотите поменять местами: ";
					cin >> change >> secondChange;
					start1 = steady_clock::now();
					swap(arr[change], arr[secondChange]);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "\nЧисла поменяны. \n" << "Времени затрачено: " << result1.count() << endl << endl;
					sorted = false;
					break;
			case 6: arrayOutput(arr, N);
					break;
			case 7: start1 = steady_clock::now();
					maxMin(N, arr, sorted, &max, &min);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "\nmax = " << max << ',' << " min = " << min << endl \
					<< "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			case 8: maxMin(N, arr, sorted, &max, &min);
					average = (min + max) / 2;
					cout << "\nСреднее значение: " << average;
					start1 = steady_clock::now();
					searchAverages(N, arr, sorted, max, min, average);
					end1 = steady_clock::now();
					result1 = duration_cast<nanoseconds>(end1 - start1);
					cout << "Время выполнения данной функции: " << result1.count() << endl << endl; break;
			}
		}
	}
}
