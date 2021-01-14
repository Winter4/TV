#include <iostream>
#include "math.h"
#include "windows.h"
#include <vector>

#define LAMBDA 0.5

class Generator {
private:
	int sampleSize; // выборка

	std::vector<float> intervals; // интервалы
	std::vector<int> joinIntervals; // вхождение в интервалы
	std::vector<float> x_values; // значения иксов

	float difference;

public:
	Generator() 
	{
		// начальное и конечное значение икса
		int x_start = -3,
			 x_end = 3;
		difference = (float)(x_end - x_start) / 100; // шаг икса; 50 - кол-во интервалов
		
		float sum1 = 0, sum2 = 0;

		// заполняем значения иксов
		for (float x = x_start; x <= x_end + difference; x += difference) {
			x_values.push_back(x);
			sum1 += Function(x);
		}
		
		// заполняем значния интервалов
		for (int i = 0; i < 100; i++) {
			sum2 += Function(x_values[i]);
			intervals.push_back(sum2);

			joinIntervals.push_back(0);
		}
		
	}

	float Function(float x) { // функция плотности распределения
		//return exp(-(x * x) / (2 * 0.25) / (sqrt(2 * 3.14) * 0.5));
		return exp(-((x * x) / 2)) / sqrt(2 * 3.14);
	}

	void PrintIntervals()
	{
		std::cout << "Intervals: " << std::endl;
		for (int i : intervals)
			std::cout << intervals[i] << std::endl;
		std::cout << std::endl;
	}

	void MyTask()
	{
		std::cout << "  Enter the sample size: ";
		// ввод выборки
		do {
			if (!(std::cin >> sampleSize)) {
				std::cout << "Please enter correct number (>100): " << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		} while (sampleSize < 100);
		
		// проверка на попадание в интервал
		for (int i = 0; i < sampleSize; i++) {
			float random = (float)rand() / RAND_MAX;
			
			for (int j : intervals) {
				if (intervals[j] > random) {
					++joinIntervals[j];
					break;
				}
			}
		}
		
		std::cout << "X\tJoin\tMath Exp.\tDispersion\tAvg. Sqr." << std::endl;

		float 
			empiricProbability = 0,
			mathExpectation = 0,
			mathExpectationSquare = 0,
			dispersion = 0,
			kolmogorova = 0;

		for (int i : intervals) {
			empiricProbability = joinIntervals[i] / sampleSize;
			mathExpectation += x_values[i] * empiricProbability;
			mathExpectationSquare += (x_values[i] * x_values[i]) * empiricProbability;
			dispersion += mathExpectationSquare - mathExpectation * mathExpectation;
			kolmogorova += fabs(empiricProbability - intervals[i]) / sqrt(sampleSize);

			std::cout << x_values[i] << "\t" << joinIntervals[i] << "\t" << mathExpectation << "\t\t" << dispersion << "\t\t" << sqrt(dispersion) << std::endl;
		}
	}
};

int main()
{
	
	Generator lab3;
	
	lab3.PrintIntervals();
	
	lab3.MyTask();
	
	system("pause");
	return 0;
}