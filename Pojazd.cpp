#include <iostream>
#include <vector>
#include "Pojazd.h"
#include <string>
#include <locale.h>

Pojazd::Pojazd()
{
	// Tu siê zapytaj czy jest coœ lepszego ni¿: setlocale(LC_CTYPE, "POLISH");
	setlocale(LC_CTYPE, "Polish");

	std::cout << "Podaj wielkoœc planszy: ";
	std::cin >> n;
	
	system("cls");

	int k = n - 1;
	tab = new std::string[n];

	for (int i = 0; i < n; ++i)
	{
		tab[i].resize(n);
	}

	for (int i = 0; i < n; ++i)
	{
		tab[i][k] = '#';
		tab[k][i] = '#';
		tab[0][i] = '#';
		tab[i][0] = '#';
	}
	for (int i = 1; i < k; ++i)
	{
		for (int j = 1; j < k; ++j)
		{
			tab[i][j] = ' ';
		}
	}
	P = new pozycja;

	P->x = n / 2;
	P->y = n / 2;
}

Pojazd::~Pojazd()
{
	
	setlocale(LC_CTYPE, "POLISH");
	std::cout << "Twoja liczba pónktów to: "<<pkt;
	delete [] tab;
	delete P;
	delete xx, yy;
}

void Pojazd::wyswietlanie()
{
	tab[P->x][P->y] = 'W';

	for (std::vector<pozycja>::iterator it = S.begin(); it < S.end(); it++)
	{
		tab[it->x][it->y] = 's';
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << tab[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Pojazd::zamiana(int &x, int &y)
{
	// Tu siê zapytaj czy jest sens bawienia siê wskaŸnikami (xx i yy) 
	//Czy ju¿ lepiej operwoaæ wartoœciami struktury P, która jest wskaŸnikiem za pomoc¹ "->"

	*xx = P->x;
	*yy = P->y;
	*xx += x;
	*yy += y;

	if (*xx == n-1  || *xx == 0) *xx -= x;
 
	if (*yy == n - 2 || *yy == 0) *yy -= y;
	
	x = 0;
	y = 0;

	zamiana_w();

	zamiana_pw();

	zamiana_p();

	if (tab[*xx][*yy] == '!')
	{
		int j = 0;

		while (*xx!= W[j].x && *yy != W[j].y) j++;

		tab[W[j].x][W[j].y] = ' ';
		W.erase(W.begin() + j);
		hp--;
		
	}
	else if (tab[*xx][*yy] == 'v')
	{
		int j = 0;

		while (*xx != Wr[j].x && *yy != Wr[j].y) j++;

		tab[W[j].x][W[j].y] = ' ';
		Wr.erase(Wr.begin() + j);
		hp--;
	}

	P->x = *xx;
	P->y = *yy;
}

void Pojazd::pocisk()
{
	if (strzaly > 0)
	{
		S.push_back({ P->x , P->y });
		strzaly--;
	}
	
}

void Pojazd::wrog()
{
	if (Wr.size() < 5)
	{
		int k = n - 3;
		int n_0 = n / 2;
		int a = 0;
		int x = 0;
		int y = 0;
		if (rand() % 4 == 0) a = 1;

		else a = -1;

		while (tab[x][y] != ' ')
		{
			x = rand() % n_0 + 1;
			y = rand() % k + 1;
		}

		Wr.push_back({ x,y,a });
	}
}

void Pojazd::czyszczenie()
{
	for (int i = 1; i < n-1; ++i)
	{
		for (int j = 1; j < n-1; ++j)
		{
			tab[i][j] = ' ';
		}
	}
}

void Pojazd::menu()
{
	
	setlocale(LC_CTYPE, "POLISH");
	std::cout << "----------------------------\n"
		<< " W lewo: A     W prawo: D\n"
		<< " Do góry: W     W dó³: S\n"
		<< " Strza³: Spacja    ¯ycia: " << hp
		<< "\n Punkty: " << pkt << "     Strza³y: " << strzaly
	    << "\n----------------------------\n";
}

void Pojazd::zamiana_w()
{
	for (std::vector<pozycja_W>::iterator it = Wr.begin(); it < Wr.end(); it++)
	{
		if (it->y == n - 2)
		{
			it->y = 1;
		}
			
		else if (it->y == 1)
		{
			it->y = n - 2;
		}
			
		it->y += it->a;

		if (tab[it->x][it->y] != ' ')
		{
			it->a = -it->a;
			it->y += it->a;
		}
		else
		{
			tab[it->x][it->y] = 'v';
		}
	}
}

void Pojazd::pocisk_w()
{
	for (std::vector<pozycja_W>::iterator it = Wr.begin(); it < Wr.end(); it++)
	{
		W.push_back({ it->x , it->y});
	}
}

void Pojazd::zamiana_p()
{
	int it = S.size();

	for (int i = 0; i < it; i++)
	{

		if (tab[S[i].x][S[i].y] == '!')
		{
			int j = 0;

			while (S[i].x != W[j].x && S[i].y != W[j].y) j++;

			S.erase(S.begin() + i);
			tab[W[j].x][W[j].y] = ' ';
			W.erase(W.begin() + j);
			it--;
			continue;
		}

		else if (tab[S[i].x][S[i].y] == 'v')
		{
			int j = 0;

			while (S[i].x != Wr[j].x && S[i].y != Wr[j].y) j++;

			S.erase(S.begin() + i);
			tab[Wr[j].x][Wr[j].y] = ' ';
			Wr.erase(Wr.begin() + j);
			it--;
			pkt++;
			continue;

		}

		S[i].x--;

		if (tab[S[i].x][S[i].y] == '!')
		{
			int j = 0;
			while (S[i].x != W[j].x && S[i].y != W[j].y) j++;

			S.erase(S.begin() + i);
			tab[W[j].x][W[j].y] = ' ';

			W.erase(W.begin() + j);
			it--;
			pkt++;
			continue;
		}

		else if (tab[S[i].x][S[i].y] == 'v')
		{
			int j = 0;

			while (S[i].x != Wr[j].x && S[i].y != Wr[j].y) j++;

			S.erase(S.begin() + i);
			tab[Wr[j].x][Wr[j].y] = ' ';
			Wr.erase(Wr.begin() + j);
			it--;
			pkt++;
			strzaly = strzaly + 5;
			continue;
		}
		else if (S[i].x < 1)
		{
			S.erase(S.begin() + i);
			it--;
		}
	}
}

void Pojazd::zamiana_pw()
{
	int it = W.size();

	for (int i = 0; i < it; i++)
	{
		if (tab[W[i].x][W[i].y] == 'v')
		{
			W.erase(W.begin() + i);
			it--;
			continue;
		}

		W[i].x++;

		if (tab[W[i].x][W[i].y] == 'v')
		{
			W.erase(W.begin() + i);
			it--;
			continue;
		}
		else if (W[i].x > n - 2)
		{

			W.erase(W.begin() + i);
			it--;
		}
		else
		{
			tab[W[i].x][W[i].y] = '!';
		}
	}
}