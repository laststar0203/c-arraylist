#pragma once

#include <stdlib.h>
#include <stdarg.h>
#define DEFAULT_SIZE 10;

enum Type { CHAR = 0, INT, LONG, FLOAT, DOUBLE, STRING };

Type type;

int size = DEFAULT_SIZE;
int pos = 0;
static void** arr;
static int* sizeArr;

void** create(int size);
void add(void* value);
void addArg(int size, void* ptr);


void** create(int size) {

	arr = (void**)malloc(sizeof(void*) * size);
	sizeArr = (int*)malloc(sizeof(int) * size);

	return arr;
}
void add(int usage, ...) {

	va_list ap;

#pragma region InputByType

	switch (type)
	{
	case CHAR:
		char *p_char;
		p_char = (char*)malloc(sizeof(char));

		*p_char = va_arg(ap, char);

		addArg(CHAR, p_char);

		break;
	case INT:
		int *p_int;

		p_int = (int*)malloc(sizeof(int));

		*p_int = va_arg(ap, int);

		addArg(INT, p_int);
		break;
	case LONG:
		long *p_long;

		p_long = (long*)malloc(sizeof(long));

		*p_long = va_arg(ap, long);

		addArg(LONG, p_long);

		break;
	case FLOAT:
		float *p_float;

		p_float = (float*)malloc(sizeof(float));

		*p_long = va_arg(ap, float);

		addArg(FLOAT, p_float);

		break;
	case DOUBLE:
		double *p_double;

		p_double = (double*)malloc(sizeof(double));

		*p_double = va_arg(ap, double);

		addArg(DOUBLE, p_double);
		break;
	case STRING:
		char** p_str;
		p_str = (char**)malloc(sizeof(char*));

		*p_str = va_arg(ap, char*);

		addArg(STRING, *p_str);
	default:
		break;
	}
#pragma endregion

}

void get(int index) {

	if (index < 0 || index > size - 1) 

	int size = sizeArr[index];	

}

void addArg(int size, void* ptr) {

	if (pos >= size) {
		arr = (void**)realloc(arr, sizeof(void*) * size * 2);
		sizeArr = (int*)realloc(arr, sizeof(int) * size * 2);
		size *= 2;
	}

	sizeArr[pos] = size;
	arr[pos] = ptr;
	pos++;

}


