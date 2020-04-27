#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "utils.h"

template <typename T>
void Allocate1D(T** array, int size)
{
	try
	{
		*array = new T[size];
	}
	catch (...)
	{
		printf("Could not allocate enough memory\n");
		exit(EXIT_FAILURE);
	}
}

template <typename T>
void Delete1D(T* array)
{
	if (array == nullptr)
		return;
	delete[] array;
}


template <typename T>
void Allocate2D(T*** array, int size)
{
	try
	{
		*array = new T*[size];
		for (int i = 0; i < size; i++)
			(*array)[i] = new T[size];
	}
	catch (...)
	{
		printf("Could not allocate enough memory\n");
		exit(EXIT_FAILURE);
	}
}

template <typename T>
void Delete2D(T** array, int size)
{
	if (array == nullptr)
		return;

	for (int i = 0; i < size; i++)
		delete[] array[i];
	delete[] array;
}

template <typename T>
void Memset2D(T** array, int size, T value)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			array[i][j] = value;
}

template <typename T>
void Copy2D(T** source, T** destination, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			destination[i][j] = source[i][j];
}

template <typename T>
T min(T a, T b)
{
	return (a < b ? a : b);
}

template <typename T>
T max(T a, T b)
{
	return (a > b ? a : b);
}

template <typename T>
T abs(T a)
{
	return a < 0 ? -a : a;
}

struct Transformation
{
	int x;
	int y;
	
	int dest_x;
	int dest_y;

	int waiting_time;

	Transformation() 
		:x(0), y(0), dest_x(0), dest_y(0), waiting_time(0){}

	Transformation(int x, int y, int dest_x, int dest_y)
		:x(x), y(y), dest_x(dest_x), dest_y(dest_y), waiting_time(0) {}
};

char* to_time(int seconds, bool display_empty_hours);	//Returned array must be freed by delete[]
char* to_cstring(int x);	//Returned array must be freed by delete[]