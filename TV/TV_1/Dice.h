#pragma once
#include <iostream>
#include <time.h>

class Dice {

private:
	float* facesProbs; // faceProbs - face probabilitys - ����������� ��������� �����

public:
	int facesAmount; // face - ����� ������
	int* facesProcs; // ���-�� ��������� ������
	Dice();
	Dice(int, float*);
	~Dice();

	void SetProb(int, float);
	void ShowSetup();
	int GetFacesAmount();

	int Roll();
};