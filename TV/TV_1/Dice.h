#pragma once
#include <iostream>
#include <time.h>

class Dice {

private:
	float* facesProbs; // faceProbs - face probabilitys - вероятность выпадения грани

public:
	int facesAmount; // face - грань кубика
	int* facesProcs; // кол-во выпадений граней
	Dice();
	Dice(int, float*);
	~Dice();

	void SetProb(int, float);
	void ShowSetup();
	int GetFacesAmount();

	int Roll();
};