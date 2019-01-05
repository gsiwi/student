

#include "pch.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <clocale>





using namespace std;

const int NFOSize = 15;

struct Student {
	char Name[NFOSize] = "";
	char SecondName[NFOSize] = "";
	char LastName[NFOSize] = "";
	char BirthDay[11] = "";
	char Faculty[NFOSize] = "";

};

struct StudentNode {
	Student* StudentData = nullptr;
	StudentNode* Next = nullptr;
	StudentNode* Prev = nullptr;
};

enum sort { up, down };
bool Sort = false;
int iSort = sort::up;
StudentNode* first = nullptr;
int Size = 0;
char FilePath[] = "C:\\Users\\кристина\\Desktop\\Base.bb";



//-------------------------------------------------------------------FunctionsList
void AddStudent(char* Name, char* LastName, char* SecondName, char* BirthDay, char* Faculty);
void DeleteStudent(StudentNode*);
StudentNode* FindStudent(char* LastName);
bool IsEmpty();
int GetSize();
void Sorting(int);
bool Save();
bool Load();
//-------------------------------------------------------------------FunctionsList
//-------------------------------------------------------------------FunctionsInterface
void PrintStudentInfo(Student* stud);
void PrintBase();
void Menu();
//-------------------------------------------------------------------FunctionsInterface

//-------------------------------------------------------------------main


int main(int argc, char const *argv[]) {
	setlocale(LC_ALL, "rus");
	Menu();
	char c = 'z';
	while (c != 'q') {
		cin >> c;
		cin.ignore(100, '\n');

		int s = 10;
		switch (c) {
		case 'q':
			break;
		case 'm':
			Menu();
			break;
		case 'l':
			if (!Load()) {
				cout << "Ошибка чтения файла" << endl;
				break;
			}
			cout << "Загружено  " << GetSize() << " студентов" << endl;
			break;
		case 'k':
			cout << "Размер базы - " << GetSize() << endl;
			break;
		case 's':
			if (IsEmpty()) {
				cout << "База пуста" << endl;
				break;
			}
			if (!Save()) {
				cout << "Ошибка при сохранении" << endl;
				break;
			}
			cout << "База сохранена" << endl;
			break;
		case 'e':
			if (IsEmpty())
				cout << "База пуста" << endl;
			else
				cout << "База не пуста" << endl;
			break;
		case 'p':
			if (IsEmpty()) {
				cout << "База пуста" << endl;
				break;
			}
			PrintBase();
			break;
		case 'f':
			if (IsEmpty()) {
				cout << "База пуста" << endl;
				break;
			}
			char SearchLastName[NFOSize];
			cout << "Введите фамилию студента для поиска: ";
			cin >> SearchLastName;
			cout << endl;
			StudentNode* tmp;
			tmp = FindStudent(SearchLastName);
			if (tmp == nullptr) {
				cout << "Студент не найден!" << endl;
				break;
			}
			cout << "Найден студент" << endl;
			PrintStudentInfo(tmp->StudentData);
			cout << "Удалить?(y/n)" << endl;
			cin >> c;
			if (c == 'y') DeleteStudent(tmp);
			c = 'z';
			break;
		case 'a':
			char Name[NFOSize];
			char SecondName[NFOSize];
			char LastName[NFOSize];
			char BirthDay[11];
			char Faculty[NFOSize];

			cout << "Введите информацию о студенте" << endl;
			cout << "Имя: ";
			cin >> Name;
			cout << endl;
			cout << "Фамилия: ";
			cin >> LastName;
			cout << endl;
			cout << "Отчество: ";
			cin >> SecondName;
			cout << endl;
			cout << "Дата рождения(дд.мм.гггг): ";
			cin >> BirthDay;
			cout << endl;
			cout << "Группа: ";
			cin >> Faculty;
			cout << endl;
			AddStudent(Name, LastName, SecondName, BirthDay, Faculty);
			cout << "Студент добавлен" << endl;
			break;
		case 'g':
			if (IsEmpty()) {
				cout << "База пуста" << endl;
				break;
			}
			while (s != sort::up && s != sort::down) {
				cout << "Выберете направление сортировки(" << sort::up << " - по возрастанию, " << sort::down << " - по убыванию): ";
				cin >> s;
				if (s != sort::up && s != sort::down) cout << "Вы ввели недопустимое число" << endl;
			}
			Sorting(s);
			break;
		default:
			cout << "Неизвестная команда" << endl;
			break;
		}
	}
	return 0;
}

//-------------------------------------------------------------------main

//-------------------------------------------------------------------RealiseList

void AddStudent(char* Name, char* LastName, char* SecondName, char* BirthDay, char* Faculty) {
	StudentNode* n = new StudentNode();
	n->StudentData = new Student();
	strcpy_s(n->StudentData->Name, Name);
	strcpy_s(n->StudentData->LastName, LastName);
	strcpy_s(n->StudentData->SecondName, SecondName);
	strcpy_s(n->StudentData->BirthDay, BirthDay);
	strcpy_s(n->StudentData->Faculty, Faculty);
	if (first == nullptr) first = n;
	else {
		n->Next = first;
		first->Prev = n;
		first = n;
	}
	Size++;
	Sort = false;
}

void DeleteStudent(StudentNode* stud) {
	StudentNode* forDelete = stud;
	if (stud == first) {
		first = stud->Next;
		first->Prev = nullptr;
		delete forDelete->StudentData;
		delete forDelete;
	}
	else if (stud->Next == nullptr) {
		stud->Prev->Next = nullptr;
		delete forDelete->StudentData;
		delete forDelete;
	}
	else {
		stud->Prev->Next = stud->Next;
		stud->Next->Prev = stud->Prev;
		delete forDelete->StudentData;
		delete forDelete;
	}
	Size--;
}

StudentNode* FindStudent(char* LastName) {
	StudentNode* point = first;
	while (point != nullptr && strcmp(point->StudentData->LastName, LastName) < 0) {
		point = point->Next;
	}
	return point;
}

bool IsEmpty() {
	return first == nullptr;
}

int GetSize() {
	return Size;
}

void Sorting(int s) {
	if (!Sort) {
		StudentNode* point = first;
		while (point != nullptr) {
			StudentNode* min = point;
			StudentNode* point2 = point;
			while (point2 != nullptr) {
				if (strcmp(min->StudentData->LastName, point2->StudentData->LastName) >= 0) min = point2;
				point2 = point2->Next;
			}
			Student* tmpFirst = point->StudentData;
			point->StudentData = min->StudentData;
			min->StudentData = tmpFirst;
			point = point->Next;
		}
		iSort = sort::up;
	}
	if (s != iSort) {
		StudentNode* point3 = first;
		while (point3 != nullptr) {
			StudentNode* tmpNode2 = point3->Next;
			point3->Next = point3->Prev;
			point3->Prev = tmpNode2;
			if (point3->Prev == nullptr) {
				first = point3;
				break;
			}
			else point3 = point3->Prev;
		}
		iSort = sort::down;
	}
	Sort = true;
}

bool Save() {
	ofstream oFile;
	oFile.open(FilePath, ios_base::trunc | ios_base::binary);
	if (oFile.is_open()) {
		StudentNode* point = first;
		while (point != nullptr) {
			oFile.write((const char*)point->StudentData, sizeof(Student));
			point = point->Next;
		}
		oFile.close();
		return true;
	}
	return false;
}

bool Load() {
	ifstream iFile;
	iFile.open(FilePath, ios_base::binary);
	if (iFile.is_open()) {
		while (!iFile.eof()) {
			char Name[NFOSize] = "";
			char SecondName[NFOSize] = "";
			char LastName[NFOSize] = "";
			char BirthDay[11] = "";
			char Faculty[NFOSize] = "";

			iFile.read(Name, sizeof(char)*NFOSize);
			iFile.read(SecondName, sizeof(char)*NFOSize);
			iFile.read(LastName, sizeof(char)*NFOSize);
			iFile.read(BirthDay, sizeof(char) * 11);
			iFile.read(Faculty, sizeof(char)*NFOSize);
			if (!iFile.eof()) {
				AddStudent(Name, LastName, SecondName, BirthDay, Faculty);
			}
		}
		iFile.close();
		return true;
	}
	return false;
}
//-------------------------------------------------------------------RealiseList

//-------------------------------------------------------------------RealiseInterface
void PrintStudentInfo(Student* stud) {
	cout << "Студент " << stud->LastName << " " << stud->Name << " " << stud->SecondName << endl;
	cout << "Родился " << stud->BirthDay << endl;
	cout << "Обучается в группе " << stud->Faculty << endl;
}

void PrintBase() {
	StudentNode* point = first;
	int i = 1;
	cout << "Вывод базы студентов" << endl;
	while (point != nullptr) {
		cout << "#" << i << endl;
		PrintStudentInfo(point->StudentData);
		cout << endl;
		point = point->Next;
		i++;
	}
	cout << "Всего " << GetSize() << " студентов." << endl;
}

void Menu() {
	cout << "Введите:" << endl;
	cout << "\"q\" - что бы выйти," << endl;
	cout << "\"a\" - что бы добавить студента," << endl;
	cout << "\"f\" - что бы найти студента," << endl;
	cout << "\"e\" - что бы проверить на пустую базу," << endl;
	cout << "\"s\" - что бы сохранить базу," << endl;
	cout << "\"l\" - что бы загрузить базу," << endl;
	cout << "\"p\" - что бы вывести базу," << endl;
	cout << "\"k\" - что бы узнать размер базы," << endl;
	cout << "\"g\" - что бы отсортировать базу," << endl;
	cout << "\"m\" - что бы показать это меню" << endl;
}
//---------------------------
