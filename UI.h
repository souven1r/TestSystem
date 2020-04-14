#pragma once
#include "User.h"
class UI
{
public:
	UI();
	void showSelector(); //������� ����
	void showLoginMenu(); //�����������
	void showRegisterMenu(); //�����������
	void showMainMenu(); //���� ������������
	void makeLogin(); //������� �����������
	void makeRegister(UserType); //������� �����������
	void makeLogOut(); // ������� ������������
private:
	User* user;
	void resetUser();
};