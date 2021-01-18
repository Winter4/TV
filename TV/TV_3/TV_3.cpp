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
		int x_start = -1,
			 x_end = 1;
		int inervalsNum = 100; // количество интервалов
		difference = (float)(x_end - x_start) / inervalsNum; // шаг икса
		
		float sum1 = 0, sum2 = 0;

		// заполняем значения иксов
		for (float x = x_start; x < x_end + difference; x += difference) {
			x_values.push_back(x);
			sum1 += Function(x);
		}
		
		// заполняем значния интервалов
		for (int i = 0; i < 100; i++) {
			sum2 += Function(x_values[i]) / sum1;
			intervals.push_back(sum2);

			joinIntervals.push_back(0);
		}
		
	}

	float Function(float x) { // функция плотности распределения
		return exp(-(x * x) / (2 * 0.25) / (sqrt(2 * 3.14) * 0.5));
	}

	void PrintIntervals()
	{
		std::cout << "Intervals: " << std::endl;
		for (float i : intervals)
			std::cout << i << std::endl;
		std::cout << std::endl;
	}

	void MyTask()
	{
		// ввод выборки
		do {
			std::cout << "  Enter the sample size (int number >100): ";
			if (!(std::cin >> sampleSize)) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		} while (sampleSize < 100);
		
		// проверка на попадание в интервал
		for (int i = 0; i < sampleSize; i++) {
			float random = (float)rand() / RAND_MAX;
			
			for (int j = 0; j < intervals.size(); j++) {
				if (intervals[j] > random) {
					++joinIntervals[j];
					break;
				}
			}
		}
		
		std::cout << "   X\tJoin\t  M.Exp.\tDispersion\tAvg. Sqr." << std::endl;

		float 
			empiricProbability = 0,
			mathExpectation = 0,
			mathExpectationSquare = 0,
			dispersion = 0,
			kolmogorova = 0;

		for (int i = 0; i < intervals.size(); i++) {
			empiricProbability = joinIntervals[i] / (float)sampleSize;
			mathExpectation += x_values[i] * empiricProbability;
			mathExpectationSquare += (x_values[i] * x_values[i]) * empiricProbability;
			dispersion += mathExpectationSquare - mathExpectation * mathExpectation;
			kolmogorova += fabs(empiricProbability - intervals[i]) / sqrt(sampleSize);

			//std::cout << x_values[i] << "\t" << joinIntervals[i] << "\t" << mathExpectation << "\t\t" << dispersion << "\t\t" << sqrt(dispersion) << std::endl;
			printf("%-9.2f %-7d %-16.3f %-13.3f %-9.3f \n", x_values[i], joinIntervals[i], mathExpectation, dispersion, sqrt(dispersion));
		}
		printf("\n Kolmogorova state: %.3f", kolmogorova);
	}
};

int main()
{
	
	Generator lab3;
	
	lab3.PrintIntervals();
	lab3.MyTask();
	
	std::cout << std::endl;
	system("pause");
	return 0;
}