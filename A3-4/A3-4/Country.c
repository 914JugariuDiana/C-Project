#include "Country.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Country* createCountry(char* name, char* continent, int population) {
	if(name == NULL || continent == NULL)
		return NULL;

	Country* country = (Country*)malloc(sizeof(Country));

	if (country == NULL) {
		return NULL;
	}

	country->name = malloc((strlen(name) + 1) * sizeof(char));

	if (country->name == NULL) {
		free(country);
		return NULL;
	}

	strcpy(country->name, name);

	country->continent = malloc((strlen(continent) + 1) * sizeof(char));

	if (country->continent == NULL) {
		free(country->name);
		free(country);
		return NULL;
	}

	strcpy(country->continent, continent);

	country->population = population;

	return country;
}

void destroyCountry(Country* country) {
	if (country == NULL)
		return;

	free(country->name);
	free(country->continent);
	free(country);
}

char* getContinent(Country* country)
{
	return country->continent;
}

Country* copyCountry(Country* country)
{
	Country* countryCopy = createCountry(country->name, country->continent, country->population);
	return countryCopy;
}

char* getName(Country* country) 
{
	return country->name;
}

int getPopulation(Country* country)
{
	return country->population;
}

void setPopulation(Country* country, int population)
{
	country->population = population;
}

void testCountry() {
	Country* country = createCountry("aaa", "asia", 145);

	Country* copyC = copyCountry(country);
	assert(strcmp(getName(country), getName(copyC)) == 0);
	assert(strcmp(getContinent(country), getContinent(copyC)) == 0);
	assert(strcmp(getName(country), "aaa") == 0);
	assert(strcmp(getContinent(country), "asia") == 0);
	assert(getPopulation(country) == getPopulation(copyC));
	assert(getPopulation(country) == 145);

	setPopulation(country, 4);
	assert(getPopulation(country) == 4);

	destroyCountry(country);
	destroyCountry(copyC);
}
