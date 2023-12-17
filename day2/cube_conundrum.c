#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_POSSIBLE 0
#define GET_POWER 1

typedef struct
	 {
	int red;
	int green;
	int blue;
} bag_contents;

int parse_game(char *game, bag_contents *current_bag, int action);
int check_possible(char *substring, bag_contents *bag_maximum);
void update_max(char *substring, bag_contents *current_max);

int main(int argc, char *argv[])
{
	const int MAX_LINELENGTH = 200;

	if (argc != 2)
	{
		printf("Usage: ./cube_conundrum [input.txt]\n");
		return 1;
	}

	char *filename = argv[1];
	FILE *input_file = fopen(filename, "r");
	if (input_file == NULL)
	{
		printf("Error opening file.\n");
		return 2;
	}

	char *buffer = malloc(sizeof(char) * MAX_LINELENGTH);
	if (buffer == NULL)
	{
		fclose(input_file);
		printf("Error allocating buffer.\n");
		return 3;
	}

	int line_number = 1;
	int total = 0;

	bag_contents current_bag = {12, 13, 14};

	int action = GET_POWER;

	while (fgets(buffer, MAX_LINELENGTH, input_file) != NULL)
	{	
		int result = parse_game(buffer, &current_bag, action) * line_number;
		total += result;

		free(buffer);
		buffer = malloc(sizeof(char) * MAX_LINELENGTH);
		if (buffer == NULL)
		{
			fclose(input_file);
			printf("Error allocating buffer.\n");
			return 3;
		}
		
		if (action == CHECK_POSSIBLE)
		{
			line_number++;
		}
	}
	free(buffer);
	fclose(input_file);

	printf("%i\n", total);
}

int parse_game(char *game, bag_contents *current_bag, int action)
{	
	bag_contents max = {0, 0, 0};

	char *colon_substring_last;
	char *colon_substring = strtok_r(game, ":", &colon_substring_last);
	while (colon_substring != NULL)
	{
		char *semicolon_substring_last;
		char *semicolon_substring = strtok_r(colon_substring, ";", &semicolon_substring_last);
		while (semicolon_substring != NULL)
		{
			char *comma_substring_last;
			char *comma_substring = strtok_r(semicolon_substring, ",", &comma_substring_last);
			while (comma_substring != NULL)
			{	
				if (action == CHECK_POSSIBLE)
				{
					if (check_possible(comma_substring, current_bag) == 0)
					{
						return 0;
					}
				}
				if (action == GET_POWER)
				{
					update_max(comma_substring, &max);
				}
				comma_substring = strtok_r(NULL, ",", &comma_substring_last);

			}
			semicolon_substring = strtok_r(NULL, ";", &semicolon_substring_last);
		}
		colon_substring = strtok_r(NULL, ":", &colon_substring_last);
	}
	if (action == GET_POWER)
	{
		return (max.red * max.green * max.blue);
	}
	return 1;
}

int check_possible(char *substring, bag_contents *bag_maximum)
{
	char *number_string_last;
	char *number_string = strtok_r(substring, " ", &number_string_last);

	char * colour = strtok_r(NULL, " ", &number_string_last);
	int cube_count = atoi(number_string);

	if (strncmp(colour, "red", 3) == 0 && cube_count > bag_maximum->red)
	{
		return 0;
	}
	else if (strncmp(colour, "green", 5) == 0 && cube_count > bag_maximum->green)
	{
		return 0;
	}
	else if (strncmp(colour, "blue", 4) == 0 && cube_count > bag_maximum->blue)
	{
		return 0;
	}
	return 1;
}

void update_max(char *substring, bag_contents *current_max)
{
	char *number_string_last;
	char *number_string = strtok_r(substring, " ", &number_string_last);

	char * colour = strtok_r(NULL, " ", &number_string_last);
	int cube_count = atoi(number_string);

	if (strncmp(colour, "red", 3) == 0 && cube_count > current_max->red)
	{
		current_max->red = cube_count;
	}
	else if (strncmp(colour, "green", 5) == 0 && cube_count > current_max->green)
	{
		current_max->green= cube_count;
	}
	else if (strncmp(colour, "blue", 4) == 0 && cube_count > current_max->blue)
	{
		current_max->blue = cube_count;
	}
}
