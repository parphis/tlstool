#include <iostream>
using namespace std;
#include <cstring>
#include <cstdlib>
#include <math.h>

#include "convert_tools.h"

int char_to_int(char c)
{
	unsigned int i = (int)c;

	switch (i)
	{
		case 48: return 0;
		case 49: return 1;
		case 50: return 2;
		case 51: return 3;
		case 52: return 4;
		case 53: return 5;
		case 54: return 6;
		case 55: return 7;
		case 56: return 8;
		case 57: return 9;
		case 65: return 10;
		case 66: return 11;
		case 67: return 12;
		case 68: return 13;
		case 69: return 14;
		case 70: return 15;
		default: return -1;
	}
}
int int_to_char(int i)
{
	switch (i)
	{
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'A';
		case 11: return 'B';
		case 12: return 'C';
		case 13: return 'D';
		case 14: return 'E';
		case 15: return 'F';
		default: return '\0';
	}
}
void int_to_bin(int i, int *bin, int cnt)
{
	int t = 0;

	while (t<cnt)
	{
		if((i%2)==0)
		{
			bin[t] = 0;
			i = i/2;
		}
		else
		{
			bin[t] = 1;
			i = i/2;
		}
    	t++;
	}
}
int bin_to_int(int *bin, int cnt)
{
	int r = 0;

	for (int i=0; i < cnt; i++)
		r += bin[i]*(pow(2,i));

	return r;
}

void char_to_bin(char c, int *bin, int cnt)
{
	int r;

	r = char_to_int(c);

	int_to_bin(r, bin, cnt);
}

char bin_to_char(int *bin, int cnt)
{
	char r;

	r = (char)bin_to_int(bin, cnt);

	return r;
}