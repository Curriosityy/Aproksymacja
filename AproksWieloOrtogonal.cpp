
#include <math.h>
#include <iostream>
#include <conio.h>
using namespace std;
//ca³kowanie numeryczne
double funkcja(double x)
{
	return exp(x);
}

double wielLag(double x,double n)
{

	if (n <= 0)
	{
		return 1;
	}else
	if (n == 1)
	{
		return x;
	}else

	return (1 / n)*(((2 * n)-1 )*x*wielLag(x, n-1) - (n-1)*wielLag(x, n - 2));
}
//ca³kowanie metod¹ trapezów-----------------
void tablicaXi(int a, int b, double* xTab, int n)
{
	for (int i = 0; i <= n; i++)
	{
		xTab[i] = a + ((double)i / n)*(b - a);
	}
}

/*double metodaTrapezow(double* xTab, double h, int n)
{
	double wynik = 0;
	for (int i = 0; i <= n; i++)
	{
		if (i == 0 && i == n)
		{
			wynik += (funkcja(xTab[i]) / 2);
		}
		else
		{
			wynik += funkcja(xTab[i]);
		}
	}
	wynik *= h;
	return wynik;
}*/
double metodaTrapezowCi(double* xTab, double h, int n,int k)
{
	double wynik = 0;
	for (int i = 0; i <= n; i++)
	{
		if (i == 0 && i == n)
		{
			wynik += ((funkcja(xTab[i])*wielLag(xTab[i],k)) / 2);
		}
		else
		{
			wynik += (funkcja(xTab[i])*wielLag(xTab[i], k));
		}
	}
	wynik *= h;
	cout <<"CI poch"<< wynik << endl;
	return wynik;

}
double metodaTrapezowFi(double* xTab, double h, int n, int k)
{
	double wynik = 0;
	for (int i = 0; i <= n; i++)
	{
		if (i == 0 && i == n)
		{
			wynik += ((pow(wielLag(xTab[i], k),2)) / 2);
		}
		else
		{
			wynik += ((pow(wielLag(xTab[i], k), 2)));
		}
	}
	wynik *= h;
	cout <<"FI"<< wynik << endl;
	return wynik;
}
//---------------------
double ci(double* xTab, double h, int n2, int i)
{
	double wynik = (1 / metodaTrapezowFi(xTab, h, n2, i))*metodaTrapezowCi(xTab, h, n2, i);
	cout << wynik << endl;
	return wynik;
}
double gX(double x, int n,double* xTab,double h,int n2)
{
	double wynik = 0;
	for (int i = 0; i < n; i++)
	{
		wynik += ci(xTab, h, n2, i)*wielLag(x,n);
	}
	return wynik ;
}

int main()
{
	double a = -1, b = 1;
	int n = 3, n2 = 1000;
	double h;
	h = ((double)b - a) / n2;
	double* xTab = new double[n2 + 1];
	tablicaXi(a, b, xTab, n2);

	cout<<gX(1, n, xTab, h, n2);
	_getch();

	return 0;
}