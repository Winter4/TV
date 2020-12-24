#include <iostream>
#include "Dice.h"
#include "conio.h"
using namespace std;

// сделать броски в автоматическим режиме
void AutoRoll(Dice, Dice);
// делать броски в ручном режиме
void ManualRoll(Dice, Dice);

int main()
{
    srand(time(0));

    Dice dice1(4), dice2(4);

    dice1.SetProb(1, 0.5);
    dice2.SetProb(4, 0.8);

    cout << "Dice 1: " << endl;
    dice1.ShowSetup();
    cout << endl << "Dice 2: " << endl;
    dice2.ShowSetup();

    int choice;
    while (true) {
        cout << endl << " Press <A> (auto) or <M> (manual) choose the rolling mode." << endl << " Press <E> (exit) to exit the program: ";
        choice = _getch();

        switch (choice) {
        case 97: // клавиша A (англ.)
            AutoRoll(dice1, dice2);
            break;
        case 109: // клавиша M (англ.)
            ManualRoll(dice1, dice2);
            break;
        case 101: // клавиша E (англ.)
            return 0;
            break;
        } 
    } 
}

void AutoRoll(Dice dice1, Dice dice2)
{
   

    int dropsAmount;
    do {
        cout << "\n Enter the amount of drops: "; // ввод выборки
        cin >> dropsAmount;
    } while (dropsAmount < 1);

    for (int i = 0; i < dice1.facesAmount; i++) // очищение сохраняющих массивов
        dice1.facesDrops[i] = 0;
    for (int i = 0; i < dice2.facesAmount; i++)
        dice2.facesDrops[i] = 0;

    for (int i = 0; i < dropsAmount; i++) { // бросание кубов
        dice1.facesDrops[dice1.Roll() - 1]++;
        dice2.facesDrops[dice2.Roll() - 1]++;
    }

    cout << "\nDice 1: " << endl;
    cout << " Face | Teor. prob. | Drops | Pract. prob. " << endl;
    for (int i = 0; i < dice1.facesAmount; i++)
        printf("   %d\t%9.5f\t%d\t%9.5f \n", i + 1, dice1.GetFaceProbability(i + 1), dice1.facesDrops[i], (float)dice1.facesDrops[i] / dropsAmount);

    cout << "\nDice 2: " << endl;
    cout << " Face | Teor. prob. | Drops | Pract. prob. " << endl;
    for (int i = 0; i < dice2.facesAmount; i++)
        printf("   %d\t%9.5f\t%d\t%9.5f \n", i + 1, dice2.GetFaceProbability(i + 1), dice2.facesDrops[i], (float)dice2.facesDrops[i] / dropsAmount);

    int coupleDrops[7] = { 0 }; // массив с рез-ми опытов (выпадение суммы очков)
    for (int i = 0; i < dropsAmount; i++) 
        coupleDrops[dice1.Roll() + dice2.Roll() - 2]++;

    // массивы-дублёры facesProbs; теоретическая вероятность
    float* facesProbsLocal1 = new float[dice1.facesAmount];
    float* facesProbsLocal2 = new float[dice2.facesAmount];

    for (int i = 0; i < dice1.facesAmount; i++)
        facesProbsLocal1[i] = dice1.GetFaceProbability(i + 1);
    for (int i = 0; i < dice2.facesAmount; i++)
        facesProbsLocal2[i] = dice2.GetFaceProbability(i + 1);

    float coupleProbs[7] = { 0 }; // массив, в котором будет содержаться вероятность выпадения суммы очков
    coupleProbs[0] = facesProbsLocal1[0] * facesProbsLocal2[0];
    coupleProbs[1] = facesProbsLocal1[0] * facesProbsLocal2[1] + facesProbsLocal1[1] * facesProbsLocal2[0];
    coupleProbs[2] = facesProbsLocal1[0] * facesProbsLocal2[2] + facesProbsLocal1[1] * facesProbsLocal2[1] + facesProbsLocal1[2] * facesProbsLocal2[0];
    coupleProbs[3] = facesProbsLocal1[0] * facesProbsLocal2[3] + facesProbsLocal1[1] * facesProbsLocal2[2] + facesProbsLocal1[2] * facesProbsLocal2[1] + facesProbsLocal1[3] * facesProbsLocal2[0];
    coupleProbs[4] = facesProbsLocal1[1] * facesProbsLocal2[3] + facesProbsLocal1[2] * facesProbsLocal2[2] + facesProbsLocal1[3] * facesProbsLocal2[1];
    coupleProbs[5] = facesProbsLocal1[2] * facesProbsLocal2[3] + facesProbsLocal1[3] * facesProbsLocal2[2];
    coupleProbs[6] = facesProbsLocal1[3] * facesProbsLocal2[3];

    cout << "\nTwo dices rolls results: " << endl;
    cout << " Face | Teor. prob. | Drops | Pract. prob. " << endl;
    for (int i = 0; i < 7; i++)
        printf("   %d\t%9.5f\t%d\t%9.5f \n", i + 2, coupleProbs[i], coupleDrops[i], (float)coupleDrops[i] / dropsAmount);

    delete[] facesProbsLocal1;
    delete[] facesProbsLocal2;
}

void ManualRoll(Dice dice1, Dice dice2)
{
    int button;

    do {
        cout << endl << "\n Press <R> (roll), or <E> (exit) " << endl;
        button = _getch();

        int face = 0;
        switch (button) {
        case 114: // клавиша R (англ.)
            face = dice1.Roll(); // служебная переменная для номера выпавшей грани
            cout << "Face " << face << " dropped. Teorethical probability: " << dice1.GetFaceProbability(face) << endl;
            face = dice2.Roll();
            cout << "Face " << face << " dropped. Teorethical probability: " << dice2.GetFaceProbability(face) << endl;
            break;
        case 101: // клавиша Е (англ.)
            return;
            break;
        }
    } while (true);
}