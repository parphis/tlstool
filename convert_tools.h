#ifndef	CONVERTTOOLSH
#define	CONVERTTOOLSH

int char_to_int(char c);
int int_to_char(int i);
void int_to_bin(int i, int *bin, int cnt);
int bin_to_int(int *bin, int cnt);
void char_to_bin(char c, int *bin, int cnt);
char bin_to_char(int *bin, int cnt);

#endif