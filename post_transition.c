#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;

void print_all_packages(town t) {
    printf("%s:\n", t.name);
    for (int i = 0; i < t.offices_count; ++i)
    {
        printf("\t%d:\n", i);
        for (int j = 0; j < t.offices[i].packages_count; ++j)
            printf("\t\t%s\n", t.offices[i].packages[j].id);
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
	// Registers the ammount of packages to be transfered
	int count_transfers = 0;

	// Alias for the source and target post offices
	post_office* source_office = source->offices + source_office_index;
	post_office* target_office = target->offices + target_office_index;

	// Counts the number of packages that can be transfered
	for (int i = 0; i < source_office->packages_count; ++i)
		if ((source_office->packages + i)->weight >= target_office->min_weight && (source_office->packages + i)->weight <= target_office->max_weight)
			count_transfers++;

	// Creates packages arrays for the post offices
	package* new_source_packages = malloc(sizeof(package) * (source_office->packages_count - count_transfers));
	package* new_target_packages = malloc(sizeof(package) * (target_office->packages_count + count_transfers));

	// Fills the new array with packages from the target post office with the previous packages
	for (int i = 0; i < target_office->packages_count; ++i)
		new_target_packages[i] = (target_office->packages)[i];

	// Fills the remaining positions on the target post office packages' array and the source post office packages' array according to the weight
	for (int i = 0, j = 0, k = 0; i < source_office->packages_count; ++i)
		if ((source_office->packages + i)->weight >= target_office->min_weight && (source_office->packages + i)->weight <= target_office->max_weight)
			new_target_packages[target_office->packages_count + k++] = (source_office->packages)[i];
		else
			new_source_packages[j++] = (source_office->packages)[i];

	// Redefines the source post office
	free(source_office->packages);
	source_office->packages = new_source_packages;
	source_office->packages_count -= count_transfers;

	// Redefines the target post office
	free(target_office->packages);
	target_office->packages = new_target_packages;
	target_office->packages_count += count_transfers;
}

int count_packages_in_town(town* t)
{
	int count = 0;
	for (int i = 0; i < t->offices_count; ++i)
		count += (t->offices + i)->packages_count;
	return count;
}

town town_with_most_packages(town* towns, int towns_count) {
	int most_packages = 0;
	for (int i = 1; i < towns_count; ++i)
		if (count_packages_in_town(towns + i) > count_packages_in_town(towns + most_packages))
			most_packages = i;
	return *(towns + most_packages);
}

town* find_town(town* towns, int towns_count, char* name) {
	int index;
    for (int i = 0; i < towns_count; ++i)
        if (strcmp((towns + i)->name, name) == 0)
        {
			index = i;
			break;
		}
	return (towns + index);
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}