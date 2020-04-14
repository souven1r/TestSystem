#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
struct LastResult // результат
{ 
	int questionID = -1; // уникальный номер теста
	int mark = 0; // оценка
};
struct Answer
{
	std::string answer; // текст ответа
	bool isCorrect = false; // true если верный ответ
};
struct Question
{
	std::string question; // текст вопроса
	Answer answers[4]; // массив из 4-ех варинтов ответа
};
Question InputQuestion();
class Test
{
public:
	Test();
	static void Load(); // загрузка из файла тестов
	static void Save(); // сохранение тестов в файл
	static void DeleteTest(int); // удаление теста
	static void AddTest(Test); // добавление теста
	static int GetSize(); // кол-во тестов
	static Test& GetElement(int); // обращение к элементу
	static void Display(); // вывод всех тестов
	LastResult startTest(); // старт теста

	int getID() const; // вывести уникальный номер
	inline std::string getName() const; // вывести название теста
	inline int getQuestionCount() const; // вывести кол-во вопросов
	void setName(std::string); // изменить название
	void printAllData() const; // вывести все вопросы с вариантами ответа
	void getData(); // ввод данных
	void addQuestion(Question); // добавить вопрос в массив
	void setQuestion(int, Question); // изменить вопрос по индексу
	void deleteQuestion(int); // удалить вопрос по индексу
private:
	static int count; // счетчик для уникальных номеров
	int ID;
	std::string name;
	std::vector<Question> questions; // массив с вопросами
	static std::vector<Test> tests; // статический массив с тестами
	void loadQuestions(); // загрузка вопросов
	void saveQuestions(); // сохранение вопросов
};