#pragma once

#include "Country.h"

typedef void* TElem;
typedef void (*functionDestroy)(void*);

typedef struct {
	int size, capacity;
	TElem* data;
	functionDestroy destroy;
}Repo;

/// <summary>
/// Create a repository
/// </summary>
/// <param name="capacity">The capacity the repository can have</param>
/// <param name="destroy">Pointer to a function that can destroy the elements from the repository</param>
/// <returns>A pointer to the created repository</returns>
Repo* createRepo(int capacity, functionDestroy destroy);
/// <summary>
/// Destroies the repo and all its elements
/// </summary>
/// <param name="repo">Pointer to the Repo</param>
void destroyRepo(Repo* repo);
/// <summary>
/// Adds an elem to the repository
/// </summary>
/// <param name="repo">A pointer to the repository</param>
/// <param name="elem">The element we want to add to the country</param>
/// <returns>1 if the operation was succesfull, 0 otherwise</returns>
int addToRepo(Repo* repo, TElem elem); 
/// <summary>
/// Deletes the country with the given name 
/// </summary>
/// <param name="repo">Pointer to the Repo</param>
/// <param name="position">The position of the element</param>
void deleteFromRepo(Repo* repo, int position);
/// <summary>
/// Updates the field of an element from the repository
/// </summary>
/// <param name="repo">A pointer the repository</param>
/// <param name="pos">the position of the element in the repository</param>
/// <param name="value">the new value we want to set</param>
/// <param name="field">A pointer to a function that sets the value we want</param>
void updateRepo(Repo* repo, int pos, int value, void (*field)(void*, int));
/// <summary>
/// Transforms all characters representing big letters into small letters
/// </summary>
/// <param name="str">Given string</param>
/// <returns> the address to the modified string </returns>
char* lowerCase(char* str);
//<summary>
//Finds a country containing a given string
//</summary>
//<param name = "repo"> Pointer to the Repo<param>
//<param name = "string"> "string" - what we are looking for<param>
//<returns> The position of the elem we are looking for </returns>
int findElem(Repo* repo, void* (*field)(void*), char* string);
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
Repo* filterRepo(Repo* repo, void* (*function)(TElem*), char* string);
/// <summary>
/// Order a repository elements
/// </summary>
/// <param name="repo">Pointer to the repository</param>
/// <param name="function">A getter function for the element after which we order </param>
/// <returns>A pointer to an ordered repo</returns>
Repo* orderRepo(Repo* repo);
void testRepo();
Repo* copyRepo(Repo* repo);