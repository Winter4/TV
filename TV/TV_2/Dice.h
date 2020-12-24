#pragma once
#include <iostream>
#include <time.h>

class Dice {

private:
	// faceProbs - face probabilitys - ����������� ��������� �����
	float* facesProbs;

public:
	int facesAmount; // face - ����� ������
	int* facesDrops; // ���-�� ��������� ������

	// ����������� �� ��������� ������ ��������. ����� � int ������
	Dice(int);
	// int - ���-�� ������ ������, float* - ������ ������������
	Dice(int, float*);

	~Dice();

	// ���������� ����������� ��� �����
	void SetProb(int, float);
	// ���������� �����
	void ShowSetup();
	// �������� ����������� ��������� ����� [1; N]
	float GetFaceProbability(int);

	// ������� ������; ���������� ����� ����� [1; N]
	int Roll();
};