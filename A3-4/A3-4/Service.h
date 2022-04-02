#pragma once
#include "Repo.h"
#include "Country.h"
#include "OperationStack.h"

typedef struct {
	Repo* repo;
	StackOperation* undoStack;
	StackOperation* redoStack;
}Service;

/// <summary>
/// Creates a service
/// </summary>
/// <param name="repo">Pointer to a repository</param>
/// <returns>Returns a pointer to a service</returns>
Service* createService(Repo* repo);
/// <summary>
/// Function destroyes the service
/// </summary>
/// <param name="service">Pointer to the Service</param>
void destroyService(Service* service);
//<summary>
//Adds a country to the repository of countries
//</summary>
//<param name = "service"> Pointer to the Service<param>
//<param name = "name"> "string" - name for country<param>
//<param name = "continent"> "string" - name of the continent containing the country<param>
//<param name = "population"> "integer" - number (in millions) of people<param>
//<returns>1 - if the planet was added sucessfully, 0 otherwise</returns>
int addCountry(Service* service, char* name, char* continent, int population);
/// <summary>
/// Filter a repository countries after a given string
/// </summary>
/// <param name="service">Pointer to service</param>
/// <param name="string">The string after which we filter</param>
/// <returns>A new repository containing the filterd elements</returns>
Repo* filterByString(Service* service, void*(*function)(Country*), char* string);
//<summary>
//Deletes a country from the repository of countries
//</summary>
//<param name = "service"> Pointer to the Service<param>
//<param name = "name"> "string" - name for country<param>
//<returns>1 - if the planet was removed sucessfully, 0 otherwise</returns>
int deleteCountry(Service* service, char* name);
/// <summary>
/// Finds a country 
/// </summary>
/// <param name="service">Pointer to service</param>
/// <param name="name">The name of the country we are looking for</param>
/// <returns>-1 if the is not found, otherwise the position of the country in the repository</returns>
int findCountry(Service* service, char* name);
/// <summary>
/// Updates the population of two countries
/// </summary>
/// <param name="service">Pointer to service</param>
/// <param name="mCountry">The name of the country from which people leave</param>
/// <param name="newCountry">The name of the country where people move</param>
/// <param name="population">The amount of people which move</param>
/// <returns>0 if hte changes can not be made, 1 otherwise</returns>
int updateCountry(Service* service, char* mCountry, char* newCountry, int population);
/// <summary>
/// Undoes the last performed operation
/// </summary>
/// <param name="service">Pointer to the service</param>
/// <returns>1 if the operation can be undone, 0 otherwise</returns>
int undoOperation(Service* service);
/// <summary>
/// Redoes the last undone operation
/// </summary>
/// <param name="service">Pointer to the service</param>
/// <returns>1 if the operation can be redone, 0 otherwise</returns>
int redoOperation(Service* service);
void initializeCountries(Service* service);
void testService();

