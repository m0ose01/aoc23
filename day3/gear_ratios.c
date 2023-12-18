#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINELENGTH 142

typedef struct node {
	char contents[MAX_LINELENGTH];
	struct node *prev;
	struct node *next;
} node;

void free_list(node *start);
int is_numeric(char character);
int get_number(char *string, int index);
int is_part_number(node *current, int index, int digits);
int is_symbol(char character);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s, <input.txt>\n", argv[0]);
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	if (input == NULL)
	{
		printf("Error opening %s.\n", argv[1]);
	}
	
	node *current = malloc(sizeof(node));
	node *start  = current;
	current->prev = NULL;
	
	// Read in lines to list
	while (fgets(current->contents, MAX_LINELENGTH, input))
	{
		current->next = malloc(sizeof(node));
		current->next->prev = current;
		current = current->next;
	}
	current->next = NULL;

	current = start;
	int total_part_numbers = 0;
	while (current->next != NULL)
	{
		int current_part_number;
		for (int i = 0, n = strlen(current->contents); i < n; i++)
		{
			current_part_number = 0;
			char current_character = current->contents[i];

			current_part_number = get_number(current->contents, i);	
			if (current_part_number == -1)
			{
				continue;
			}
			

			int digits = floor(log10(current_part_number)) + 1;
			if (is_part_number(current, i, digits))
			{
				total_part_numbers += current_part_number;
			}

			i += digits;
		}
		current = current->next;
	}

	printf("%i\n", total_part_numbers);
	free_list(start);
	fclose(input);
}

void free_list(node *start)
{
	node *head = start;
	while (head->next != NULL)
	{
		head = head->next;
		free(head->prev);
	}

	free(head);
}

int is_numeric(char character)
{
	if (character < '0' || character > '9')
	{
		return 0;
	}
	return 1;	
}

int get_number(char *string, int index)
{
	char current_character = string[index];
	int number;

	if (!is_numeric(current_character))
	{
		number = -1;
	}
	else
	{
		number = 0;
	}

	while (is_numeric(current_character))
	{
		number *= 10;
		number += current_character - '0';

		index++;
		current_character = string[index];
	}
	return number;
}

int is_part_number(node *current, int index, int digits)
{
	for (int i = 0; i < digits + 2; i++)
	{
		int current_place = (index - 1) + i;
		if (is_symbol(current->contents[current_place]))
		{
			return 1;
		}

		if (current->next != NULL && is_symbol(current->next->contents[current_place]))
		{
			return 1;
		}

		if (current->prev != NULL && is_symbol(current->prev->contents[current_place]))
		{
			return 1;
		}
	}
	return 0;
}

int is_symbol(char character)
{
	if (is_numeric(character) || character == '.' || character == '\0' || character == '\n')
	{
		return 0;
	}
	return 1;
}
