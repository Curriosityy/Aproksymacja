// NajKwa.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"

// Interpolacjacpp.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//


// Eliminacja Gaussa
// Data: 15.02.2010
// (C)2012 mgr Jerzy Wa³aszek
//-----------------------------

#include <iostream>
#include <conio.h>
#include <cmath>
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
void tabDoGauss(double *Xi,double *Yi,double **AB,int m,int n)
{
	for (int i= 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double suma = 0;
			for (int k = 0; k < m; k++)
			{
				suma += pow(Xi[k], i + j);
			}
			AB[i][j] = suma;
		}
	}
	for (int i = 0; i < n;i++)
	{
		double tk = 0;
		for (int k = 0; k < m; k++)
		{
			tk += pow(Xi[k], i)*Yi[k];
		}
		AB[i][n] = tk;
	}

}
double oblicz(double x, double *Wyn,int n)
{
	double wynik = 0;
	for (int i = 0; i < n; i++)
	{
		wynik += pow(x, i)*Wyn[i];
	}
	return wynik;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	int n,m;
	double x;
	cout << "podaj n\n";
	cin >> n;
	cout << "podaj ilosc wezlow\n";
	cin >> m;
	cout << "podaj dla jakiego x\n";
	cin >> x;
	n += 1;
	double **AB = new double *[n];
	double *Wyn = new double[n];
	double *Xi = new double[m];
	double *Yi = new double[m];
	for (int i = 0; i < m; i++)
	{
		cin >> Xi[i] >> Yi[i];
	}

	for (int i = 0; i < n; i++)
		AB[i] = new double[n + 1];
	tabDoGauss(Xi, Yi, AB, m, n);
	gauss(n, AB, Wyn);
	for (int i = 0; i < n; i++)
	{
		cout << Wyn[i] <<endl;
	}
	cout << oblicz(x, Wyn, n);
	

	_getch();

	return 0;
}

