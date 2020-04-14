#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
struct LastResult // ���������
{ 
	int questionID = -1; // ���������� ����� �����
	int mark = 0; // ������
};
struct Answer
{
	std::string answer; // ����� ������
	bool isCorrect = false; // true ���� ������ �����
};
struct Question
{
	std::string question; // ����� �������
	Answer answers[4]; // ������ �� 4-�� �������� ������
};
Question InputQuestion();
class Test
{
public:
	Test();
	static void Load(); // �������� �� ����� ������
	static void Save(); // ���������� ������ � ����
	static void DeleteTest(int); // �������� �����
	static void AddTest(Test); // ���������� �����
	static int GetSize(); // ���-�� ������
	static Test& GetElement(int); // ��������� � ��������
	static void Display(); // ����� ���� ������
	LastResult startTest(); // ����� �����

	int getID() const; // ������� ���������� �����
	inline std::string getName() const; // ������� �������� �����
	inline int getQuestionCount() const; // ������� ���-�� ��������
	void setName(std::string); // �������� ��������
	void printAllData() const; // ������� ��� ������� � ���������� ������
	void getData(); // ���� ������
	void addQuestion(Question); // �������� ������ � ������
	void setQuestion(int, Question); // �������� ������ �� �������
	void deleteQuestion(int); // ������� ������ �� �������
private:
	static int count; // ������� ��� ���������� �������
	int ID;
	std::string name;
	std::vector<Question> questions; // ������ � ���������
	static std::vector<Test> tests; // ����������� ������ � �������
	void loadQuestions(); // �������� ��������
	void saveQuestions(); // ���������� ��������
};