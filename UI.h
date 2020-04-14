#pragma once
#include "User.h"
class UI
{
public:
	UI();
	void showSelector(); //Главное меню
	void showLoginMenu(); //Авторизация
	void showRegisterMenu(); //Регистрация
	void showMainMenu(); //Меню пользователя
	void makeLogin(); //попытка авторизации
	void makeRegister(UserType); //попытка регистрации
	void makeLogOut(); // сменить пользователя
private:
	User* user;
	void resetUser();
};