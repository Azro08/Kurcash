#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<windows.h>

using namespace std;

typedef struct User {
	char username[15], password[16];
	char role;
}User;

void deleteUser(string curUser, string username);
void printAllUsers(string curUser);
bool checkIfUserExists(string username);
void editUsername(string curUser, string username);
void editUserPassword(string curUser, string username);
void editUserRole(string curUser, string username);
void addUser(string curUsername, string username, string password, char role);
char getUserRole(string username);
string getUserToEdit(string curUsername);
void loginAsAdmin(string curUsername);

vector <User> getUsersVec() {
	string userLine;
	User tempUsers;
	ifstream usersFile;
	vector<User> vUsers;
	int usersAmount = 0;

	usersFile.open("users.txt");

	if (!usersFile.is_open()) {
		cout << "файл не открыть" << endl;
	}
	else {
		while (getline(usersFile, userLine))
		{
			usersFile >> tempUsers.username >> tempUsers.password >> tempUsers.role;
			vUsers.push_back(tempUsers);
		}
	}
	return vUsers;
}

void editUsersMenu(string curUsername) {
	cout << "====================================" << endl
		 << "1. удалить аккаунт" << endl
		 << "2. изменить пароль" << endl
		 << "3. изменить username" << endl
		 << "4. изменить руль" << endl
		 << "5. добавить аккаунт" << endl
		 << "6. просмотр всех пользователей" << endl
		 << "7. Назад" << endl;

	int pick;
	string username, password;
	char role;

	cin >> pick;

	switch (pick)
	{

	case 1:
		username = getUserToEdit(curUsername);
		deleteUser(curUsername, username);
		break;

	case 2:
		username = getUserToEdit(curUsername);
		editUserPassword(curUsername, username);
		break;

	case 3:
		username = getUserToEdit(curUsername);
		editUsername(curUsername ,username);
		break;

	case 4:
		username = getUserToEdit(curUsername);
		editUserRole(curUsername, username);
		break;

	case 5:
		cout << "нажимайти 'n' чтобы выйти" << endl;
		cout << "логин: "; cin >> username; 
		if (username == "n") editUsersMenu(curUsername);
		else if (checkIfUserExists(username) && username != "e") {
			cout << "пользователь существует!" << endl;
			editUsersMenu(username);
		}
		else
		{
			cout << "пароль: "; cin >> password;
			cout << "руль: "; cin >> role;
			while (role != 'a' && role != 'w' && role != 'n')
			{
				cout << "руль не существует, Выйти? (n)" << endl;
				cin >> role;
				if (role == 'n') editUsersMenu(curUsername);
			}
			addUser(curUsername ,username, password, role);
		}
		break;

	case 6:
		printAllUsers(curUsername);
		break;

	case 7:
		loginAsAdmin(curUsername);
		break;

	default:
		break;
	}

}

string getUserToEdit(string curUsername) {
	vector<User> allUsers = getUsersVec();
	string pickedUser = "";
	int pick;

	cout << "логин:" << endl << "====================================" << endl;
	for (int i = 0; i < allUsers.size(); i++)
	{
		cout << i << ". " << allUsers[i].username  << endl << "    " << allUsers[i].role << endl << endl;
	}
	cout << allUsers.size() << ". назад" << endl;


	cin >> pick;

	while (pick < 0 || (pick > allUsers.size() - 1))
	{
		cout << "error! ещё раз!" << endl;
		cin >> pick;
	}
	
	if (pick == allUsers.size()) editUsersMenu(curUsername);
	else pickedUser = allUsers[pick].username;
	return pickedUser;
}

char getUserRole(string username) {

	vector<User> allUsers = getUsersVec();
	char role = 'a';

	for (int i = 0; i < allUsers.size(); i++)
	{
		if (username == allUsers[i].username) role = allUsers[i].role;
	}
	return role;
}

void deleteUser(string curUser, string username) {
	string userLine;
	vector<User> allUsers = getUsersVec();
	ofstream new_users_file;
	User user;
	fstream users_file;

	char toDelteUserRole = getUserRole(username);
	char curUserRole = getUserRole(curUser);

	if (toDelteUserRole == 'h') {
		cout << "аккаунт главного админа не может быть удален" << endl;
		editUsersMenu(curUser);
	}
	else if (curUserRole == 'a' && toDelteUserRole == 'a') {
		cout << "только главный админ имеет доступ к удалению аккаунта админа" << endl;
		editUsersMenu(curUser);
	}

	vector<string> newUsersVec;

	for (int i = 0; i < allUsers.size(); i++)
	{
		string curUsername = allUsers[i].username;
		if (username != allUsers[i].username)
		{
			newUsersVec.push_back(curUsername + " " + allUsers[i].password + " " + allUsers[i].role);
		}
	}

	new_users_file.open("users.txt"); //to clear the file
	users_file.open("users.txt");

	if (!users_file.is_open()) {
		cout << "файл не открыть" << endl;
	}
	else {
		for (size_t i = 0; i < newUsersVec.size(); i++)
		{
			users_file << "\n" << newUsersVec[i];
		}
	}
	users_file.close();
	editUsersMenu(curUser);

}

void editUsername(string curUser, string username) {
	char toEditUserRole = getUserRole(username);
	char curUserRole = getUserRole(curUser);

	vector<User> allUsers = getUsersVec();
	User user;
	fstream users_file;

	if (curUserRole == 'a' && toEditUserRole == 'a') {
		cout << "только главный админ имеет доступ к редоктерованию аккаунта админа" << endl;
		editUsersMenu(curUser);
	}
	else if (toEditUserRole == 'h' && curUserRole != 'h') cout << "главный аккаунт админа не может быит редоктерован" << endl;
	else
	{
		vector<string> newUsersVec;

		for (int i = 0; i < allUsers.size(); i++)
		{
			string curUsername = allUsers[i].username;
			if (username == allUsers[i].username)
			{
				string newUsernmae;
				cout << "введите новый логин: "; cin >> newUsernmae;
				newUsersVec.push_back(newUsernmae + " " + allUsers[i].password + " " + allUsers[i].role);
			}
			else
			{
				newUsersVec.push_back(curUsername + " " + allUsers[i].password + " " + allUsers[i].role);
			}
		}


		users_file.open("users.txt");

		if (!users_file.is_open()) {
			cout << "файл не открыть" << endl;
		}
		else {
			for (size_t i = 0; i < newUsersVec.size(); i++)
			{
				users_file << "\n" << newUsersVec[i];
			}
		}
		users_file.close();
	}
	editUsersMenu(curUser);
}

void editUserPassword(string curUser, string username) {
	char toEditUserRole = getUserRole(username);
	char curUserRole = getUserRole(curUser);

	vector<User> allUsers = getUsersVec();
	User user;
	fstream users_file;

	if (curUserRole == 'a' && toEditUserRole == 'a') {
		cout << "только главный админ имеет доступ к редоктерованию аккаунта админа" << endl;
		editUsersMenu(curUser);
	}
	else if (toEditUserRole == 'h' && curUserRole != 'h') cout << "главный аккаунт админа не может быит редоктерован" << endl;
	else
	{
		vector<string> newUsersVec;

		for (int i = 0; i < allUsers.size(); i++)
		{
			string curUsername = allUsers[i].username;
			if (username == allUsers[i].username)
			{
				string newPassword;
				cout << "введите новый пароль: "; cin >> newPassword;
				newUsersVec.push_back(curUsername + " " + newPassword + " " + allUsers[i].role);
			}
			else
			{
				newUsersVec.push_back(curUsername + " " + allUsers[i].password + " " + allUsers[i].role);
			}
		}


		users_file.open("users.txt");

		if (!users_file.is_open()) {
			cout << "файл не открыть" << endl;
		}
		else {
			for (size_t i = 0; i < newUsersVec.size(); i++)
			{
				users_file << "\n" << newUsersVec[i];
			}
		}
		users_file.close();
	}
	editUsersMenu(curUser);
}

void editUserRole(string curUser, string username) {
	char toEditUserRole = getUserRole(username);
	char curUserRole = getUserRole(curUser);

	vector<User> allUsers = getUsersVec();
	User user;
	fstream users_file;

	if (curUserRole == 'a' && toEditUserRole == 'a') {
		cout << "только главный админ имеет доступ к редоктерованию аккаунта админа" << endl;
		editUsersMenu(curUser);
	}
	else if (toEditUserRole == 'h') cout << "главный аккаунт админа не может быит редоктерован" << endl;
	else
	{
		vector<string> newUsersVec;

		for (int i = 0; i < allUsers.size(); i++)
		{
			string curUsername = allUsers[i].username;
			if (username == allUsers[i].username)
			{
				char newRole;
				cout << "введите новый руль: "; cin >> newRole;
				while (newRole != 'a' && newRole != 'w' && newRole != 'n')
				{
					cout << "руль не существует, выйти? (n)" << endl;
					cin >> newRole;
					if (newRole == 'n') editUsersMenu(curUser);
				}
				newUsersVec.push_back(curUsername + " " + allUsers[i].password + " " + newRole);
			}
			else
			{
				newUsersVec.push_back(curUsername + " " + allUsers[i].password + " " + allUsers[i].role);
			}
		}


		users_file.open("users.txt");

		if (!users_file.is_open()) {
			cout << "файл не открыть" << endl;
		}
		else {
			for (size_t i = 0; i < newUsersVec.size(); i++)
			{
				users_file << "\n" << newUsersVec[i];
			}
		}
		users_file.close();
	}
	editUsersMenu(curUser);
}

void addUser(string curUsername, string username, string password, char role) {
	ofstream users_file;

	string newUser = username + " " + password + " " + role;

	users_file.open("users.txt", std::ofstream::app);

	if (!users_file.is_open()) {
		cout << "файл не открыть" << endl;
	}
	else {
			users_file << "\n" << newUser;

	}
	users_file.close();

	editUsersMenu(curUsername);
}

void printAllUsers(string curUser) {
	vector<User> allUsers = getUsersVec();
	cout << "====================================" << endl;
	cout << "username	" << "role" << endl;
	for (int i = 0; i < allUsers.size(); i++)
	{
		cout << allUsers[i].username << "		  " << allUsers[i].role << endl;
	}
	editUsersMenu(curUser);
}

bool checkIfUserExists(string username) {
	vector<User> allUsers;
	int userIsFound = 0;
	for (int i = 0; i < allUsers.size(); i++)
	{
		if (username == allUsers[i].username) {
			userIsFound = 1;
			break;
		}
	}

	if (userIsFound == 1) return true;
		else return false;

}