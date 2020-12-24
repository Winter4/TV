#include <iostream>
#include "math.h"
#include "windows.h"

#define IN 0.
#define OUT 5. 
#define L 2.

using namespace std;

class distrib
{
private:
	int n;
	float* ver;
	float* valueX;
public:
	distrib()
	{
		n = 100;
		ver = new float[n]();
		valueX = new float[n]();
		for (int i = 0; i < n; i++)
		{
			valueX[i] = (OUT - IN) * (i + 1) / n;
			ver[i] = func(valueX[i]);
		}
	}
	distrib(int num)
	{
		if (num > 0) n = num;
		else n = 100;
		ver = new float[n]();
		valueX = new float[n]();
		for (int i = 0; i < n; i++)
		{
			valueX[i] = (OUT - IN) * (i + 1) / n;
			ver[i] = func(valueX[i]);
		}
	}
	~distrib()
	{
		delete[] ver;
		delete[] valueX;
	}
	float func(float x)
	{
		if (x < 0) return 0;
		return (1 - expf(-L * x));
	}
	int roll()
	{
		float random = (float)rand() * (ver[n - 1]) / RAND_MAX;
		for (int i = 0; i < n; i++)
			if (random <= ver[i])return i;
	}
	void autoroll()
	{
		int k;

		do
		{
			cout << "Размер выборки: ";
			cin >> k;
		} while (k < 1);
		int* g = new int[n]();
		for (int i = 0; i < k; i++)
			g[roll()]++;

		float hi = 0, verlast = 0, mat_oz = 0, dispersion = 0;
		for (int i = 0; i < n; i++)
		{
			float pr_ver = (float)g[i] / k;
			hi += powf(ver[i] - verlast - pr_ver, 2.) / (ver[i] - verlast);
			dispersion += powf(valueX[i], 2) * pr_ver;
			mat_oz += valueX[i] * pr_ver;
			verlast = ver[i];
		}
		hi *= k;
		dispersion -= powf(mat_oz, 2.);
		cout << "Математическое ожидание: " << mat_oz << "\nДисперсия: " << dispersion << "\nСреднеквадратическое отклонение:" << sqrt(dispersion) << "\nКритерий Пирсона: " << hi;
		_getch();
		delete[]g;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	distrib a;
	a.autoroll();
	return 0;
}