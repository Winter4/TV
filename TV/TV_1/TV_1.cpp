#include <iostream>
#include "Dice.h"
using namespace std;

int main()
{
    srand(time(0));
    Dice tetra_equal;
    tetra_equal.ShowSetup();

    tetra_equal.facesProcs = new int[tetra_equal.facesAmount];
    for (int i = 0; i < tetra_equal.facesAmount; i++)
        tetra_equal.facesProcs[i] = 0;

    for (int i = 0; i < 20000; i++) 
        tetra_equal.facesProcs[tetra_equal.Roll() - 1]++;
    
    cout << endl;
    cout << tetra_equal.facesProcs[0] << endl;
    cout << tetra_equal.facesProcs[1] << endl;
    cout << tetra_equal.facesProcs[2] << endl;
    cout << tetra_equal.facesProcs[3] << endl;

    cout << endl;
    system("pause");
    return 0;
}

