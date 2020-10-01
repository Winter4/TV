#pragma once
#include <iostream>
#include <time.h>

class Dice {

private:
	// faceProbs - face probabilitys - вероятность выпадения грани
	float* facesProbs;

public:
	int facesAmount; // face - грань кубика
	int* facesProcs; // кол-во выпадений граней

	// конструктор по умолчанию создаёт равновер. кубик с int граней
	Dice(int);
	// int - кол-во граней кубика, float* - массив вероятностей
	Dice(int, float*);

	~Dice();

	// установить вероятность для грани
	void SetProb(int, float);
	// отобразить сетап
	void ShowSetup();
	// получить кол-во граней
	int GetFacesAmount();

	// функция броска
	int Roll();
};