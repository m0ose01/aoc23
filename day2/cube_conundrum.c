#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
	 {
	int red;
	int green;
	int blue;
} bag_contents;

int is_possible(char *line, bag_contents *total);

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

	while (fgets(buffer, MAX_LINELENGTH, input_file) != NULL)
	{
		int result = is_possible(buffer, &current_bag) * line_number;
		total += result;

		free(buffer);
		buffer = malloc(sizeof(char) * MAX_LINELENGTH);
		if (buffer == NULL)
		{
			fclose(input_file);
			printf("Error allocating buffer.\n");
			return 3;
		}
		
		line_number++;
	}
	free(buffer);
	fclose(input_file);

	printf("%i\n", total);
}

int is_possible(char *game, bag_contents *current_bag)
{	
	char game_copy[strlen(game)];
	strcpy(game_copy, game);
	char *colon_substring_last;
	char *colon_substring = strtok_r(game_copy, ":", &colon_substring_last);
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
				char *space_substring_last;
				char *space_substring = strtok_r(comma_substring, " ", &space_substring_last);
				if (space_substring == NULL)
				{
					break;
				}
				int cube_count = atoi(space_substring);


				char * colour = strtok_r(NULL, " ", &space_substring_last);
				if (colour == NULL)
				{
					continue;
				}

				if (strncmp(colour, "red", 3) == 0 && cube_count > current_bag->red)
				{
					return 0;
				}
				else if (strncmp(colour, "green", 5) == 0 && cube_count > current_bag->green)
				{
					return 0;
				}
				else if (strncmp(colour, "blue", 4) == 0 && cube_count > current_bag->blue)
				{
					return 0;
				}

				comma_substring = strtok_r(NULL, ",", &comma_substring_last);
			}
			semicolon_substring = strtok_r(NULL, ";", &semicolon_substring_last);
		}
		colon_substring = strtok_r(NULL, ":", &colon_substring_last);
	}
	return 1;
}
