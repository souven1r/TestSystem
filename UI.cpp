#include "UI.h"
UI::UI()
{
	user = nullptr;
}
void UI::resetUser()
{
	if (user != nullptr)
	{
		user->setLogIn(false);
		user = nullptr;
	}
}
void UI::showSelector()
{
	int input;
	bool loop = true;
	while (loop)
	{
		std::cout << "=============== Testing system ===============\n";
		std::cout << "Enter 1 - to login\n";
		std::cout << "Enter 2 - to register\n";
		std::cout << "Enter 3 - to show your menu\n";
		std::cout << "Enter 4 - to log out\n";
		std::cout << "Enter 5 - to save users\n";
		std::cout << "Enter 6 - to exit\n";
		std::cout << "Your choice: ";
		std::cin >> input;
		switch (input)
		{
			case 1:
				showLoginMenu();
				break;
			case 2:
				showRegisterMenu();
				break;
			case 3:
				showMainMenu();
				break;
			case 4:
				makeLogOut();
				break;
			case 5:
				User::Save();
				break;
			case 6:
				loop = false;
				break;
			default:
				std::cout << "Incorrect Input,try again\n";
				break;
		}
	}
}
void UI::makeLogOut()
{
	if (user == nullptr)
	{
		std::cout << "You are already logged out\n";
		return;
	}
	resetUser();
	std::cout << "You have successfully logged out\n";
}
void UI::showLoginMenu()
{
	if (user != nullptr)
	{
		std::cout << "Are you already logged in\n";
		return;
	}
	makeLogin();
}
void UI::showRegisterMenu()
{
	if (user != nullptr)
	{
		std::cout << "Are you already logged in\n";
		return;
	}
	if (User::isEmpty()) //если юзеров нет - тогда регистрация админа
	{
		makeRegister(ADMIN);
	}
	else // регистрация гостя
	{
		makeRegister(GUEST);
	}
}
void UI::showMainMenu()
{
	if (user == nullptr)
	{
		std::cout << "You must to login to use it\n";
		return;
	}
	user->showMenu();
}
void UI::makeLogin()
{
	resetUser();
	std::string login, password;
	std::cout << "Enter login: ";
	std::cin >> login;
	std::cout << "Enter password: ";
	std::cin >> password;
	if (User::Login(user, login, password))
	{
		std::cout << "login > success\n";
	}
	else
	{
		std::cout << "login > error\n";
	}

}
void UI::makeRegister(UserType type)
{
	User* user;
	if (type == ADMIN)
		user = new Admin();
	else if (type == GUEST)
		user = new Guest();
	else
		user = new Guest();

	user->getData();
	if (User::Add(user))
	{
		std::cout << "create > success\n";
	}
	else
		std::cout << "create > error\n";
}