#include<iostream>
#include<string>
#include<fstream>
#include <windows.h>
#include "Source.h"
#include "Stdafx.h"
using namespace std;

struct date
{
	short day;
	short month;
	short year;
	bool isCorrect();
};

bool date::isCorrect()
{
	bool result = false;
	if ((day < 1) || (month < 1) || (year < 1))
		result = false;
	else {
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			if ((day <= 31) && (day > 0))
				result = true;
			break;
		}

		case 4:
		case 6:
		case 9:
		case 11:
		{
			if ((day <= 30) && (day > 0))
				result = true;
			break;
		}

		case 2:
		{
			if (year % 4 != 0)
			{
				if ((day <= 28) && (day > 0))
					result = true;
			}
			else
				if (year % 400 == 0)
				{
					if ((day <= 29) && (day > 0))
						result = true;
				}
				else
					if ((year % 100 == 0) && (year % 400 != 0))
					{
						if ((day == 28) && (day > 0))
							result = true;
					}
					else
						if ((year % 4 == 0) && (year % 100 != 0))
							if ((day <= 29) && (day > 0))
								result = true;
			break;
		}

		default:
			result = false;
		}
	}
	return result;
}
struct HomeAdress
{
	string mail_index;
	string country;
	string region;
	string district;
	string city;
	string street;
	string house_number;
	string flat_num;
};
struct Person
{
	string fio;
	date birth;
	string nation;
	string telephone_num;
	HomeAdress home_adress;

};
struct Worker {
	Person person;
	int NumberShop;
	int PersonnelNumber;
	char educated[32];
	int YearEmployment;
};


void BaseLevel() {

    /* «Рабочий»:
	фамилия; имя; отчество; домашний адрес(почтовый индекс, страна,
	область, район, город, улица, дом, квартира); национальность; дата
	рождения(год, месяц число); № цеха; табельный номер; образование; год
	поступления на работу.Вывести данные про рабочих, поступивших на
	работу в 2010 году.*/

	Worker* w = new Worker[2];
	w[0].person.fio = "Иванов Алексей Александрович";
	w[1].person.fio = "Руда Мария Витальевна ";
	for (size_t i = 0; i < 2; i++)
	{
		w[i].YearEmployment = 2000 + rand() % 21; 
	}

	FILE* f_out, * f_in;
	f_out = fopen("worker", "wb");
	fwrite(w, sizeof(Worker), 2, f_out);
	fclose(f_out);
	f_in = fopen("worker", "rb");
	Worker* buffer = new Worker[2];
	fread(buffer, sizeof(Worker), 2, f_in);
	f_out = fopen("year2010", "wb");
	int counter = 0;
	for (size_t i = 0; i < 2; i++)
	{
		cout << "\t" << buffer[i].person.fio << " " << buffer[i].YearEmployment << "\n";
		if (buffer[i].YearEmployment == 2010)
		{
			fwrite(&buffer[i], sizeof(Worker), 1, f_out); counter++;
		}
	}
	fclose(f_out);
	fclose(f_in);
	f_in = fopen("year2010", "rb");
	Worker* buf = (Worker*)malloc(counter * sizeof(Worker));
	fread(buf, sizeof(Worker), counter, f_in);
	for (size_t i = 0; i < counter; i++)
	{
		cout << "\t" << buf[i].person.fio << " " << buf[i].YearEmployment << "\n";
	}
	fclose(f_in);
}



void MiddleLevel() 
{
	/*Дан файл f, компоненты которого являются целыми числами.
	Найти колличество чётных чисел среди компонент.*/

	ifstream fin("f_middle.txt");
	ofstream fout("g_middle.txt");
	if (!fin.is_open())
		cout << "Файл не может быть открыт!\n";
	else {
		int* arr;
		int count = 0;
		arr = new int[36];
		for (int i = 0; i < 36; i++)
		{
			fin >> arr[i];
			if (arr[i] % 2 == 0)
			{
				count++;
			}
		}
		fout << count;
	}
	fin.close();
	fout.close();
			
}




int main() {
	BaseLevel();
	MiddleLevel();
	return 0;
}