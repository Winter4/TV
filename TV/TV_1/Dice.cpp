#include "Dice.h"
using namespace std;

Dice::Dice(int facesAmountToSet)
{
	facesAmount = facesAmountToSet;
	facesProbs = new float[facesAmount];

	float tmp = 0; // ����� n - 1 ������������
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
	delete[] facesProcs;
}

void Dice::SetProb(int faceNum, float probToSet) // xyi
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
	float result = ((float)rand() / (RAND_MAX)); // ��������� ������
//	cout << endl << "Result: " << result << endl;
	float probsSum = 0; // ��������� ���������� ��� ������������
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