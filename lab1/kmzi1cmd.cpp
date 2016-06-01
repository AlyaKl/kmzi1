// kmzi1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <ctype.h>
#include <fstream>
//#include "conio.h"
//#include "windows.h"


using namespace std;
using std::cout;
using std::cin;
using std::endl;



string intext(string textname, string &text) {
	ifstream fin;
	fin.open(textname.c_str());

	if (!fin.is_open())
	{          //Если есть ошибка чтения
		cout << "Error reading file data" << endl;  //Уведомим
        //getchar();
		return 0;
	}
	int i = 0;
	string t = "";
   // fin>>text;
   //
    while (!fin.eof())
	{
		fin >> t;
        text = text + " " + t;
    }
    fin.close();
	//cout << text << endl;
return (text);
}

string incrack(string crackname, string &crack)
{
	ifstream fin;
	fin.open(crackname.c_str());

	if (!fin.is_open())
	{          //Если есть ошибка чтения
		cout << "Error reading file data" << endl;  //Уведомим
		getchar();
		return 0;
	}
	int i = 0;
	string t = "";
    fin>>crack;
    fin.close();
    /*while (!fin.eof())
	{
		fin >> t;
        crack = crack + " " + t;
    }*/
	//cout << crack << endl;
	return (crack);
}

string Shifr(string &text, string &A, string d)
{
	int x;
	int y;
	string hshifr = "";
	for (int i = 0; i < text.size(); i++)
	{
		x = -1;
		y = -1;
		for (int j = 0; j < A.size(); j++)
		{
			if (text[i] == A[j])
				x = j;
			if (d[i] == A[j])
				y = j;
		}
		if (x != -1 && y != -1)
			hshifr = hshifr + A[(x + y) % 26];
		else
			hshifr = hshifr + text[i];
    }
	return (hshifr);
}

string key(int &t, int &c, string &crack)
{
	string d;
	if (t >= c)
	{
		for (int i = 0; i < (t / c); i++)
		{
			d = d + crack;		//целое количество
		}
		for (int j = 0; j < (t % c); j++)
		{
			d = d + crack[j];
		}
	}
	else
	{
		for (int i = 0; i < t; i++)
		{
			d = d + crack[i];
		}
	}
	//cout << d << endl; //расскомментить для показа, как подогнан ключ
	return(d);
}


string Dshifr(string &text, string &A, string d)
{
	int x;
	int y;
	string dshifr = "";
	for (int i = 0; i < text.size(); i++)
	{
		x = -1;
		y = -1;
		for (int j = 0; j < A.size(); j++)
		{
			if (text[i] == A[j])
				x = j;
			if (d[i] == A[j])
				y = j;
		}
		int p = x - y;

		if (p < 0)
		{
			p = 26 + (x - y);
		}

		if (x != -1 && y != -1)
			dshifr = dshifr + A[p];
		else
			dshifr = dshifr + text[i];
	}
	return (dshifr);
}



int main(int argc, char *argv[])
{
	string text = "", crack = "", d = "";
	string A = "abcdefghijklmnopqrstuvwxyz";
	setlocale(LC_ALL, "Rus");
	string textname = "";
	string crackname = "";
	string shifr = "";

	
	int cmd = 0;
int e=2;
	while ((cmd = getopt(argc, argv, "t:k:ed")) != -1)
	{
		switch (cmd)
		{
		case 't':
			textname = optarg;
			intext(textname, text); //ввод исходного текста
			break;
		case 'k':
			crackname = optarg;
			incrack(crackname, crack); //ввод key
			break;
        case 'e': //шифровкa
        e = 1;
        break;

        case 'd': //deшифровка
           e = 0;
           break;
		}

	}
if (e == 2)
{
        cout <<"neverny vvod argumentov"<< endl;
        exit (0);
}

cerr << "текст: " << text << endl;
cerr << "crack: " << crack << endl;
int c = crack.size();
int t = text.size();
d = key(t, c, crack);   //подгон ключа
cerr << "podg key: " << d << endl;

if(e == 1)
{ 
  //freopen ("myfile.txt","w",stdout);
  shifr = Shifr(text, A, d);
  cout << shifr << endl;
  //fclose (stdout);
}
if (e == 0)
{
shifr = Dshifr(text, A, d);
cout << shifr << endl;
}
			

//getchar();
//getchar();

return 0;
}
