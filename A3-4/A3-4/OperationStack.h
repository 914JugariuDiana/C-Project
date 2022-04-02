#pragma once
#include "Repo.h"
#include "Operation.h"

typedef struct {
	Repo* stackOperation;
}StackOperation;

/// <summary>
/// Function creates a stack of operations
/// </summary>
/// <returns>A pointer to the stack</returns>
StackOperation* createStackOperation();
/// <summary>
/// Function destroyes a stack of operations
/// </summary>
/// <param name="stackOperation">A pointer to the stack we want to destroy</param>
void destroyStackOperation(StackOperation* stackOperation);
/// <summary>
/// Functions adds an elemnt to the stack
/// </summary>
/// <param name="StackOPeration">A pointer to the stack</param>
/// <param name="operation">A pointer to the operation we want to add</param>
void push(StackOperation* StackOPeration, Operation* operation);
/// <summary>
/// Function pops an element from the stack
/// </summary>
/// <param name="StackOPeration">A pointer to the stack</param>
/// </summary>
/// <returns>A pointer to the element that was removed from the stack</returns>
Operation* pop(StackOperation* stackOperation);