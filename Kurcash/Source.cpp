#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Accounts.cpp"
#include <clocale>

using namespace std;



void loginMenu();

void authentication(string username, string password);

void loginAsClient(string curUsername);

void loginAsAdmin(string curUsername);


int main() {
	setlocale(LC_ALL, "Russina");

	
	ofstream usersFile;
	usersFile.open("users.txt");
	string admin = "admin 123 h";
	if (!usersFile.is_open()) {
		cout << "файл не открыть" << endl;
	}
	else {
		usersFile << "\n" << admin;
	}

	loginMenu();
}

void loginMenu() {
	User users;
	int a = 0;

	cout << "логин: "; cin >> users.username;
	while (isdigit(users.username[0]))
	{
		cout << "неправильный формата логина " << endl;
		cout << "повторите ещё раз, логин: "; cin >> users.username;
	}

	cout << "пароль: "; cin >> users.password;

	authentication(users.username, users.password);
}

void authentication(string username, string password) {
	vector<User> vAllUsers = getUsersVec();
	bool userIsFound = false;
	for (int i = 0; i < vAllUsers.size(); i++)
	{
		if (username == vAllUsers[i].username && password == vAllUsers[i].password)
		{
			if (vAllUsers[i].role == 'w') loginAsClient(username);
			else if (vAllUsers[i].role == 'a') loginAsAdmin(username);
			else if (vAllUsers[i].role == 'h') loginAsAdmin(username);
			else cout << "не удалось определить права доступа" << endl;
			userIsFound = true;
			break;
		}
	}
	if (!userIsFound) {
		cout << "Пользователь не найден! повторите ещё раз " << endl;
		loginMenu();
	}
}



void loginAsAdmin(string curUsername) {
	cout << "меню главного админа" << endl
		<< "====================================" << endl
		<< "1. Редоктерование пользователей" << endl
		<< "2. " << endl
		<< "3. " << endl
		<< "4. " << endl
		<< "5. Выйти" << endl;
	int pick;
	cin >> pick;

	switch (pick)
	{

	case 1:
		editUsersMenu(curUsername);
		break;

	case 2:

		break;

	case 3:

		break;

	case 4:

		break;

	case 5:
		loginMenu();
		break;

	default:
		break;
	}

}

void loginAsClient(string curUsername) {
	cout << "loged in as worker" << endl;

}