#include "UI.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Service.h"
#include "Country.h"

UI* createUI(Service* service) {
	UI* ui = malloc(sizeof(UI));

	if (ui == NULL) {
		return NULL;
	}

	ui->service = service;

	return ui;
}
void destroyUI(UI* ui) {
	if (ui == NULL)
		return;

	destroyService(ui->service);
	free(ui);
}
void printOptions() {
	printf("***********************************************\n");
	printf("1 - add country\n");
	printf("2 - delete country\n");
	printf("3 - update country\n");
	printf("4 - find country containing given string(NULL to print all countries)\n");
	printf("5 - display all countries from a specified continent(NULL to consider countries from all continents)\n");
	printf("6 - undo\n");
	printf("7 - redo\n");
	printf("8 - exit\n");
	printf("***********************************************\n");
}
int readNumber(char* message) {
	char string[30];
	int number = 0;
	int result = 0;

	while (result == 0) {
		printf("%s", message);
		if (scanf("%29s", string) == 1) {
			string[strlen(string)] = 0;
			result = sscanf(string, "%d", &number);
		}
		if (result == 0)
			printf("Error reading number!\n");
	}
	return number;
}
int checkContinent(char* continent) {
	char continents[] = "europe america africa australia asia";
	continent = lowerCase(continent);
	if (strstr(continents, lowerCase(continent)) != NULL)
		return 1;
	return 0;
}
int add(UI* ui) {
	char* name;
	char* continent;
	int population;

	name = malloc(sizeof(char) * 50);
	continent = malloc(sizeof(char) * 50);
	if (name == NULL || continent == NULL)
		return 0;

	printf("Input the name of the country: ");
	if (scanf("%49s", name) != 1) {
		free(name);
		free(continent);
		return 0;
	}
	name[strlen(name)] = 0;

	printf("Input the name of the continent: ");
	if (scanf("%49s", continent) != 1) {
		free(name);
		free(continent);
		return 0;
		}

	continent[strlen(continent)] = 0;

	population = readNumber("Input the population <in millions>: ");
	if (findCountry(ui->service, name) == -1 && checkContinent(continent) == 1) {
		if (addCountry(ui->service, name, continent, population)) {
			free(name);
			free(continent);
			return 1;
		}
		else {
			free(name);
			free(continent);
			return 0;
		}
	}
	else {
		free(name);
		free(continent);
		return 0;
	}
}
int delete(UI* ui) {
	char* name;
	int value;

	name = malloc(sizeof(char) * 50);
	if (name == NULL)
		return 0;
	printf("Input the name of the country: ");
	if (scanf("%49s", name) != 1)
	{
		free(name);
		return 0;
	}
	value = deleteCountry(ui->service, name);
	free(name);
	return value;

}

Repo* filter(UI* ui, void*(*filter)(Country*)) {
	char* string;
	Repo* list;

	string = malloc(sizeof(char) * 50);
	if (string == NULL) {
		return 0;
	}
	printf("Input string(NULL to see all): ");
	if (scanf("%49s", string) != 1)
	{
		free(string);
		return 0;
	}

	list = filterByString(ui->service, filter, string);
	printRepo(list);
	destroyRepo(list);
	free(string);
	return list;
}

int undo(UI* ui)
{
	return undoOperation(ui->service);
}

int redo(UI* ui)
{
	return redoOperation(ui->service);
}

int update(UI* ui) {
	char* mCountry;
	char* newCountry;
	int population;
	int result;

	mCountry = malloc(sizeof(char) * 50);
	printf("Write country from where people migrate: ");
	if (scanf("%49s", mCountry) != 1) {
		free(mCountry);
		return 0;
	}
	
	newCountry = malloc(sizeof(char) * 50);
	printf("Write country to where people migrate: ");
	if (scanf("%49s", newCountry) != 1) {
		free(mCountry);
		free(newCountry);
		return 0;
	}

	population = readNumber("Write number of people who migrate <in millions>: ");

	result = updateCountry(ui->service, mCountry, newCountry, population);
	free(mCountry);
	free(newCountry);
	return result;
}
void startUI(UI* ui) {
	int option, run;

	run = 1;
	initializeCountries(ui->service);
	while (run) {
		printOptions();
		option = readNumber("Option: ");
		switch (option) {
			case 1:
				if (add(ui))
					printf("Country added\n");
				else
					printf("Country could not be added\n");
				break;
			case 2:
				if (delete(ui))
					printf("Country removed succesfully\n");
				else
					printf("Country could not be removed\n");
				break;
			case 3:
				if (update(ui))
					printf("Migration finnished\n");
				else
					printf("Migration could not be finished\n");
				break;
			case 4:
			{
				filter(ui, &getName);
			}
				break;
			case 5:
			{
				filter(ui, &getContinent);
			}
			break;
			case 6:
				if (undo(ui))
					printf("Operation is undone\n");
				else
					printf("Operation can not be undone\n");
				break;
			case 7:
				if (redo(ui))
					printf("Operation is redone\n");
				else
					printf("Operation can not be redone\n");
				break;
				break;
			case 8:
				return;
			default:
				break;
		}
	}
}


void printRepo(Repo* repo){
	if (repo == NULL)
		return;
	int i;

	for (i = 0; i < repo->size; i++)
		printf("Country %s found on continent %s has a population of %d millions people\n", getName(repo->data[i]), getContinent(repo->data[i]), getPopulation(repo->data[i]));
}


