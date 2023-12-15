#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_first_digit(int *digit, char *line);
int get_last_digit(int *digit, char *line);

char *digits_alpha[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int digits_numeric[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int main(int argc, char * argv[])
{	
	if (argc != 2)
	{
		printf("Usage: ./trebuchet input.txt\n");
		return 1;
	}

	char * filename = argv[1];
	
	FILE *input = fopen(filename, "r");
	if (input == NULL)
	{
		printf("Error opening file.\n");
		return 2;
	}
	
	const int MAX_LINE_LENGTH = 100;

	char *buffer = malloc(sizeof(char) * MAX_LINE_LENGTH);
	if (buffer == NULL)
	{	
		fclose(input);
		printf("Error allocating buffer");
		return 3;
	}
	int current_digit = 0;
	int total = 0;

	while (fgets(buffer, MAX_LINE_LENGTH, input) != NULL)
	{
		// Get first digit of line
		if (get_first_digit(&current_digit, buffer) != 0)
		{
			printf("ERROR\n");
			total += 0;
			continue;
		}
		total += current_digit * 10;

		// Get last digit of line
		if (get_last_digit(&current_digit, buffer) != 0)
		{
			printf("ERROR\n");
			total += 0;
			continue;
		}
		total += current_digit;

		free(buffer);
		buffer = malloc(sizeof(char) * MAX_LINE_LENGTH);
		if (buffer == NULL)
		{
			fclose(input);
			printf("Error allocating buffer");
			return 3;
		}

	}
	printf("%i\n", total);
}

int get_first_digit(int *digit, char *line)
{
	int ans;
	for (int i = 0, n = strlen(line); i < n; i++)
	{
		if (line[i] >= 48 && line[i] <= 57)
		{
			ans = line[i] - 48;
			*digit = ans;
			return 0;
		}

		for (int current_digit = 0; current_digit < 10; current_digit++)
		{	
       			int digit_length = strlen(digits_alpha[current_digit]);
			if (strncmp(&line[i], digits_alpha[current_digit], digit_length) == 0)
			{	
				ans = digits_numeric[current_digit];
				*digit = ans;
				return 0;
			}
		}
	}
	return 1;
}

int get_last_digit(int *digit, char *line)
{
	int ans;
	for (int i = 0, n = strlen(line); i < n + 1; i++)
	{
		if (line[n - i] >= 48 && line[n - i] <= 57)
		{
			ans = line[n - i] - 48;
			*digit = ans;
			return 0;
		}

		for (int current_digit = 0; current_digit < 10; current_digit++)
		{	
       			int digit_length = strlen(digits_alpha[current_digit]);
			if (strncmp(&line[n - i], digits_alpha[current_digit], digit_length) == 0)
			{	
				ans = digits_numeric[current_digit];
				*digit = ans;
				return 0;
			}
		}
	}
	return 1;
}
