#pragma once
#include <iostream>
#include <time.h>

class Dice {

private:
	// faceProbs - face probabilitys - вероятность выпадения грани
	float* facesProbs;

public:
	int facesAmount; // face - грань кубика
	int* facesDrops; // кол-во выпадений граней

	// конструктор по умолчанию создаёт равновер. кубик с int граней
	Dice(int);
	// int - кол-во граней кубика, float* - массив вероятностей
	Dice(int, float*);

	~Dice();

	// установить вероятность для грани
	void SetProb(int, float);
	// отобразить сетап
	void ShowSetup();
	// получить вероятность выпадения грани [1; N]
	float GetFaceProbability(int);

	// функция броска; возвращает номер грани [1; N]
	int Roll();
};