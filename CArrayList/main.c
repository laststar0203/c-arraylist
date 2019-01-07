#include <stdio.h>
#include "ArrayList.h"


int main(void) {

	ArrayList a = newArrayList(&a, FALSE, 10);

	add(&a, INT, 34);
	add(&a, FLOAT, 5.3422f);
	add(&a, LONG, 643434);
	add(&a, STRING, "HI");
	add(&a, CHAR, 'c');
	add(&a, REFERENCE, &a);
	printf("%p", &a);
	/*
	for (int i = 0; i < a.size; i++)
	{
		printf("%d", a.typeArr[i]);
	}
	toString(&a);
	*/



	system("pause");
}