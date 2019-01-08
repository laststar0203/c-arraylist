#include <stdio.h>
#include "ArrayList.h"


int main(void) {

	ArrayList a = newArrayList(&a, FALSE, 10);
	int i = 3;

	al_add(&a, INT, 34);
	al_add(&a, FLOAT, 5.3422f);
	al_add(&a, LONG, 643434);
	al_add(&a, STRING, "HELLO");
	al_add(&a, CHAR, 'c');
	al_add(&a, REFERENCE, &i);
	printArray(&a);

	ArrayList b = newArrayList(&b, TRUE, &a);

	al_add(&b, INT, 45);
	al_remove(&b, 2);
	printArray(&b);

	printf("%s값의 위치는 %d에 위치해 있습니다\n",*(char**)al_get(&b , al_indexOf(&b , STRING , "HELLO")) , al_indexOf(&b, STRING, "HELLO"));
	printf("%s\n", al_contains(&a , INT , 34) == 1 ? "true" : "false");

	al_clear(&b);
	printf("%s값의 위치는 %d에 위치해 있습니다\n", al_get(&b, al_indexOf(&b, STRING, "HELLO")), al_indexOf(&b, STRING, "HELLO"));

	printArray(&b);

	system("pause");
}