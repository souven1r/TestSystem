#pragma once
#include "Test.h"
enum UserType{GUEST,ADMIN};
class User
{
public:
	std::string getLogin() const;
	virtual void showMenu() = 0; // ���� �����
	virtual void getData() = 0; // ���� ������
	virtual void printData() const = 0; // ����� ������
	static void Load(); // �������� � �����
	static void Save(); // ���������� �����
	static bool Add(User*); // ������� �����������
	static bool Login(User*&, std::string, std::string); // ������� �����������
	static bool isEmpty(); // ���� �� �����
	bool getLogIn() const; // ������ �����������?
	void setLogIn(bool); // �������� ��������� �����������
protected:
	virtual void saveUser(std::ofstream&) = 0; // ��������� � ����
	virtual void readUser(std::ifstream&) = 0; // ��������� �� �����
	bool isLogIn;
	std::string login;
	std::string password;
	static std::vector<User*> users;
};
class Admin : public User
{
public:
	void showMenu();
	void getData();
	void printData() const;

private:
	void saveUser(std::ofstream&);
	void readUser(std::ifstream&);
	void showUsers(); // ��� ������������
	void showUser(); // ��� ������ ������ ������������
	void createUser(); // ������� ������������
	void changeUser(); // �������� ������
	void showTests(); // ��� �����
	void addTest(); // �������� ����� ����
	void changeTest(); // ���� �����
	void showTest(int); // ��� ������� � ������ ���� �����
	void changeTest(int); // 
	void editTestName(int); // �������� �������� �����
	void addQuestion(int); // �������� ������
	void editQuestion(int); // �������� ������
	void deleteQuestion(int); // ������� ������
	void deleteTest(int); // ������� ����
};
class Guest : public User
{
public:
	void showMenu();
	void getData();
	void printData() const;

private:
	void saveUser(std::ofstream&);
    void readUser(std::ifstream&);
	std::string name;
	std::string surname;
	std::string adress;
	long long phoneNumber;
	std::vector<LastResult> results;

	void loadResults(std::ifstream&); // �������� ����. ����������
	void saveResults(std::ofstream&); // ���������� ���������� ������
	void showTests() const; // ����� � ������
	void passTest(); // ������ ����
	int getGrade(int) const; // ������ ������
};