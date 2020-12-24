#include "Dice.h"
using namespace std;

Dice::Dice(int facesAmountToSet)
{
	facesAmount = facesAmountToSet;
	facesProbs = new float[facesAmount];
	facesDrops = new int[facesAmount];

	float tmp = 0; // сумма n - 1 вероятностей
	for (int i = 0; i < facesAmount - 1; i++) {
		facesProbs[i] = 1.0 / facesAmount;
		tmp += facesProbs[i];
	}
	facesProbs[facesAmount - 1] = 1.0 - tmp;
}

Dice::Dice(int facesAmountToSet, float* facesProbsToSet)
{
	facesAmount = facesAmountToSet;

	for (int i = 0; i < facesAmount; i++)
		facesProbs[i] = facesProbsToSet[i];
}

Dice::~Dice()
{
	delete[] facesProbs;
	delete[] facesDrops;
}

void Dice::SetProb(int faceNum, float probToSet) // 
{
	if (faceNum <= facesAmount && faceNum > 0 && probToSet > 0 && probToSet < 1) {
		float sum = 0; // служебная переменная для вычисления 1 - сумма вероятностей

		if (faceNum != facesAmount) {
			facesProbs[faceNum - 1] = probToSet; // если дом. грань стоит в середине, то присвоить ей значение
			sum += probToSet; // для корректного вычисления последней грани прибавляем к сумме дом. грань

			for (int i = 0; i < facesAmount - 1; i++)
				if (i != faceNum - 1) {
					facesProbs[i] = (1.0 - probToSet) / (facesAmount - 1);
					sum += facesProbs[i];
				}
			facesProbs[facesAmount - 1] = 1.0 - sum;
		}
		else {
			for (int i = 0; i < facesAmount - 1; i++) {
				facesProbs[i] = (1.0 - probToSet) / (facesAmount - 1);
				sum += facesProbs[i];
			}
			facesProbs[faceNum - 1] = 1.0 - sum;
		}
	}
	else {
		cout << "Wrong data!" << endl;
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
	float probsSum = 0; // служебная переменная для отслеживания суммы вероятностей
	int i = 0; // индикатор грани 
	while (probsSum <= result) {
		probsSum += facesProbs[i];
		i++;
	}

	return i;
}

float Dice::GetFaceProbability(int face)
{
	if (face > 0 && face <= facesAmount)
		return facesProbs[face - 1];
	else
		cout << "Wrong data!" << endl;
}