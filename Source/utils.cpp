#include "utils.h"

char* to_cstring(int x)
{
	char Array[sizeof(int) * 8] = {};

	char* result;
	int size = 0;
	bool minus = false;


	try
	{
		if (x == 0)
		{
			result = new char[2];
			result[0] = '0';
			result[1] = '\0';

			return result;
		}
		else if (x < 0)
			minus = true;

		while (x)
		{
			Array[size] = '0' + x % 10;
			x /= 10;
			size++;
		}

		result = new char[size + 1 + (minus ? 1 : 0)];
		int index = 0;
		if (minus)
		{
			result[0] = '-';
			index++;
		}
		for (int i = size - 1; i >= 0; i--)
			result[index++] = Array[i];
		result[index] = '\0';

	}
	catch (...)
	{
		printf("Could not allocate enough memory - to_cstring function.\n");
		exit(EXIT_FAILURE);
	}

	return result;
}

char* to_time(int seconds, bool display_empty_hours)
{
	char* hour = to_cstring(seconds/3600);
	seconds %= 3600;
	char* minute = to_cstring(seconds/60);
	seconds %= 60;
	char* second = to_cstring(seconds);

	char* result;
	try 
	{
		result = new char[2 + 1 + 2 + 1 + 2 + 1];
	}
	catch (...)
	{
		printf("Could not allocate enough memory - to_cstring function.\n");
		exit(EXIT_FAILURE);
	}

	result[2] = result[5] = ':';

	int index = 0;
	if (display_empty_hours || strcmp("0", hour) != 0)
	{
		if (strlen(hour) == 1)
		{
			result[0] = '0';
			result[1] = hour[0];
		}
		else
			memcpy(result, hour, 2 * sizeof(char));
		index = 3;
	}

	if (strlen(minute) == 1)
	{
		result[index] = '0';
		result[index + 1] = minute[0];
	}
	else
		memcpy(result + index, minute, 2 * sizeof(char));
	index += 3;

	if (strlen(second) == 1)
	{
		result[index] = '0';
		result[index + 1] = second[0];
	}
	else
		memcpy(result + index, second, 2 * sizeof(char));
	result[index + 2] = '\0';

	delete[] hour;
	delete[] minute;
	delete[] second;

	return result;
}