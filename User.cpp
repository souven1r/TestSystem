#include "User.h"
const std::string USERS_FILE = "files\\users.dat";
const std::string RESULTS_FILE = "files\\results.dat";
std::vector<User*> User::users;
std::string User::getLogin() const
{
	return login;
}
bool User::isEmpty()
{
	return users.empty();
}
bool User::getLogIn() const
{
	return isLogIn;
}
void User::setLogIn(bool b)
{
	isLogIn = b;
}
void User::Load() {
	UserType type;
	std::ifstream file;
	file.open(USERS_FILE, std::ios::binary | std::ios_base::in);
	if (!file.is_open())
	{
		std::cout << "File wasnt opened\n";
		return;
	}
	int n = 0;
	file.read(reinterpret_cast<char*>(&n), sizeof(int));
	for(int i = 0; i < n;i++)
	{
		if (file.eof())
			break;
		file.read(reinterpret_cast<char*>(&type), sizeof(UserType));
		User* user;
		if (type == ADMIN)
		{
			user = new Admin();
		}
		else if (type == GUEST)
		{
			user = new Guest();
		}
		else
		{
			user = new Guest();
		}
		user->readUser(file);
		users.push_back(user);
	}
	std::cout << "LOAD: " << n << " users was loaded from file!\n";
	file.close();
}
void User::Save() {
	std::ofstream file;
	file.open(USERS_FILE, std::ios::binary | std::ios::trunc);
	int n = users.size();
	file.write(reinterpret_cast<char*>(&n), sizeof(int));
	for (auto user : users)
	{
		user->saveUser(file);
	}
	std::cout << "SAVE: file " << USERS_FILE << " was saved\n";
 	file.close();
}
bool User::Login(User*& user, std::string login, std::string password)
{
	bool result = false;
	for (auto u : users)
	{
		if (login == u->getLogin()) // проверка на совпадение логинов
		{
			if (password == u->password) // совпадение паролей
			{
				u->isLogIn = true; // юзер авторизован
				user = u; //user получает данные из массива всех пользователей
				result = true;
			}
			else // неверный пароль
			{
				std::cout << "Incorrect password\n";
				return false;
			}
		}
	}
	if (result == false) // совпадений не было
	{
		std::cout << "This user doesn't exist\n";
	}
	return result;
}
bool User::Add(User* user)
{
	for (auto u : users)
	{
		if (user->getLogin() == u->getLogin()) // проверка есть ли уже пользователь с таким логином
		{
			std::cout << "ERROR: This login already exists\n";
			return false;
		}
	}
	users.push_back(user);
	return true;
}
void Admin::saveUser(std::ofstream& file)
{
	UserType type = ADMIN;
	file.write(reinterpret_cast<char*>(&type), sizeof(UserType));
	file.write(reinterpret_cast<char*>(&login), sizeof(std::string));
	file.write(reinterpret_cast<char*>(&password), sizeof(std::string));
}
void Admin::readUser(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&login), sizeof(std::string));
	file.read(reinterpret_cast<char*>(&password), sizeof(std::string));
}
void Guest::saveUser(std::ofstream& file)
{
	UserType type = GUEST;
	file.write(reinterpret_cast<char*>(&type), sizeof(UserType));
	file.write(reinterpret_cast<char*>(&login), sizeof(std::string));
	file.write(reinterpret_cast<char*>(&password), sizeof(std::string));
	file.write(reinterpret_cast<char*>(&name), sizeof(std::string));
	file.write(reinterpret_cast<char*>(&surname), sizeof(std::string));
	file.write(reinterpret_cast<char*>(&adress), sizeof(std::string));
	file.write(reinterpret_cast<char*>(&phoneNumber), sizeof(long long));
	saveResults(file);
}
void Guest::readUser(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&login), sizeof(std::string));
	file.read(reinterpret_cast<char*>(&password), sizeof(std::string));
	file.read(reinterpret_cast<char*>(&name), sizeof(std::string));
	file.read(reinterpret_cast<char*>(&surname), sizeof(std::string));
	file.read(reinterpret_cast<char*>(&adress), sizeof(std::string));
	file.read(reinterpret_cast<char*>(&phoneNumber), sizeof(long long));
	loadResults(file);
}
void Guest::saveResults(std::ofstream& file)
{
	int size = results.size();
	file.write(reinterpret_cast<char*>(&size), sizeof(int));
	for (auto r : results)
	{
		file.write(reinterpret_cast<char*>(&r), sizeof(LastResult));
	}
}
void Guest::loadResults(std::ifstream& file)
{
	int size = 0;
	file.read(reinterpret_cast<char*>(&size), sizeof(int));
	for (int i = 0; i < size; i++)
	{
		LastResult r;
		file.read(reinterpret_cast<char*>(&r), sizeof(LastResult));
		results.push_back(r);
	}
}
void Admin::getData()
{
	std::cout << "Enter login: ";
	std::cin >> login;
	std::cout << "Enter password: ";
	std::cin >> password;
}
void Guest::getData()
{
	std::cout << "Enter login: ";
	std::cin >> login;
	std::cout << "Enter password: ";
	std::cin >> password;
	std::cout << "Enter name: ";
	std::cin >> name;
	std::cout << "Enter surname: ";
	std::cin >> surname;
	std::cout << "Enter adress: ";
	std::cin >> adress;
	std::cout << "Enter phone number: ";
	std::cin >> phoneNumber;
}
void Admin::printData() const
{
	std::cout << "login: " << getLogin() << std::endl;
}
void Guest::printData() const
{
	std::cout << "=============== "<< getLogin() << " ===============\n";
	std::cout << "* Name: " << name << " " << surname << std::endl;
	std::cout << "* Adress: " << adress << std::endl;
	std::cout << "* Phone number: +" << phoneNumber << std::endl;
	showTests();
}
void Admin::showMenu()
{
	bool loop = true;
	int input;
	while (loop)
	{
		std::cout << "============= ADMIN MENU =============\n";
		std::cout << "Enter 0 - to show all info about user\n";
		std::cout << "Enter 1 - to show all users\n";
		std::cout << "Enter 2 - to create user\n";
		std::cout << "Enter 3 - to change user's data\n";
		std::cout << "Enter 4 - to show all tests\n";
		std::cout << "Enter 5 - to add new test\n";
		std::cout << "Enter 6 - to change test\n";
		std::cout << "Enter 7 - to save tests\n";
		std::cout << "Enter 8 - to exit\n";
		std::cout << "Your choice: ";
		std::cin >> input;
		switch (input)
		{
			case 0:
				showUser();
				break;
			case 1:
				showUsers();
				break;
			case 2:
				createUser();
				break;
			case 3:
				changeUser();
				break;
			case 4:
				showTests();
				break;
			case 5:
				addTest();
				break;
			case 6:
				changeTest();
				break;
			case 8:
				loop = false;
				break;
			case 7:
				Test::Save();
				break;
			default:
				std::cout << "ERROR: Incorrect input, try again\n";
		}
	}
}
void Guest::showMenu()
{
	bool loop = true;
	int input;
	while (loop)
	{
		std::cout << "============= GUEST MENU =============\n";
		std::cout << "Enter 1 - to show your stats\n";
		std::cout << "Enter 2 - to pass test\n";
		std::cout << "Enter 3 - to exit\n";
		std::cout << "Your choice: ";
		std::cin >> input;
		switch (input)
		{
			case 1:
				showTests();
				break;
			case 2:
				passTest();
				break;
			case 3:
				loop = false;
				break;
			default:
				std::cout << "ERROR: Incorrect input, try again\n";
		}
	}
}
void Guest::showTests() const
{
	std::cout << "=============== TESTS ===============\n";
	for (int i = 0; i < Test::GetSize(); i++)
	{
		std::cout << "#" << i << ". " << Test::GetElement(i).getName();
		int grade = getGrade(Test::GetElement(i).getID()); // оценка за данный тест
		if (grade != -1) // если оценка есть - вывод оценки
		{
			std::cout << " mark: " << grade;
		}
		std::cout << "\n";
	}
}
int Guest::getGrade(int ID) const
{
	int result = -1;
	for (auto r : results)
	{
		if (r.questionID != ID)
			continue;
		if (r.mark > result)
			result = r.mark;
	}
	return result;
}
void Guest::passTest()
{
	if (Test::GetSize() < 1) // проверка есть ли тесты
	{
		std::cout << "There are no avaible tests\n";
		return;
	}
	int chose;
	while (true)
	{
		std::cout << "Enter number of test which you want to pass: ";
		std::cin >> chose;
		if (chose < 0 || chose >= Test::GetSize())
		{
			std::cout << "Wrong from 0 to " << Test::GetSize() - 1;
			continue;
		}
		LastResult result = Test::GetElement(chose).startTest(); // старт теста
		results.push_back(result); // добавление результата в массив
		break;
	}
		
}
void Admin::showUsers()
{
	std::cout << "============= USERS =============\n";
	int n = 0;
	for (auto u : users)
	{
		std::cout << "#" << n << ". " << u->getLogin() << "\n";
		n++;
	}
	std::cout << "Users count: " << n << std::endl;
}
void Admin::showUser()
{
	int id = 0;
	while (true)
	{
		std::cout << "Enter # of user which info you want to see: ";
		std::cin >> id;
		if (id < 0 || (size_t)id >= users.size())
		{
			std::cout << "Wrong #, try again (from 0 to " << users.size() - 1 << ")\n";
			continue;
		}
		users[id]->printData();
		break;
	}
}
void Admin::createUser()
{
	User* user;
	bool loop = true;
	char input;
	while (loop)
	{
		std::cout << "You want to create (a)dmin or (g)uest? (b - to back): ";
		std::cin >> input;
		if (tolower(input) == 'a')
			user = new Admin;
		else if (tolower(input) == 'g')
			user = new Guest;
		else if (tolower(input) == 'b')
			return;
		else
		{
			std::cout << "Incorrect input,try again:";
			continue;
		}
		user->getData();
		if (User::Add(user))
		{
			std::cout << "You successfully created a user\n";
			return;
		}
		else
			continue;
	}
}
void Admin::changeUser()
{
	bool loop = true;
	int id;
	while (loop)
	{
		std::cout << "Enter id of user you want to change: (-1 to back) ";
		std::cin >> id;
		if (id == -1)
		{
			return;
		}
		if (id < 0 || (size_t)id > users.size())
		{
			std::cout << "Incorrect id of users, try again\n";
		}
		users[id]->getData();
	}
}
void Admin::showTests()
{
	Test::Display();
}
void Admin::addTest()
{
	Test newTest;
	newTest.getData();
	Test::AddTest(newTest);
}
void Admin::changeTest()
{
	int id;
	while (true)
	{
		std::cout << "Enter # of test which you want to edit: ";
		std::cin >> id;
		if (id < 0 || id >= Test::GetSize())
		{
			std::cout << "Wrong from 0 to " << Test::GetSize() - 1;
			continue;
		}
		changeTest(id);
		break;
	}
}

void Admin::changeTest(int id)
{
	bool loop = true;
	int input;
	while (loop)
	{
		std::cout << "============= TEST EDIT =============\n";
		std::cout << "Enter 0 - to show all data\n";
		std::cout << "Enter 1 - to edit name of test\n";
		std::cout << "Enter 2 - to add question\n";
		std::cout << "Enter 3 - to edit question\n";
		std::cout << "Enter 4 - to delete question\n";
		std::cout << "Enter 5 - to delete this test\n";
		std::cout << "Enter 6 - to exit\n";
		std::cout << "Your choice: ";
		std::cin >> input;
		switch (input)
		{
		case 0:
			showTest(id);
			break;
		case 1:
			editTestName(id);
			break;
		case 2:
			addQuestion(id);
			break;
		case 3:
			editQuestion(id);
			break;
		case 4:
			deleteQuestion(id);
			break;
		case 5:
			deleteTest(id);
			loop = false;
			break;
		case 6:
			loop = false;
			break;
		default:
			std::cout << "ERROR: Incorrect input, try again\n";
		}
	}
}
void Admin::showTest(int id)
{
	Test::GetElement(id).printAllData();
}
void Admin::editTestName(int id)
{
	std::cin.ignore();
	std::string name;
	std::cout << "Enter name of test: ";
	std::getline(std::cin, name);
	Test::GetElement(id).setName(name);
	std::cout << "You successfully changed the name\n";
}
void Admin::addQuestion(int id)
{
	std::cin.ignore();
	Question quest = InputQuestion();
	Test::GetElement(id).addQuestion(quest);
}
void Admin::editQuestion(int id)
{
	if (Test::GetElement(id).getQuestionCount() < 1)
	{
		std::cout << "This test doesnt have any questions yet\n";
	}
	int input;
	while (true)
	{
		std::cout << "Enter # of question which you want to edit: ";
		std::cin >> input;
		std::cin.ignore();
		if (input < 0 || input >= Test::GetElement(id).getQuestionCount())
		{
			std::cout << "Invalid #, try again\n";
			continue;
		}
		Question quest = InputQuestion();
		Test::GetElement(id).setQuestion(input, quest);
		break;
	}
}
void Admin::deleteQuestion(int id)
{
	if (Test::GetElement(id).getQuestionCount() < 1)
	{
		std::cout << "This test doesnt have any questions yet\n";
	}
	int input;
	while (true)
	{
		std::cout << "Enter # of question which you want to delete: ";
		std::cin >> input;
		if (input < 0 || input >= Test::GetElement(id).getQuestionCount())
		{
			std::cout << "Invalid #, try again\n";
			continue;
		}
		Test::GetElement(id).deleteQuestion(input);
		break;
	}
}
void Admin::deleteTest(int id)
{
	char input;
	while (true)
	{
		std::cout << "Are you sure you want to delete this? (Y/N): ";
		std::cin >> input;
		if (tolower(input) == 'y')
		{
			Test::DeleteTest(id);
			break;
		}
		else if (tolower(input) == 'n')
			break;
		else
			std::cout << "Wrong answer, only 'y' or 'n'\n";
	}
}