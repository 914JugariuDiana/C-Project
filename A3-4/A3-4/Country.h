#pragma once

typedef struct {
	char* name;
	char* continent;
	int population;
}Country;

//<summary>
//Creates a country and returns a pointer to it.
//</summary>
//<param name = "name">
//	"string" - name for country
//<param name = "continent">
//	"string" - name of the continent containing the country
//<param name = "population">
//	"integer" - number (in millions) of people
//<returns></returns>
Country* createCountry(char* name, char* Type, int population);
/// <summary>
/// Create a deep copy to a country
/// </summary>
/// <param name="country">The country to which we want to make the deep copy to</param>
/// <returns>A pointer to the copy of the country</returns>
Country* copyCountry(Country* country);
//<summary>
// Deallocates memory occupied by the Country.
//<summary>
//<param name = "c">
//	c - pointer to a Country
void destroyCountry(Country* country);
/// <summary>
/// Function returns the name of a country
/// </summary>
/// <param name="country">A pointer to the country </param>
/// <returns>The name of the country, </returns>
char* getName(Country* country);
/// <summary>
/// Funtion returns the population of the given country
/// </summary>
/// <param name="country">A pointer to the country</param>
/// <returns>The population of the country</returns>
int getPopulation(Country* country);
/// <summary>
/// Function returns the name of the continent where the country is found
/// </summary>
/// <param name="country">A pointer to the country </param>
/// <returns>The name of a continent </returns>
char* getContinent(Country* country);
/// <summary>
/// Updates the population of a country
/// </summary>
/// <param name="country">The country we want to update the population to</param>
/// <param name="population">The populations new value</param>
void setPopulation(Country* country, int population);
void testCountry();

