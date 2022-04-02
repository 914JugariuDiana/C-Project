#include "Repo.h"
#include "Country.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

Repo* createRepo(int capacity, functionDestroy destroy) {
	Repo* repo = malloc(sizeof(Repo));

	if (repo == NULL) {
		return NULL;
	}

	repo->size = 0;
	repo->capacity = capacity;
	repo->data = malloc(sizeof(TElem*) * repo->capacity);
	if (repo->data == NULL) {
		free(repo);
		return NULL;
	}
	repo->destroy = destroy;
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
			repo->destroy(repo->data[i]);

	free(repo->data);
	free(repo);
}
int addToRepo(Repo* repo, TElem elem)
{
	TElem* currentData = repo->data;
		if (repo == NULL)
			return 0;
	if (repo->size == repo->capacity) {
		repo->capacity *= 2;
		currentData = realloc(repo->data, sizeof(TElem*) * repo->capacity);
		if (currentData == NULL) {
			repo->capacity /= 2;
			return 0;
		}
	}
	repo->data = currentData;
	repo->data[repo->size] = elem;
	repo->size += 1;
	return 1;
}

void deleteFromRepo(Repo* repo, int position)
{
	Country* country;

	country = repo->data[position];
	repo->data[position] = repo->data[repo->size - 1];
	repo->size -= 1;
	destroyCountry(country);
}
void updateRepo(Repo* repo, int pos, int value, void (*field)(void*, int))
{
	(*field)(repo->data[pos], value);
}
char* lowerCase(char* str)
{
	int i;

	for (i = 0; i < strlen(str); i++)
		str[i] = (char)(tolower(str[i]));
	
	return str;
}
int findElem(Repo* repo, void* (*field)(void*), char* string)
{
	int i;
	TElem* elem;

	for (i = 0; i < repo->size; i++) {
		elem = repo->data[i];
		if (strcmp(lowerCase((*field)(elem)), lowerCase(string)) == 0)
			return i;
	}
	return -1;
}
Repo* getRepo(Repo* repo) {
	return repo;
}
Repo* filterRepo(Repo* repo, void* (*function)(TElem*), char* string)
{
	Repo* newRepo;
	Country* country;
	int i;

	newRepo = createRepo(repo->capacity, repo->destroy);
	for (i = 0; i < repo->size; i++) {
		if (strstr(lowerCase(function(repo->data[i])), lowerCase(string)) != NULL)
		{
			country = copyCountry(repo->data[i]);
			addToRepo(newRepo, country);
		}
	}
	return newRepo;
}
Repo* orderRepo(Repo* repo)
{
	TElem* elem;
	int i, ok = 0;

	do {
		ok = 1;
		for (i = 1; i < repo->size; i++) {
			if (getPopulation(repo->data[i]) < getPopulation(repo->data[i - 1])) {
				elem = repo->data[i];
				repo->data[i] = repo->data[i - 1];
				repo->data[i - 1] = elem;
				ok = 0;
			}
		}
	} while (ok == 0);

	return repo;
}

Repo* copyRepo(Repo* repo) {
	Repo* repoCopy = createRepo(repo->capacity, repo->destroy);
	int i;
	for (i = 0; i < repo->size; i++)
		repoCopy->data[i] = copyCountry(repo->data[i]);

	return repo;
}
void testLowerCase_stringToPointerContainingUpperCaseLetters_stringLowercase() {
	assert(strcmp(lowerCase("KFIEl"), "kfiel") == 0);
}

void testRepo() {
	Repo* repo = createRepo(2, &destroyCountry);
	void* (*p)(void*);
	char* a;
	assert(repo->size == 0);
	Country* country = createCountry("ba", "asia", 4);
	addToRepo(repo, country);

	assert(repo->size == 1);
	p = &getName;
	a = malloc(sizeof(char) * 50);
	if (a == NULL) {
		destroyRepo(repo);
		free(a);
		return;
	}
	*a = 'a';
	assert(findElem(repo, p, a) == -1);

	Repo* repoA;
	repoA = filterRepo(repo, p, a);
	assert(repoA->size == 0);

	Country* cc = createCountry("ab", "asia", 1);
	addToRepo(repo, cc);

	repo = orderRepo(repo);
	assert(strcmp(getName(repo->data[0]), "ab") == 0);

	deleteFromRepo(repo, 1);
	assert(repo->size == 1);

	destroyRepo(repoA);
	destroyRepo(repo);
	free(a);
}