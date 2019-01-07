#pragma once

#include <stdlib.h>
#include <stdarg.h>

#define DEFAULT_SIZE 10;


enum Type { NONE = 0 , CHAR , INT , LONG , FLOAT , DOUBLE , STRING , REFERENCE};

enum Bool {FALSE , TRUE};

typedef struct arrayList
{

	int capacity;
	int size;
	void** box;
	enum Type* typeArr; //c는 반드시 앞에 enum 키워드를 붙여주어야함

}ArrayList;
//구조체 안에서에 초기화는 적용되지 않는다

ArrayList newArrayList(ArrayList* arr , enum Bool isCopy, ...);
void add(ArrayList* list, enum Type type, ...);
void* get(ArrayList* list, int index);
void clear(ArrayList* list);
int length(ArrayList* list);
int isEmpty(ArrayList* list);
void allRemove(ArrayList* list);
void remove(ArrayList* list, int index);



ArrayList newArrayList(ArrayList* arr, enum Bool isCopy, ...) { //들어오는 가변인자 타입들이 다를경우 고정인자를 통해 구별해 줘야 한다.

	va_list ap;
	va_start(ap, isCopy); //bool

	switch (isCopy)
	{
		case FALSE:
		{
			int size = va_arg(ap, int);
			arr->size = 0;

			if ((arr->capacity = size) <= 0) {
				arr->box = (void**)malloc(sizeof(void*) * 10);
				arr->typeArr = (enum Type*)malloc(sizeof(enum Type) * 10);

			}
			else {
				arr->box = (void**)malloc(sizeof(void*) * size);
				arr->typeArr = (enum Type*)malloc(sizeof(enum Type) * size);
			}
		}
		break;

		case TRUE: {
			ArrayList* copy = va_arg(ap, ArrayList*);
			arr = copy;
		}
			break;

	default:
		break;
	}


	return *arr;
}

void add(ArrayList* list , enum Type type, ...) {

	va_list ap;
	va_start(ap,  type); //type 뒤에서부터 가변인자가 시작된다는 말임


	

	int pos = list->size;

	if (pos >= list->capacity) {
		list->box = (void**)realloc(list->box, sizeof(void*) * list->size * 2);
		list->typeArr = (enum Type*)realloc(list->box, sizeof(enum Type) * list->size * 2);
		list->size *= 2;
	}

	
	
#pragma region InputByType

	switch (type)
	{
	case CHAR:
	{
		char* ap_char = (char*)malloc(sizeof(char));
		*ap_char = va_arg(ap, char);
		list->box[pos] = ap_char;
		list->typeArr[pos] = CHAR;

		break;
	}
	case INT:
	{

		int* ap_int = (int*)malloc(sizeof(int));
		*ap_int = va_arg(ap, int);
		list->box[pos] = ap_int;
		list->typeArr[pos] = INT;
		break;
	}
	case LONG:

	{
		long* ap_long = (long*)malloc(sizeof(long));
		*ap_long = va_arg(ap, long);
		list->box[pos] = ap_long;
		list->typeArr[pos] = LONG;

		break;
	}
	case FLOAT:
	{
		float* ap_float = (float*)malloc(sizeof(float));
		*ap_float = va_arg(ap, float);
		//printf("%f", *ap_float);
		list->box[pos] = ap_float;
		list->typeArr[pos] = FLOAT;

		break;
	}
	case DOUBLE:
	{
		double* ap_double = (double*)malloc(sizeof(double));
		*ap_double = va_arg(ap, double);
		list->box[pos] = ap_double;
		list->typeArr[pos] = DOUBLE;

		break;
	}
	case STRING:
	{
		char** ap_str = (char**)malloc(sizeof(char*));
		*ap_str = va_arg(ap, char*);
		list->box[pos] = ap_str;
		list->typeArr[pos] = STRING;
	}
	case REFERENCE:
	{ 
		list->box[pos] = va_arg(ap, void*);
		printf("%p\n", list->box[pos]);
		list->typeArr[pos] = REFERENCE;
	}
	default:
		break;
	}
#pragma endregion

	list->size++;
}



void* get(ArrayList* list, int index) {
	if (index < 0 || index > sizeof - 1) return NULL;

	void *value = list->box[index];
	

	return value;

}

void clear(ArrayList* list) {
	for (int i = 0; i < list->size; i++)
	{
		list->box[i] = NULL;
		list->typeArr[i] = NONE;
	}
	list->size = 0;
}

void remove(ArrayList* list, int index) {

	
		int lth = length(list);

		for (int i = index ; i < lth-1; i++) {		
			list->box[i] = list->box[i + 1];
			list->typeArr[i] = list->typeArr[i + 1];
		}
		free(list->box[lth - 1]);
		free((void*)list->typeArr[lth - 1]);

		list->size--;
}

void allRemove(ArrayList* list) {

	for (int i = 0; i < list->size; i++)
	{
		free(list->box[i]);
		free((void*)list->typeArr[i]);
	}
	free(list);

	list->size = 0;
}


void toString(ArrayList* list) {

	printf("[");
	for (int i = 0; i < list->size; i++) {
		switch (list->typeArr[i])
		{
		case CHAR:
			printf("%c,", *(char*)list->box[i]);
			break;
		case INT:
			printf("%d,", *(int*)list->box[i]);
			break;
		case LONG:
			printf("%d,", *(long*)list->box[i]);
			break;
		case FLOAT:
			printf("%f,", *(float*)list->box[i]);
			break;
		case DOUBLE:
			printf("%f,", *(double*)list->box[i]);
			break;
		case STRING:
			printf("%s,", *(char**)list->box[i]);
			break;
		case REFERENCE:
			printf("%p,", list->box[i]);
			break;
		default:
			printf("NULL,");
			break;
		}
	}

	printf("]");
}

int length(ArrayList* list) { return list->size; }
int isEmpty(ArrayList* list) { return list->size == 0; }










