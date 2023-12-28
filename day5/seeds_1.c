#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	long int destination_start;
	long int source_start;
	long int range_length;
} Map;

long binary_search(long target, Map array[], int start, int end);
int cmp(const void *a, const void *b);
int compare_maps(const void *a, const void *b);
long get_location(long seed, const int MAX_CATEGORIES, const int MAX_SEEDS, Map maps[MAX_CATEGORIES][MAX_SEEDS], int num_maps[]);

int main(int argc, char *argv[])
{
	// Input handling
	const int MAX_LENGTH = 220;
	if (argc != 2)
	{
		printf("Usage: %s, <input.txt>\n", argv[0]);
		return -1;
	}

	FILE *input = fopen(argv[1], "r");
	if (input == NULL)
	{
		printf("Error opening file \'%s\'\n", argv[1]);
		return -2;
	}

	// Program Start
	char buffer[MAX_LENGTH];
	fgets(buffer, MAX_LENGTH, input);
	strtok(buffer, ":");

	char *seed_str = NULL;

	const int MAX_SEEDS = 20;
	long seeds[MAX_SEEDS];
	
	for (int i = 0; i < MAX_SEEDS && (seed_str = strtok(NULL, " ")) != NULL; i++)
	{
		seeds[i] = atol(seed_str);
	}

	const int MAX_CATEGORIES = 7;
	const int MAX_MAPS = 51;
	int num_maps[] = {0, 0, 0, 0, 0, 0, 0};
	Map maps[MAX_CATEGORIES][MAX_MAPS];
	for (int this_category = 0; this_category < MAX_CATEGORIES; this_category++)
	{
		while (buffer[0] < '0' || buffer[0] > '9')
		{
			fgets(buffer, MAX_LENGTH, input);
		}

		for (int this_map = 0; this_map < MAX_MAPS; this_map++)
		{
			sscanf(
				buffer, "%ld %ld %ld",
				&maps[this_category][this_map].destination_start, 
				&maps[this_category][this_map].source_start, 
				&maps[this_category][this_map].range_length
			);
			if (buffer[0] < '0' || buffer[0] > '9' || (fgets(buffer, MAX_LENGTH, input) == NULL))
			{
				if (buffer[0] != 10)
				{
					num_maps[this_category] = this_map + 1;
				}
				else
				{
					num_maps[this_category] = this_map;
				}
				break;
			}
		}
	}

	// Should probably sort the list first.
	long source_starts[MAX_CATEGORIES][MAX_MAPS];
	for (int i = 0; i < MAX_CATEGORIES; i++)
	{
		qsort(&maps[i], num_maps[i], sizeof(Map), &compare_maps);
	}

	// Now, take seed, and search through each map to find its destination range
	long locations[MAX_SEEDS];
	for (int this_seed = 0; this_seed < MAX_SEEDS; this_seed++)
	{
		locations[this_seed] = get_location(seeds[this_seed], MAX_CATEGORIES, MAX_MAPS, maps, num_maps);
	}

	qsort(&locations, MAX_SEEDS, sizeof(long), &cmp);
	long final_answer = locations[0];
	printf("%li\n", final_answer);
	
	// End of Program
	return 0;
}

long binary_search(long target, Map array[], int start, int end)
{
	int middle = ((start + end)  / 2);
	Map current_map = array[middle];
	long current_range[2] = {current_map.source_start, current_map.source_start + current_map.range_length};

	long ans = target;
	if (target >= current_range[0] && target < current_range[1])
	{
		ans = current_map.destination_start + (target - current_map.source_start);
		return ans;
	}
	else if (start >= end)
	{
		return ans;
	}
	else if (target < current_map.source_start)
	{
		ans = binary_search(target, array, start, middle - 1);
		return ans;
	}
	else if (target > current_map.source_start)
	{
		ans = binary_search(target, array, middle + 1, end);
		return ans;
	}
	return ans;
}

int cmp(const void *a, const void *b)
{

	long A = *(long*) a;
	long B = *(long*) b;
	if (A > B)
	{
		return 1;
	}
	else if (A < B)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int compare_maps(const void *a, const void *b)
{
	Map *arg1 = (Map*)a;
	Map *arg2 = (Map*)b;
	
	if (arg1->source_start > arg2->source_start)
	{
		return 1;
	}
	else if (arg1->source_start < arg2->source_start)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

long get_location(long source, const int MAX_CATEGORIES, const int MAX_MAPS, Map maps[MAX_CATEGORIES][MAX_MAPS], int num_maps[])
{
	long key = source;
	long source_starts[MAX_CATEGORIES][MAX_MAPS];
	for (int this_category = 0; this_category < MAX_CATEGORIES; this_category++)
	{
		// TODO: Go through each category, and get the destination key
		key = binary_search(key, maps[this_category], 0, num_maps[this_category]);
	}
	return key;
}
