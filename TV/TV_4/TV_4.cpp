#include <iostream>
#include "math.h"
#include "windows.h"
#include <vector>

#define LAMBDA 0.5

class Generator {
private:
	int sampleSize; // выборка
	int intervalsNum;

	std::vector<float> intervals; // интервалы
	std::vector<int> joinIntervals; // вхождение в интервалы
	std::vector<float> x_values; // значения иксов

	std::vector< std::vector<float> > criticals{
		{0.0039, 0.016, 3.84},
		{0.103, 0.211, 5.99},
		{0.352, 0.584, 7.815},
		{0.711, 1.064, 9.488},
		{1.145, 1.61, 11.071},
		{1.635, 2.204, 12.592},
		{2.167, 2.833, 14.067},
		{2.733, 3.49, 18.307 },
		{3.325, 4.168, 16.919},
		{3.94, 4.865, 18.307 },
		{4.575, 5.578, 19.675},
		{5.226, 6.304, 21.026 },
		{5.89, 7.042, 22.362},
		{6.571, 7.79, 23.685 },
		{7.261, 8.547, 24.996},
		{7.962, 9.312, 26.296},
		{8.672, 10.085, 28.869 },
		{9.39, 10.865, 28.869},
		{10.117, 11.651, 30.114 },
		{10.851, 12.443, 31.410},
		{11.591, 13.24, 32.671 },
		{12.338, 14.042, 33.924},
		{13.091, 14.848, 35.172 },
		{13.848, 15.659, 36.415},
		{14.611, 16.473, 37.652 }
		};

	float difference;
	float R;

public:
	Generator()
	{
		// ввод выборки
		do {
			std::cout << "  Enter the sample size (int number >100): ";
			if (!(std::cin >> sampleSize)) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		} while (sampleSize < 1000);

		// начальное и конечное значение икса
		int x_start = -1,
			x_end = 1;
		
		R = (float)x_end - x_start; // размах варьирования
		intervalsNum = 1 + 3.32 * log10f(sampleSize); // количество интервалов
		difference = R / intervalsNum; // шаг икса

		float sum1 = 0, sum2 = 0;

		// заполняем значения иксов
		for (float x = x_start; x < x_end + difference; x += difference) {
			x_values.push_back(x);
			sum1 += Function(x);
		}
		//std::cout << "VUJ1";
		// заполняем значния интервалов
		for (int i = 0; i < intervalsNum; i++) {
			sum2 += Function(x_values[i]) / sum1;
			intervals.push_back(sum2);

			joinIntervals.push_back(0);
		}
		//std::cout << "VUJ2";
	}

	float Function(float x) { // функция плотности распределения
		return exp(-(x * x) / (2 * 0.25) / (sqrt(2 * 3.14) * 0.5));
	}

	void PrintIntervals()
	{
		std::cout << "Intervals: " << std::endl;
		for (int i = 0; i < intervalsNum; i++)
			std::cout << intervals[i] << std::endl;
		std::cout << std::endl;
	}

	void MyTask()
	{
		
		// проверка на попадание в интервал
		for (int i = 0; i < sampleSize; i++) {
			float random = (float)rand() / RAND_MAX;

			for (int j = 0; j < intervalsNum; j++) {
				if (intervals[j] > random) {
					++joinIntervals[j];
					break;
				}
			}
		}
		
		printf("№  left X\tright x\t   middle x \t Ni \t Emp.p.\t High \t Emp.f.\tTer.p. \tEmp.p \n");

		float
			empiricProbability = 0,
			empiricSum = 0,
			lastInterval = 0,
			mathExpectation = 0,
			mathExpectationSquare = 0,
			dispersion = 0,
			kolmogorova = 0,
			pearson = 0;

		for (int i = 0; i < intervalsNum; i++) {
			empiricProbability = joinIntervals[i] / (float)sampleSize;
			empiricSum += empiricProbability;

			mathExpectation += x_values[i] * empiricProbability;
			mathExpectationSquare += (x_values[i] * x_values[i]) * empiricProbability;

			dispersion += mathExpectationSquare - mathExpectation * mathExpectation;

			kolmogorova += fabs(empiricProbability - intervals[i]) / sqrt(sampleSize);
			pearson += powf(empiricProbability - intervals[i], 2.0) / intervals[i];
			
			if (i < intervalsNum - 1)
				printf("%d  %.5f\t%.2f \t   %.4f \t %d \t  %.2f \t %.2f \t %.2f \t%.2f \t%.2f \n",
					i + 1,
					intervals[i],
					intervals[i+ 1],
					(intervals[i + 1] - intervals[i]) / 2,
					joinIntervals[i],
					empiricProbability,
					empiricProbability / difference,
					empiricSum,
					intervals[i] - lastInterval,
					intervals[i]
					);
			else 
				printf("%d  %.5f \t%.2f \t   %.4f \t %d \t  %.2f \t %.2f \t %.2f \t%.2f \t%.2f \n",
					i + 1,
					intervals[i],
					1.0,
					(1 - intervals[i]) / 2,
					joinIntervals[i],
					empiricProbability,
					empiricProbability / difference,
					empiricSum,
					intervals[i] - lastInterval,
					intervals[i]
				);

			lastInterval = intervals[i];

			//std::cout << x_values[i] << "\t" << joinIntervals[i] << "\t" << mathExpectation << "\t\t" << dispersion << "\t\t" << sqrt(dispersion) << std::endl;
			//printf("%-9.2f %-7d %-16.3f %-13.3f %-9.3f \n", x_values[i], joinIntervals[i], mathExpectation, dispersion, sqrt(dispersion));
		}

		std::cout << "\nMath expectation: " << mathExpectation << std::endl;
		std::cout << "Dispersion: " << dispersion << std::endl;
		std::cout << "Avg. sqr.: " << sqrt(dispersion) << std::endl;
		std::cout << "Pearson: " << pearson << std::endl;
		std::cout << "Kolmogorov: " << kolmogorova << std::endl;

		if (pearson < criticals[intervalsNum - 3][0])
			std::cout << "\n Importance: 0.95 \n" << criticals[intervalsNum - 3][0];
		else
			if (pearson < criticals[intervalsNum - 3][1])
				std::cout << "\n Importance: 0.9 \n" << criticals[intervalsNum - 3][1];
			else
				if (pearson < criticals[intervalsNum - 3][2])
					std::cout << "\n Importance: 0.05 \n" << criticals[intervalsNum - 3][2];
				else
					std::cout << "\n Importance: < 0.05 \n";
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