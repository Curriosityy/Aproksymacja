

// Eliminacja Gaussa
// Data: 15.02.2010
// (C)2012 mgr Jerzy Wa³aszek
//-----------------------------

#include <iostream>
#include <conio.h>
#include <cmath>
#include <math.h>
using namespace std;

const double eps = 1e-12; // sta³a przybli¿enia zera

// Funkcja realizuje algorytm eliminacji Gaussa
//---------------------------------------------
bool gauss(int n, double ** AB, double * X)
{

	int i, j, k;
	double m, s;

	// eliminacja wspó³czynników

	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (fabs(AB[i][i]) < eps) return false;
			m = -AB[j][i] / AB[i][i];
			for (k = i + 1; k <= n; k++)
				AB[j][k] += m * AB[i][k];
		}
	}

	// wyliczanie niewiadomych

	for (i = n - 1; i >= 0; i--)
	{
		s = AB[i][n];
		for (j = n - 1; j >= i + 1; j--)
			s -= AB[i][j] * X[j];
		if (fabs(AB[i][i]) < eps) return false;
		X[i] = s / AB[i][i];
	}
	return true;
}
//------------------------------------------------------------//

double funkcja(double x)
{
	return pow(x,2)+(3*x);
}
double wielomian(double x, int n, double* TabA)
{
	double wynik = 0;
	for (int i = 0; i < n; i++)
	{
		wynik += (pow(x, i)*TabA[i]);
	}
	return wynik;
}
double jednomian(int i, double x)
{
	return pow(x, i);
}


void tablicaXi(int a, int b, double* xTab, int n)
{
	for (int i = 0; i <= n; i++)
	{
		xTab[i] = a + ((double)i / n)*(b - a);
	}
}
//--------------------calkowanie numeryczne metoda trapezów
double metodaTrapezowAij(double* xTab, double h, int n, int k,int l)
{
	double wynik = 0;
	for (int i = 0; i <= n; i++)
	{
		if (i == 0 && i == n)
		{
			wynik += ((jednomian(k, xTab[i])*jednomian(l, xTab[i])) / 2);
		}
		else
		{
			wynik += (jednomian(k, xTab[i])*jednomian(l, xTab[i]));
		}
	}
	wynik *= h;
	return wynik;
}
double metodaTrapezowBi(double* xTab, double h, int n, int k)
{
	double wynik = 0;
	for (int i = 0; i <= n; i++)
	{
		if (i == 0 && i == n)
		{
			wynik += ((jednomian(k, xTab[i])*funkcja(xTab[i])) / 2);
		}
		else
		{
			wynik += ((jednomian(k, xTab[i])*funkcja(xTab[i])));
		}
	}
	wynik *= h;
	return wynik;
}
//----------Aproksymacja ŚredniaKwadratowa ciągła


void tabDoGaussa(double** AB,int n, double* xTab, double h, int n2)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			AB[i][j] = metodaTrapezowAij(xTab, h, n2, i,j);
		}
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		AB[i][n] =	metodaTrapezowBi(xTab,h,n2,i);
	}

}

int main()
{
	double a = 2.5, b = 4;
	int n=3,n2=10000;
	double h = ((double)b - a) / (n2*1.0);
	double* xTab = new double[n2 + 1];
	tablicaXi(a, b, xTab, n2);

	double **AB = new double *[n];
	for (int i = 0; i < n; i++)
		AB[i] = new double[n + 1];

	double *X = new double[n];
	tabDoGaussa(AB, n, xTab, h, n2);
	gauss(n, AB, X);
	for(int i =0;i<n;i++)
	{
		cout << X[i]<<" ";
	}
	cout << endl;
	cout << wielomian(2, n, X);
	_getch();
	return 0;
}