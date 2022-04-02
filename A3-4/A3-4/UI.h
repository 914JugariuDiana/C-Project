#pragma once
#include "service.h"

typedef struct {
	Service* service;
}UI;

UI* createUI(Service* service);

void destroyUI(UI* ui);
void startUI(UI* ui);
int add(UI* ui);
int delete(UI* ui);
Repo* filter(UI* ui, void*(*filter)(Country*));
void printRepo(Repo* repo);
int update(UI* ui);
int undo(UI* ui);
int redo(UI* ui);

