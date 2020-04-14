#include "UI.h"

int main()
{
	UI ui;
	User::Load();
	Test::Load();
	ui.showSelector();
	system("pause");
}