#pragma once
#include "Test.h"
enum UserType{GUEST,ADMIN};
class User
{
public:
	std::string getLogin() const;
	virtual void showMenu() = 0; // меню юзера
	virtual void getData() = 0; // ввод данных
	virtual void printData() const = 0; // вывод данных
	static void Load(); // загрузка с файла
	static void Save(); // сохранение файла
	static bool Add(User*); // попытка регистрации
	static bool Login(User*&, std::string, std::string); // попытка авторизации
	static bool isEmpty(); // есть ли юзеры
	bool getLogIn() const; // сейчас авторизован?
	void setLogIn(bool); // изменить состояние авторизации
protected:
	virtual void saveUser(std::ofstream&) = 0; // сохранить в файл
	virtual void readUser(std::ifstream&) = 0; // загрузить из файла
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
	void showUsers(); // все пользователи
	void showUser(); // все данные одного пользователя
	void createUser(); // создать пользователя
	void changeUser(); // изменить данные
	void showTests(); // все тесты
	void addTest(); // добавить новый тест
	void changeTest(); // меню теста
	void showTest(int); // все вопросы и ответы одно теста
	void changeTest(int); // 
	void editTestName(int); // изменить название теста
	void addQuestion(int); // добавить вопрос
	void editQuestion(int); // изменить вопрос
	void deleteQuestion(int); // удалить вопрос
	void deleteTest(int); // удалить тест
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

	void loadResults(std::ifstream&); // загрузка пред. резульатов
	void saveResults(std::ofstream&); // сохранение пройденных тестов
	void showTests() const; // тесты и оценки
	void passTest(); // пройти тест
	int getGrade(int) const; // узнать оценку
};