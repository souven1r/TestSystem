#include "Test.h"

const std::string TESTS_FILE = "files/tests.dat";
const std::string QUESTIONS_FILE = "files/questions/";
std::vector<Test> Test::tests;
int Test::count = 0; // ���-�� ��������� ������(��� ����������� ID'a)
const int MAX_GRADE = 12; // ����. ������

void SaveStr(std::ofstream& file, std::string& str) // ���������� ������ � ��������� � ����
{
	size_t size = str.size();
	file.write(reinterpret_cast<char*>(&size), sizeof(size));
	file.write(reinterpret_cast<char*>(&str[0]), size);
}
void LoadStr(std::ifstream& file, std::string& str) // �������� ������ � ��������� � �����
{
	size_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	str.resize(size);
	file.read(reinterpret_cast<char*>(&str[0]), size);
}
void Test::loadQuestions() // �������� �������� �� �����
{
	std::ifstream file;
	std::string path = QUESTIONS_FILE; // ���������� � ���������
	path += (std::to_string(ID) + ".dat"); // ��� ���� � ���������
	file.open(path, std::ios::binary | std::ios_base::in);
	if (!file.is_open())
	{
		std::cout << "File wasnt opened\n";
		return;
	}
	int size = 0;
	file.read(reinterpret_cast<char*>(&size), sizeof(int)); // ���-�� �������� � �����
	for(int i = 0; i < size; i++)
	{
		if (file.eof())
			break;
		Question q;
		LoadStr(file, q.question);
		for (int i = 0; i < 4; i++) // �������� ��������� ������
		{
			file.read(reinterpret_cast<char*>(&q.answers[i].isCorrect), sizeof(bool));
			LoadStr(file, q.answers[i].answer);
		}
		questions.push_back(q); // ���������� ������� � ������ ��������
	}
	file.close();
}
void Test::saveQuestions() // ���������� � ����
{
	std::ofstream file;
	std::string path = QUESTIONS_FILE;
	path += (std::to_string(ID) + ".dat");
	file.open(path, std::ios::binary | std::ios::trunc); // �������� � ��������� �����������
	if (!file.is_open())
	{
		std::cout << "File wasnt opened\n";
		return;
	}
	int size = questions.size();
	file.write(reinterpret_cast<char*>(&size), sizeof(int)); // ���������� ���-�� ��������
	for (auto q : questions)
	{
		SaveStr(file, q.question); // ���������� ������ � ��������
		for (int i = 0; i < 4; i++)
		{
			file.write(reinterpret_cast<char*>(&q.answers[i].isCorrect), sizeof(bool));
			SaveStr(file, q.answers[i].answer);
		}
	}
	file.close();
}
void Test::Load()
{

	std::ifstream file;
	file.open(TESTS_FILE, std::ios::binary | std::ios_base::in);
	if (!file.is_open())
	{
		std::cout << "File wasnt opened\n";
		return;
	}
	file.read(reinterpret_cast<char*>(&(Test::count)), sizeof(int)); // ������� ��������� ������(��� ���������� �������)
	int n = 0;
	file.read(reinterpret_cast<char*>(&(n)), sizeof(int)); // ���-�� ��������
	for(int i = 0; i < n; i++)
	{
		if (file.eof())
			break;
		Test test;
		file.read(reinterpret_cast<char*>(&test.ID), sizeof(int));
		LoadStr(file, test.name);
		test.loadQuestions();
		tests.push_back(test);
	}
	std::cout << "LOAD: " << n << " tests was loaded from file!\n";
	file.close();
}
void Test::Save()
{
	std::ofstream file;
	file.open(TESTS_FILE, std::ios::binary | std::ios::trunc);
	if (!file.is_open())
	{
		std::cout << "File wasnt opened\n";
		return;
	}
	int size = tests.size();
	file.write(reinterpret_cast<char*>(&Test::count), sizeof(int));
	file.write(reinterpret_cast<char*>(&size), sizeof(int));
	for (auto t : tests)
	{
		file.write(reinterpret_cast<char*>(&t.ID), sizeof(int));
		SaveStr(file, t.name);
		t.saveQuestions();
	}
	std::cout << "SAVE: file " << TESTS_FILE << " was saved\n";
	file.close();
}
LastResult Test::startTest()
{
	int n = 0; // ���-�� ��������
	int correct = 0; // ���������� �������
	int input;
	for (auto q : questions)
	{
		n++;
		std::cout << "============ Question #" << n << " ============\n";
		std::cout << q.question << "\n";
		for (int i = 0; i < 4; i++)
		{
			std::cout << "Enter " << i + 1 << " to - " << q.answers[i].answer << std::endl;
		}
		while (true)
		{
			std::cout << "Your answer: ";
			std::cin >> input;
			if (input < 1 || input > 4)
			{
				std::cout << "Incorrect input, try again\n";
				continue;
			}
			if (q.answers[input - 1].isCorrect) // ���� ����� ������
			{
				std::cout << "ANSWER: Correct\n";
				correct++;
			}
			else // ���� ����� ��������
			{
				std::cout << "ANSWER: Wrong\n";
			}
			break;
		}
	}
	LastResult result;
	result.mark = correct * MAX_GRADE / questions.size(); // ��������� ������ �� ������ ���-�� ��������
	result.questionID = ID; // ���������� ����� �����
	std::cout << "Result: " << correct << " correct of " << questions.size() << std::endl; // ����� ����������
	std::cout << "Your mark: " << result.mark << std::endl; 
	return result;
}
int Test::getID() const
{
	return ID;
}
std::string Test::getName() const
{
	return name;
}
void Test::setName(std::string name)
{
	this->name = name;
}
void Test::Display() // ����� ���� ������
{
	int i = 0;
	std::cout << "============== TESTS ==============\n";
	for (auto t : tests)
	{
		std::cout << "#" << i << ". " << t.getName() << "\n";
		i++;
	}
	std::cout << "Tests count: " << i << std::endl;
}
int Test::getQuestionCount() const
{
	return questions.size();
}
Test::Test()
{
	ID = count;
	count++;
}
void Test::DeleteTest(int i)
{
	if (i < 0 || (size_t)i >= tests.size())
	{
		std::cout << "ERROR: Unable to delete test, test by this number does not exist\n";
		return;
	}
	std::string path = QUESTIONS_FILE;
	path += (std::to_string(tests[i].ID) + ".dat");
	std::remove(path.c_str());
	tests.erase(tests.begin() + i);
	std::cout << "INFO: Test by number " << i << " was deleted and file was saved\n";
	Save();
}
void Test::deleteQuestion(int id)
{
	if (id < 0 || id >= getQuestionCount())
		return;
	questions.erase(questions.begin() + id);
	std::cout << "INFO: Question by number " << id << " was deleted\n";
}
void Test::setQuestion(int id, Question quest)
{
	if (id < 0 || id >= getQuestionCount())
		return;
	questions[id] = quest;
}
void Test::getData()
{
	std::cin.ignore();
	std::cout << "Enter name of test: ";
	std::getline(std::cin, name);
	bool loop = true;
	while (loop)
	{
		if (questions.size() > 4)
		{
			char input;
			std::cout << "You want to add one more question(Y/N): ";
			std::cin >> input;
			std::cin.ignore();
			if (tolower(input) == 'y') {}
			else if (tolower(input) == 'n')
				break;
			else
			{
				std::cout << "Wrong input, only 'y' or 'n'!\n";
				continue;
			}
		}
		addQuestion(InputQuestion());
	}
}
void Test::addQuestion(Question question)
{
	questions.push_back(question);
	std::cout << "questions size: " << questions.size() << std::endl;
}
Question InputQuestion() // �������� �������
{
	Question quest;
	std::cout << "Enter text of question: ";
	std::getline(std::cin, quest.question);
	bool isCorrectAnswerPresent = false; // ������������ �� ��� ������ �����
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Enter answer option # " << i + 1 << ": ";
		std::getline(std::cin, quest.answers[i].answer);
		if (i == 3 && !isCorrectAnswerPresent) // ���� ����������� ������ ��� ���, � ������ ��������� - �� ����� ����������
		{
			quest.answers[i].isCorrect = true;
			isCorrectAnswerPresent = true;
		}
		if (!isCorrectAnswerPresent) // ���� ������� ������ ��� ��� ���������� ��� ������
		{
			while (true)
			{
				char input;
				std::cout << "This is the right one? (Y/N): ";
				std::cin >> input;
				std::cin.ignore();
				if (tolower(input) == 'y')
				{
					quest.answers[i].isCorrect = true;
					isCorrectAnswerPresent = true;
					break;
				}
				else if (tolower(input) == 'n')
					break;
				else 
					std::cout << "Wrong input, only 'y' or 'n'!\n";
			}
		}
	}
	return quest;
}
int Test::GetSize()
{
	return tests.size();
}
Test& Test::GetElement(int i)
{
	if (i < 0 || (size_t)i >= tests.size())
	{
		std::cout << "error\n";
		Test t;
		return t;
	}
	return tests[i];
}
void Test::AddTest(Test t)
{
	tests.push_back(t);
}
void Test::printAllData() const
{
	std::cout << "============== " << getName() << " ==============\n";
	int qC = 0;
	for (auto q : questions)
	{
		std::cout << "#" << qC << ". " << q.question << std::endl;
		for (int i = 0; i < 4; i++)
		{
			std::cout << "* " << i + 1 << ". " << q.answers[i].answer << std::endl;
		}
		std::cout << std::endl;
		qC++;
	}
	std::cout << "Questions count: " << qC << std::endl;
}