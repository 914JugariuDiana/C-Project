#include "Service.h"
#include <stdlib.h>
#include <string.h>
#include "Repo.h"
#include <assert.h>

Service* createService(Repo* repo) {
	Service* service = malloc(sizeof(Service));
	
	if (service == NULL) {
		return NULL;
	}

	service->undoStack = malloc(sizeof(StackOperation));
	if (service->undoStack == NULL) {
		return NULL;
	}
	service->undoStack->stackOperation = createRepo(2, &destroyOperation);
	service->redoStack = malloc(sizeof(StackOperation));
	if (service->redoStack == NULL) {
		return NULL;
	}
	service->redoStack->stackOperation = createRepo(2, &destroyOperation);

	service->repo = repo;

	return service;
}

void destroyService(Service* service) {

	if (service == NULL)
		return;

	destroyRepo(service->repo);
	destroyRepo(service->undoStack->stackOperation);
	destroyRepo(service->redoStack->stackOperation);
	free(service->undoStack);
	free(service->redoStack);
	free(service);
}

Repo* filterByString(Service* service, void*(*function)(TElem *), char* string) {
	Repo* repo;

	repo = filterRepo(service->repo, function, string);
	if (repo->size == 0)
		return orderRepo(copyRepo(service->repo));
	return orderRepo(repo);
}

int deleteCountry(Service* service, char* name)
{
	int position;
	position = findElem(service->repo, &getName, name);
	if (position != -1) {
		Country* country = copyCountry(service->repo->data[position]);
		Operation* operation = createOperation(country, "add");
		addToRepo(service->undoStack->stackOperation, operation);
		deleteFromRepo(service->repo, position);
		return 1;
	}
	return 0;
}

int addCountry(Service* service, char* name, char* continent, int population) {

	Country* country = createCountry(name, continent, population);
	if (addToRepo(service->repo, country)) {
		Country* countryCopy = copyCountry(country);
		Operation* operation = createOperation(countryCopy, "delete");
		addToRepo(service->undoStack->stackOperation, operation); 
		return 1;
	}
	destroyCountry(country);
	return 0;
}

int findCountry(Service* service, char* name) {
	return findElem(service->repo, &getName, name);
}

int updateCountry(Service* service, char* mCountry, char* newCountry, int population)
{
	int posFirstCountry, posSecondCountry;

	posFirstCountry = findCountry(service, mCountry);
	posSecondCountry = findCountry(service, newCountry);
	if (posFirstCountry != -1 && posSecondCountry != -1) {
		if (getPopulation(service->repo->data[posFirstCountry]) >= population) {
			Country* copy = copyCountry(service->repo->data[posFirstCountry]);
			Operation* operation1 = createOperation(copy, "update");
			addToRepo(service->undoStack->stackOperation, operation1);
			copy = copyCountry(service->repo->data[posSecondCountry]);
			Operation* operation2 = createOperation(copy, "update");
			addToRepo(service->undoStack->stackOperation, operation2);
			updateRepo(service->repo, posFirstCountry, getPopulation(service->repo->data[posFirstCountry]) - population, &setPopulation);
			updateRepo(service->repo, posSecondCountry, getPopulation(service->repo->data[posSecondCountry]) + population, &setPopulation);
			return 1;
		}
	}
	return 0;
}

int undoOperation(Service* service)
{
	Operation* operation = pop(service->undoStack);
	if (operation == NULL) {
		destroyOperation(operation);
		return 0;
	}
	if (strcmp(operation->operationName, "delete") == 0) {
		Country* copyC = copyCountry(operation->country);
		Operation* redoOperation = createOperation(copyC, "add");
		addToRepo(service->redoStack->stackOperation, redoOperation);
		deleteFromRepo(service->repo, findCountry(service, operation->country->name));
	}
	else {
		if (strcmp(operation->operationName, "add") == 0) {
			Country* copyC = copyCountry(operation->country);
			Operation* redoOperation = createOperation(copyC, "delete");
			addToRepo(service->redoStack->stackOperation, redoOperation);
			addToRepo(service->repo, operation->country);
		}
		else {
			if (strcmp(operation->operationName, "update") == 0) {
				Country* copyC = copyCountry(service->repo->data[findCountry(service, operation->country->name)]);
				Operation* redoOperation = createOperation(copyC, "update");
				addToRepo(service->redoStack->stackOperation, redoOperation);
				updateRepo(service->repo, findCountry(service, operation->country->name), operation->country->population, &setPopulation);
				destroyOperation(operation);
				operation = pop(service->undoStack);
				copyC = copyCountry(service->repo->data[findCountry(service, operation->country->name)]);
				redoOperation = createOperation(copyC, "update");
				addToRepo(service->redoStack->stackOperation, redoOperation);
				updateRepo(service->repo, findCountry(service, operation->country->name), operation->country->population, &setPopulation);
			}
		}
	}
	destroyOperation(operation);
	return 1;
}

int redoOperation(Service* service)
{
	Operation* operation = pop(service->redoStack);
	if (operation == NULL) {
		destroyOperation(operation);
		return 0;
	}
	if (strcmp(operation->operationName, "delete") == 0) {
		Country* copyC = copyCountry(operation->country);
		Operation* undoOperation = createOperation(copyC, "add");
		addToRepo(service->undoStack->stackOperation, undoOperation);
		deleteFromRepo(service->repo, findCountry(service, operation->country->name));
	}
	else {
		if (strcmp(operation->operationName, "add") == 0) {
			Country* copyC = copyCountry(operation->country);
			Operation* undoOperation = createOperation(copyC, "delete");
			addToRepo(service->undoStack->stackOperation, undoOperation);
			addToRepo(service->repo, operation->country);
		}
		else {
			if (strcmp(operation->operationName, "update") == 0) {
				Country* copyC = copyCountry(service->repo->data[findCountry(service, operation->country->name)]);
				Operation* undoOperation = createOperation(copyC, "update");
				addToRepo(service->undoStack->stackOperation, undoOperation);
				updateRepo(service->repo, findCountry(service, operation->country->name), operation->country->population, &setPopulation);
				destroyOperation(operation);
				operation = pop(service->redoStack);
				copyC = copyCountry(service->repo->data[findCountry(service, operation->country->name)]);
				undoOperation = createOperation(copyC, "update");
				addToRepo(service->undoStack->stackOperation, undoOperation);
				updateRepo(service->repo, findCountry(service, operation->country->name), operation->country->population, &setPopulation);
			}
		}
	}
	destroyOperation(operation);
	return 1;
}

void testService() {
	Repo* repo;
	repo = createRepo(2, &destroyCountry);
	Service* service = createService(repo);
	void* (*p)(void*);
	p = &getName;
	Country* country = createCountry("aa", "asia", 4);

	addCountry(service, "aa", "asia", 4);
	assert(repo->size == 1);
	Repo* repoA;
	char* a;
	a = malloc(sizeof(char) * 50);
	if (a == NULL) {
		destroyService(service);
		destroyCountry(country);
		free(a);
		return;
	}

	*a = 'a';
	a[1] = 0;
	repoA = filterByString(service, p, a);
	assert(repoA->size == 1);

	*a = 'b';
	a[1] = 0;
	assert(findCountry(service, a) == -1);
	strcpy(a, "aa");
	assert(findCountry(service, a) == 0);

	Country* countryU = createCountry("bb", "america", 9);
	addCountry(service, "bb", "america", 9);
	assert(repo->size == 2);

	updateCountry(service, country->name, countryU->name, 2);

	assert(getPopulation(service->repo->data[0]) == 2);
	assert(getPopulation(service->repo->data[1]) == 11);

	undoOperation(service);

	assert(getPopulation(service->repo->data[0]) == 4);
	assert(getPopulation(service->repo->data[1]) == 9);

	redoOperation(service);
	assert(getPopulation(service->repo->data[0]) == 2);
	assert(getPopulation(service->repo->data[1]) == 11);

	destroyRepo(repoA);
	destroyService(service);
	destroyCountry(country);
	destroyCountry(countryU);
	free(a);
}

void initializeCountries(Service* service) {
	Country* country;
	country = createCountry("A", "Australia", 45);
	addToRepo(service->repo, country);
	country = createCountry( "b", "Europe", 15);
	addToRepo(service->repo, country);
	country = createCountry("C", "Asia", 45);
	addToRepo(service->repo, country);
	country = createCountry("d", "Europe", 35);
	addToRepo(service->repo, country);
	country = createCountry("E", "Asia", 75);
	addToRepo(service->repo, country);
	country = createCountry("F", "Europe", 45);
	addToRepo(service->repo, country);
	country = createCountry("G", "Africa", 5);
	addToRepo(service->repo, country);
	country = createCountry("h", "America", 25);
	addToRepo(service->repo, country);
	country = createCountry("i", "Asia", 95);
	addToRepo(service->repo, country);
	country = createCountry("J", "America", 105);	
	addToRepo(service->repo, country);
}


