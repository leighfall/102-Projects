//Autumn Henderson
//CS 130
//January 17th, 2019
//Mini Lab 2
//This program defines functions Set, Clear, and Test for use with bits

#include<cstdio>

int Set(int original_number, int bit_index);
int Clear(int original_number, int bit_index);
int Test(int number, int bit_index);

int main() {
	int i = 0;
	i = Set(i, 0);
	printf("%d\n", i);

	i = Set(i, 3);
	printf("%d\n", i);

	i = Clear(i,0);
	printf("%d\n", i);
	printf("%d\n", Test(i, 0));
	printf("%d\n", Test(i, 3));

	return 0;
}

int Set(int original_number, int bit_index) {
	return original_number | (1 << bit_index);
}

int Clear(int original_number, int bit_index) {
	return original_number & ~(1 << bit_index);
}

int Test(int number, int bit_index) {
	return (number >> bit_index) & 1;
}
