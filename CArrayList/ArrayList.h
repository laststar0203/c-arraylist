#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

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

#pragma region Functions

ArrayList newArrayList(ArrayList* arr , enum Bool isCopy, ...);
/*
newArrayList(사용할 ArrayList 주소 , 복사 여부 , 크기 or 복사할 ArrayList)

ArrayList 생성자 같은 역할
넘겨받은 arrayList구조체에 메모리를 할당
복사여부에 따라 true 이면 세번째 인자에 들어간 arrayList를 사용할 arrayList에 복사
false이면 세번째 인자에는 int값이 들어가며 크기를 설정

*/
void al_add(ArrayList* list, enum Type type, ...);
/*
al_add(사용할 ArrayList 주소, 타입 , 값)

넘겨 받은 ArrayList에 타입에 맞춰 값을 저장

*/
void* al_get(ArrayList* list, int index);
/*
al_get(사용할 ArrayList 주소 , 인덱스)

인덱스에 위치한 값을 (void*)타입으로 리턴 인덱스가 범위를 벗어났을경우
Null을 리턴
(현재 실수형 자료는 알수없는 오류로 잘못된 값이 리턴됨..)

*/
void al_clear(ArrayList* list);
/*
al_clear(사용할 ArrayList 주소)

ArrayList에 저장되어 있는 값을 모두 비움(메모리는 지우지 않음)

*/
int al_size(ArrayList* list);
/*
al_size(사용할 ArrayList 주소)

ArrayList에 저장된 값의 개수를 리턴

*/
int al_isEmpty(ArrayList* list);
/*
al_isEmpty(사용할 ArrayList 주소);

ArrayList가 모두 비어있는지 확인 비어있다면 true를 리턴

*/
void al_allRemove(ArrayList* list);
/*
al_allRemove(사용할 ArrayList 주소);

ArrayList 모두 삭제(메모리 포함)

*/
void al_remove(ArrayList* list, int index);
/*
al_remove(사용할 ArrayList 주소);

넘겨받은 인덱스에 위치한 값을 삭제(메모리 포함)

*/
void printArray(ArrayList* list);
/*
al_printArray(사용할 ArrayList 주소);

ArrayList에 저장되어 있는 값들을 출력

*/
int al_indexOf(ArrayList* list, enum Type type, ...);
/*
al_printArray(사용할 ArrayList 주소 , 타입, 값);

넘겨 받은 타입과 맞는 값의 인덱스 값을 리턴 없다면 -1를 리턴

*/
int al_contains(ArrayList* list, enum Type type, ...);
/*
al_printArray(사용할 ArrayList 주소 , 타입, 값);

넘겨 받은 타입과 맞는 값이 존재하는지 확인하는 함수
존재하면 true를 리턴

*/

#pragma endregion


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

void al_add(ArrayList* list , enum Type type, ...) {

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
		break;
	}
	case REFERENCE:
	{ 
		list->box[pos] = va_arg(ap, void*);
		list->typeArr[pos] = REFERENCE;
	}
	default:
		break;
	}
#pragma endregion

	list->size++;
}



void* al_get(ArrayList* list, int index) {
	if (index < 0 || index > list->size - 1) 
		return NULL;

	

	void *value = list->box[index];


	return value;

}

void al_clear(ArrayList* list) {
	for (int i = 0; i < list->size; i++)
	{
		list->box[i] = NULL;
		list->typeArr[i] = NONE;
	}
	list->size = 0;
}

void al_remove(ArrayList* list, int index) {

	
	int lth = al_size(list);

	for (int i = index ; i < lth-1; i++) {		
		list->box[i] = list->box[i + 1];
		list->typeArr[i] = list->typeArr[i + 1];

	}
	list->box[lth-1] = NULL;
	free(list->box[lth - 1]);	
	//free((void*)(list->typeArr+(lth-1))); 계속 오류가 뜬다 도대체 뭐가 문제인지 모르겠다 어차피 이거 안되도 size값이 줄어들어 접근을 못하기때문에 상관 X

	list->size--;
}

void al_allRemove(ArrayList* list) {

	for (int i = 0; i < list->size; i++)
	{
		list->box[i] = NULL;
		free(list->box[i]);
		//free(&list->typeArr[i]); //위와 동일
	}
	free(list);

	list->size = 0;
}


void printArray(ArrayList* list) {

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
			printf("%p(%dByte),", list->box[i],sizeof(list->box[i]));
			break;
		default:
			printf("NULL,");
			break;
		}
	}

	printf("]\n");
}

int al_indexOf(ArrayList* list, enum Type type, ...) {

	va_list ap;
	va_start(ap, type);

    const int size = list->size;
	int index = 0;
	for (index = 0; index < size; index++) {
	
		if (list->typeArr[index] == type) {


			switch (type)
			{
			case CHAR:
				if (*(char*)list->box[index] == va_arg(ap, char))
					goto result;
				break;
			case INT:
				if (*(int*)list->box[index] == va_arg(ap, int))
					goto result;
				break;
			case LONG:
				if (*(long*)list->box[index] == va_arg(ap, long))
					goto result;
				break;
			case FLOAT:
				if (*(float*)list->box[index] == va_arg(ap, float))
					goto result;
				break;
			case DOUBLE:
				if (*(double*)list->box[index] == va_arg(ap, double))
					goto result;
				break;
			case STRING:
				if (strcmp(*(char**)list->box[index], va_arg(ap, char*)) == 0)
					goto result;
				break;
			case REFERENCE:
				if (list->box[index] == va_arg(ap, void*))
					goto result;
				break;
			default:
				break;
			}

		}
	}

result:
	if (index == size) {
		return -1;
	}
	else {
		return index;
	}
	}

int al_contains(ArrayList* list, enum Type type, ...) { 
	
	va_list ap;
	va_start(ap, type);

	switch (type)
	{
	case CHAR:
		return al_indexOf(list, type, va_arg(ap, char)) != -1 ? 1 : 0;
		break;
	case INT:
		return al_indexOf(list, type, va_arg(ap, int)) != -1 ? 1 : 0;
		break;
	case LONG:
		return al_indexOf(list, type, va_arg(ap, long)) != -1 ? 1 : 0;
		break;
	case FLOAT:
		return al_indexOf(list, type, va_arg(ap, float)) != -1 ? 1 : 0;
		break;
	case DOUBLE:
		return al_indexOf(list, type, va_arg(ap, double)) != -1 ? 1 : 0;
		break;
	case STRING:
		return al_indexOf(list, type, va_arg(ap, char*)) != -1 ? 1 : 0;
		break;
	case REFERENCE:
		return al_indexOf(list, type, va_arg(ap, void*)) != -1 ? 1 : 0;
		break;
	default:
		return 0;
		break;
	}

}


int al_size(ArrayList* list) { return list->size; }
int al_isEmpty(ArrayList* list) { return list->size == 0; }










