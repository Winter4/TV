#include "Dice.h"
using namespace std;

Dice::Dice()
{
	facesAmount = 4;
	facesProbs = new float[facesAmount];

	float tmp = 0; // сумма n - 1 вероятностей
	for (int i = 0; i < facesAmount - 1; i++) {
		facesProbs[i] = 1.0 / 4;
		tmp += facesProbs[i];
	}
	facesProbs[facesAmount - 1] = 1.0 - tmp;
}

Dice::Dice(int facesAmountToSet, float* faceProbsToSet)
{
	facesAmount = facesAmountToSet;

	for (int i = 0; i < facesAmount; i++)
		facesProbs[i] = faceProbsToSet[i];
}

Dice::~Dice()
{
	delete[] facesProbs;
	delete[] facesProcs;
}

void Dice::SetProb(int faceNum, float probToSet)
{
	if (faceNum <= facesAmount) {
		facesProbs[faceNum - 1] = probToSet;
		for (int i = 0; i < facesAmount; i++)
			if (i != faceNum - 1)
				facesProbs[i] = (1.0 - probToSet) / (facesAmount - 1.0);
	}
}

void Dice::ShowSetup()
{
	cout << "Cube faces amount: " << facesAmount << endl;
	cout << "Faces proc probability: ";
	for (int i = 0; i < facesAmount; i++)
		cout << facesProbs[i] << " ";

	cout << endl;
}

int Dice::Roll()
{
	float result = ((float)rand() / (RAND_MAX)); // результат броска
//	cout << endl << "Result: " << result << endl;
	float probsSum = 0; // служебная переменная для отслеживания
	int i = 0;
	while (probsSum <= result) {
		probsSum += facesProbs[i];
		i++;
	}

	return i;
}

int Dice::GetFacesAmount()
{
	return facesAmount;
}