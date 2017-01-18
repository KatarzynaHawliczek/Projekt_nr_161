/*
Projekt nr 161
18.01.2017 Katarzyna Hawliczek 15804
Program rysuje figurę znakiem ASCII i umożliwia przesuwanie, zmniejszanie oraz zwiększanie jej.
*/
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <string>

using namespace std;

const int x = 62;
const int y = 236;

int wczytajRozmiar(string komunikat, bool czyMiesciSieWOknie);
void czyt_dane(char A[x][y], char znak);
void gora(char A[x][y]);
void dol(char A[x][y]);
void lewo(char A[x][y]);
void prawo(char A[x][y]);
void zwieksz(char A[x][y], char &znak);
void zmniejsz(char A[x][y], char &znak);
void pisz_tab(char A[x][y]);
void menu();
bool czy_w_ramce(char A[x][y], char &znak);

int main()
{
	char A[x][y];
	char z, znak, ruch;
	bool koniec = false;
	bool rama = false;

	menu();

	cout << "Podaj znak: ";
	cin >> znak;

	czyt_dane(A, znak);
	pisz_tab(A);

	/*-----------------------Sterowanie figurą.--------------------------*/

	while (koniec == false)
	{
		z = _getch();

		switch (z)
		{
		case 72:       // Przesuwanie w górę.
		{
			gora(A);
			ruch = 'g';
		}
		break;
		case 80:       // Przesuwanie w dół.
		{
			dol(A);
			ruch = 'd';
		}
		break;
		case 75:       // Przesuwanie w lewo.
		{
			lewo(A);
			ruch = 'l';
		}
		break;
		case 77:       // Przesuwanie w prawo.
		{
			prawo(A);
			ruch = 'p';
		}
		break;
		case 43:       // Powiększanie.
		{
			zwieksz(A, znak);
			ruch = '+';
		}
		break;
		case 45:       // Pomniejszanie.    
		{
			zmniejsz(A, znak);
			ruch = '-';
		}
		break;
		case 27:
		{
			koniec = true;
		}
		break;
		}

		rama = czy_w_ramce(A, znak);
		if (rama == false)
		{
			system("cls");
			pisz_tab(A);
		}
		else
		{
			switch (ruch)
			{
			case 'g':
			{
				dol(A);
			}
			break;
			case 'd':
			{
				gora(A);
			}
			break;
			case 'l':
			{
				prawo(A);
			}
			break;
			case 'p':
			{
				lewo(A);
			}
			break;
			case '+':
			{
				zmniejsz(A, znak);
			}
			break;
			case '-':
			{
				zwieksz(A, znak);
			}
			break;
			}
		}		
	}
	/*---------------------------------------------------------------*/
	return 0;
}
void menu()  // Opis programu.
{
	cout << "Program rysuje figure znakiem ASCII." << endl;
	cout << "------------------------------------" << endl;
	cout << "Sterowanie: " << endl << endl;
	cout << "\"Strzalka w prawo\" - w prawo" << endl;
	cout << "\"Strzalka w lewo\"  - w lewo" << endl;
	cout << "\"Strzalka w gore\"  - do gory" << endl;
	cout << "\"Strzalka w dol\"   - na dol" << endl;
	cout << "\"+\"                - powieksz" << endl;
	cout << "\"-\"                - pomniejsz" << endl;
	cout << "\"Esc\"              - wyjscie" << endl;
	cout << "------------------------------------";

	_getch();
	system("cls");
}
int wczytajRozmiar(string komunikat, bool czyMiesciSieWOknie)   // Walidacja rozmiaru.
{
	int rozmiar;

	cout << komunikat;
	cin >> rozmiar;

	while (cin.fail() || (czyMiesciSieWOknie && (rozmiar >= 31 || rozmiar <= 0)))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Figura nie zmiesci sie w oknie!." << endl;
		cout << komunikat << endl;
		cin >> rozmiar;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return rozmiar;
}
void czyt_dane(char A[x][y], char znak)   // Wczytanie rozmiaru i wypełnienie tablicy.
{
	int i, j, r;

	r = wczytajRozmiar("Podaj rozmiar figury: ", true);

	system("cls");

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			A[i][j] = NULL;
		}
	}

	for (i = 31, j = 118; i >= 32 - r, j >= 119 - r; i--, j--)
	{
		A[i][j] = znak;
	}

	for (i = 31, j = 118; i <= 30 + r, j >= 119 - r; i++, j--)
	{
		A[i][j] = znak;
	}
}
void gora(char A[x][y])		// Przesuwanie w górę.
{
	int i, j;

	for (i = 0; i < x - 1; i++)
	{
		for (j = 0; j < y; j++)
		{
			A[i][j] = A[i + 1][j];
			A[x - 1][j] = NULL;
		}
	}
}
void dol(char A[x][y])		// Przesuwanie w dół.
{
	int i, j;

	for (i = x - 1; i > 0; i--)
	{
		for (j = y - 1; j >= 0; j--)
		{
			A[i][j] = A[i - 1][j];
			A[0][j] = NULL;
		}
	}
}
void lewo(char A[x][y])		// Przesuwanie w lewo.
{
	int i, j;

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y - 1; j++)
		{
			A[i][j] = A[i][j + 1];
			A[i][y - 1] = NULL;
		}
	}
}
void prawo(char A[x][y])		// Przesuwanie w prawo.
{
	int i, j;

	for (i = x - 1; i >= 0; i--)
	{
		for (j = y - 1; j > 0; j--)
		{
			A[i][j] = A[i][j - 1];
			A[i][0] = NULL;
		}
	}
}
void zwieksz(char A[x][y], char &znak)		// Powiększanie.
{
	int i, j;

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			if ((A[i + 1][j + 1] == znak) && (A[i + 2][j + 2] == znak))
			{
				A[i][j] = znak;
			}
		}
	}
	for (i = x - 1; i >= 0; i--)
	{
		for (j = 0; j < y; j++)
		{
			if ((A[i - 1][j + 1] == znak) && (A[i - 2][j + 2] == znak))
			{
				A[i][j] = znak;
			}
		}
	}
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			if ((A[i][j] == znak) && (A[i - 1][j - 1] != znak) && (A[i + 1][j - 1] != znak) && (A[i - 1][j + 1] != znak) && (A[i + 1][j + 1] != znak))
			{
				A[i - 1][j - 1] = znak;
				A[i + 1][j - 1] = znak;
			}
		}
	}
}
void zmniejsz(char A[x][y], char &znak)		// Pomniejszanie.
{
	int i, j;
	bool zmniejsz1 = false, zmniejsz2 = false;

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			if ((A[i][j] == znak) && (A[i + 1][j + 1] == znak))
			{
				A[i][j] = NULL;
				zmniejsz1 = true;
			}
			if (zmniejsz1 == true)
			{
				break;
			}
		}
	}
	zmniejsz1 = false;
	for (i = x - 1; i >= 0; i--)
	{
		for (j = 0; j < y; j++)
		{
			if ((A[i][j] == znak) && (A[i - 1][j + 1] == znak))
			{
				A[i][j] = NULL;
				zmniejsz2 = true;
			}
			if (zmniejsz2 == true)
			{
				break;
			}
		}
	}
	zmniejsz2 = false;
}
void pisz_tab(char A[x][y])   // Wypisanie tablicy ( rysowanie figury ).
{
	int i, j;

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < y; j++)
		{
			cout << A[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
bool czy_w_ramce(char A[x][y], char &znak)   // Sprawdzenie, czy figura nie wychodzi poza ramkę. 
{
	int i, j;
	bool ramka = false;

	for (i = 1; i < x - 1; i++)
	{
		if (A[i][1] == znak || A[i][y - 2] == znak)
		{
			ramka = true;
		}
	}
	for (j = 1; j < y - 1; j++)
	{
		if (A[1][j] == znak || A[x - 2][j] == znak)
		{
			ramka = true;
		}

	}
	return ramka;
}
