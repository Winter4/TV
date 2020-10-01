#pragma once
#include <iostream>
#include <time.h>

class Dice {

private:
	// faceProbs - face probabilitys - ����������� ��������� �����
	float* facesProbs;

public:
	int facesAmount; // face - ����� ������
	int* facesProcs; // ���-�� ��������� ������

	// ����������� �� ��������� ������ ��������. ����� � int ������
	Dice(int);
	// int - ���-�� ������ ������, float* - ������ ������������
	Dice(int, float*);

	~Dice();

	// ���������� ����������� ��� �����
	void SetProb(int, float);
	// ���������� �����
	void ShowSetup();
	// �������� ���-�� ������
	int GetFacesAmount();

	// ������� ������
	int Roll();
};