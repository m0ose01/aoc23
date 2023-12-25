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
int get_gear_ratio(node *current, int index);
int get_digits(int n);
int get_number_offset(char *string, int index);

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
		return 2;
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
	int total_gear_ratios = 0;
	while (current != NULL)
	{
		int current_number;
		for (int i = 0, n = strlen(current->contents); i < n; i++)
		{
			char current_character = current->contents[i];

			// TODO: Test whether each character is a gear, and find its gear ratio
			int current_gear_ratio;
			if (current_character == '*')
			{
				current_gear_ratio = get_gear_ratio(current, i);
			}
			else
			{
				continue;
			}

			total_gear_ratios += current_gear_ratio;
		}
		current = current->next;
	}

	printf("%i\n", total_gear_ratios);
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

int get_gear_ratio(node *current_node, int index)
{
	const int MAX_ADJACENT_NUMBERS = 6;

	int adjacent_numbers_count = 0;
	int adjacent_numbers[MAX_ADJACENT_NUMBERS];

	node *rows[] = {current_node->prev, current_node, current_node->next};

	for (int current_row = 0; current_row < 3; current_row++)
	{
		if (rows[current_row] == NULL)
		{
			continue;
		}

		for (int current_column = 0; current_column < 3; current_column++)
		{
			int current_place = (index - 1) + current_column;

			if (is_numeric(rows[current_row]->contents[current_place]))
			{
				int number_start = current_place - get_number_offset(rows[current_row]->contents, current_place);
				adjacent_numbers_count++;
				adjacent_numbers[adjacent_numbers_count - 1] = get_number(rows[current_row]->contents, number_start);

				while (current_column < 3 && is_numeric(rows[current_row]->contents[current_place]))
				{
					current_column++;
					current_place = (index - 1) + current_column;
				}
			}
		}
	}

	if (adjacent_numbers_count == 2)
	{
		return adjacent_numbers[0] * adjacent_numbers[1];
	}

	return 0;
}

int get_digits(int n)
{
	return floor(log10(n)) + 1;
}

int get_number_offset(char *string, int index)
{
	int offset = 0;
	char current_character = string[index - offset];
	while (index - offset >= 0 && is_numeric(current_character)) // This line took so so long to fix. Should have been >= 0, not >!!!
	{
		offset++;
		current_character = string[index - offset];
	}
	return offset - 1;
}
