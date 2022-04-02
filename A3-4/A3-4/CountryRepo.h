#pragma once

#include "Country.h"

typedef struct {
	int size, capacity;
	Country** data;
}Repo;

Repo* createRepo();
/// <summary>
/// Destroies the repo and all its elements
/// </summary>
/// <param name="repo">Pointer to the Repo</param>
void destroyRepo(Repo* repo);

/// <summary>
/// 
/// </summary>
/// <param name="repo"></param>
/// <param name="country"></param>
/// <returns></returns>
int addToRepo(Repo* repo, Country* country);

/// <summary>
/// Deletes the country with the given name 
/// </summary>
/// <param name="repo">Pointer to the Repo</param>
/// <param name="name">Name of the country</param>
/// <returns>1 if the operation was succesfull, 0 otherwise</returns>
int deleteFromRepo(Repo* repo, char* name);

/// <summary>
/// Imitates a migration changing the population of 2 countries
/// </summary>
/// <param name="repo">Pointer to repo</param>
/// <param name="mCountry">The name of the country from where the people leave</param>
/// <param name="newCountry">The name of the country where people move</param>
/// <param name="population">The amount of people who move</param>
/// <returns>1 if the operation can be done, 0 otherwise </returns>
int updateRepo(Repo* repo, char* mCountry, char* newCountry, int population);

/// <summary>
/// Transforms all characters representing big letters into small letters
/// </summary>
/// <param name="str">Given string</param>
/// <returns> the address to the modified string </returns>
char* lowerCase(char* str);


//<summary>
//Finds all countries containing a given string
//</summary>
//<param name = "repo"> Pointer to the Repo<param>
//<param name = "string"> "string" - what we are looking for<param>
//<returns> A pointer to a repository of countries that contain the given string </returns>
int findElem(Repo* repo, char* string);

/// <summary>
/// Gets all elements from a repo
/// </summary>
/// <param name="repo">Pointer to the repo</param>
/// <returns>A repo and all its elements</returns>
Repo* getRepo(Repo* repo);

/// <summary>
/// Filters the elements from a repo
/// </summary>
/// <param name="repo">Pointer to a repo</param>
/// <param name="string">The string after which we filter the repo</param>
/// <returns>A repository</returns>
Repo* filterRepo(Repo* repo, char* string);
