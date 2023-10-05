#include <vector>
#include <string>
#ifndef POJAZD_H
#define POJAZD_H

struct pozycja
{

	int x = 0;
	int y = 0;
};

struct pozycja_W 
{
	int x = 0;
	int y = 0;
	int a = 1;
};


class Pojazd 
{
public:
	int hp = 3;
	int i = 0;
private:
	int* xx = new int;
	int* yy = new int;
	
	int n = 0;
	
	int pkt = 0;
	int strzaly = 20;
	pozycja *P = nullptr;
	std::vector<pozycja> S;
	std::vector<pozycja_W> Wr;
	std::vector<pozycja> W;
	std::string* tab;

	//methods
public:
	Pojazd();

	void wyswietlanie();
	void zamiana(int& x, int& y);
	void wrog();
	void czyszczenie();
	void pocisk();
	void zamiana_p();
	void zamiana_pw();
	void zamiana_w();
	void pocisk_w();
	void menu();

	~Pojazd();
};

#endif