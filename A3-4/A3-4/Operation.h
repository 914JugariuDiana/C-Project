#pragma once
#include "Country.h"

typedef struct {
	Country* country;
	char* operationName;
}Operation;

/// <summary>
/// Function creates an operation
/// </summary>
/// <param name="country">Pointer to a country</param>
/// <param name="operationName">Pointer to a string containing the name of an operation</param>
/// <returns>A pointer to a operation</returns>
Operation* createOperation(Country* country, char* operationName);
/// <summary>
/// Destroyes an operation
/// </summary>
/// <param name="operation">Pointer to an operation</param>
void destroyOperation(Operation* operation);
/// <summary>
/// Returns a country from an operation
/// </summary>
/// <param name="operation">Pointer to an operation</param>
/// <returns>A pointer to a country</returns>
Country* getCountry(Operation* operation);
/// <summary>
/// Gets an operation name
/// </summary>
/// <param name="operation">A pointer to an operation</param>
/// <returns>A pointer to a string containing the name of an operation</returns>
char* getOperationName(Operation* operation);
/// <summary>
/// Function creates an operation
/// </summary>
/// <param name="operation">Pointer to the operation to be copied</param>
/// <returns>A pointer to a operation</returns>
Operation* copyOperation(Operation* operation);