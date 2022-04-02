#include "CountryRepo.h"
#include "Country.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

Repo* createRepo(int capacity) {
	Repo* repo = malloc(sizeof(Repo));

	if (repo == NULL) {
		return NULL;
	}

	repo->size = 0;
	repo->capacity = capacity;
	repo->data = malloc(sizeof(Country*) * repo->capacity);
	if (repo->data == NULL) {
		free(repo);
		return NULL;
	}

	return repo;
}

void destroyRepo(Repo* repo) {
	int i;

	if (repo == NULL)
		return;
	
	if (repo->data == NULL) {
		free(repo);
		return;
	}
	for (i = 0; i < repo->size; i++)
		if (repo->data[i] != NULL) 
			destroyCountry(repo->data[i]);

	free(repo->data);;
	free(repo);
}

int addToRepo(Repo* repo, Country* country) {
	Country** currentData = repo->data;
	if (repo == NULL)
		return 0; 
	if (repo->size == repo->capacity) {
		repo->capacity *= 2;
		currentData = realloc(repo->data, sizeof(Country*) * repo->capacity);
		if (currentData == NULL) {
			repo->capacity /= 2;
			return 0;
		}
	}
	repo->data = currentData;
	repo->data[repo->size] = country;
	repo->size += 1;
	return 1;
 }

int deleteFromRepo(Repo* repo, char* name) {
	int position;
	Country* country;

	if (repo == NULL)
		return 0;


	position = findElem(repo, name);
	country = repo->data[position];
	repo->data[position] = repo->data[repo->size - 1];
	repo->size -= 1;
	destroyCountry(country);

	return 1;
}

char* lowerCase(char* str)
{
	int i;

	for (i = 0; i < strlen(str); i++)
		str[i] = (char)(tolower(str[i]));
	
	return str;
}

int findElem(Repo* repo, char* name) {
	int i;
	Country* c;

	for (i = 0; i < repo->size; i++) {
		c = repo->data[i];
		if (strcmp(lowerCase(getName(c)), lowerCase(name)) == 0)
			return i;
	}
	return -1;
}
int updateRepo(Repo* repo, char* mCountry, char* newCountry, int population) {
	if (repo->data[findElem(repo, mCountry)]->population < population)
		return 0;

	repo->data[findElem(repo, mCountry)]->population -= population;
	repo->data[findElem(repo, newCountry)]->population += population;
	return 1;
}
Repo* getRepo(Repo* repo) {
	return repo;
}

Repo* filterRepo(Repo* repo, char* string) {
	Repo* newRepo;
	int i;

	newRepo = createRepo(repo->capacity);
	for (i = 0; i < repo->size; i++) {
		if (strstr(lowerCase(repo->data[i]->name), lowerCase(string)) != NULL)
			addToRepo(newRepo, repo->data[i]);
	}
	return newRepo;
}

void testLowerCase_stringToPointerContainingUpperCaseLetters_stringLowercase() {
	assert(strcmp(lowerCase("KFIEl"), "kfiel") == 0);
}