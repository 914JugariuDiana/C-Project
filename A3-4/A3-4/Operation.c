#include "Operation.h"
#include <string.h>
#include <stdlib.h>

Operation* createOperation(Country* country, char* operationName)
{
	Operation* operation;

	operation = malloc(sizeof(Operation));
	if (operation == NULL)
		return NULL;
	operation->country = country;
	operation->operationName = malloc(sizeof(char) * (strlen(operationName) + 1));
	if (operation->operationName == NULL)
		return NULL;
	strcpy(operation->operationName, operationName);

	return operation;
}

void destroyOperation(Operation* operation)
{
	if (operation == NULL) {
		return;
	}
	if (operation->operationName == NULL) {
		free(operation);
		return;
	}
	free(operation->operationName);
	destroyCountry(operation->country);
	free(operation);
}

Country* getCountry(Operation* operation)
{
	return operation->country;
}

char* getOperationName(Operation* operation)
{
	return operation->operationName;
}

Operation* copyOperation(Operation* operation)
{
	Operation* copy = createOperation(copyCountry(operation->country), operation->operationName);
	return copy;
}
