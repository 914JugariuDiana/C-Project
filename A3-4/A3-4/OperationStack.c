#include "OperationStack.h"
#include <stdlib.h>

void push(StackOperation* stackOperation, Operation* operation)
{
	addToRepo(stackOperation->stackOperation, operation); 
}

Operation* pop(StackOperation* stackOperation)
{
	Operation* operation;

	if (stackOperation->stackOperation->size == 0)
		return NULL;
	operation = copyOperation(stackOperation->stackOperation->data[stackOperation->stackOperation->size - 1]);
	destroyOperation(stackOperation->stackOperation->data[stackOperation->stackOperation->size - 1]);
	stackOperation->stackOperation->size--;

	return operation;
}