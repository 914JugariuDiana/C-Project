#include "Country.h"
#include "Repo.h"
#include "UI.h"
#include <crtdbg.h>

int main() {
	Repo* repo = createRepo(2, &destroyCountry);
	Service* service = createService(repo);
	UI* ui = createUI(service);
	startUI(ui);
	destroyUI(ui);
	testCountry();
	testService();
	testRepo();
	_CrtDumpMemoryLeaks();
	return 0;
}