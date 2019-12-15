// ObjectModelCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// https://stepik.org/lesson/12794/step/16?unit=3142
// Разработать класс Student со следующими полями: Фамилия, Имя, Отчество, Дата рождения, Адрес, Телефон, Факультет, Курс.
// Включить в класс конструкторы, конструктор копирования, деструктор, методы set(…), get(…), show(…).
// Память под строковые поля необходимо выделять динамически. Определить другие необходимые методы.  Создать массив объектов и вывести:
// а) список студентов заданного факультета;
// б) список студентов для заданного курса;
// в) список студентов, родившихся после заданного года.
// Sample Input:
//  Иванов, Иван, Иванович, 01.01.1998, Москва, 128500, РК-6, 4. Петров, Петр, Петрович, 02.02.1995, Москва, 128500, РК-4, 3. РК-6, 3, 1994
// Sample Output :
//  Иванов, Иван, Иванович, 01.01.1998, Москва, 128500, РК-6, 4. Петров, Петр, Петрович, 02.02.1995, Москва, 128500, РК-4, 3. Иванов, Иван, Иванович, 01.01.1998, Москва, 128500, РК-6, 4; Петров, Петр, Петрович, 02.02.1995, Москва, 128500, РК-4, 3.

#include <iostream>
#include <sstream>
#include <clocale>
#include <string>
#include <algorithm>
#include <vector>
#include <windows.h>

class Student
{
public:
    std::string Name;
    std::string Surname;
    std::string Lastname;
    std::string BirthDate;
    unsigned int BirthYear;
    std::string Address;
    std::string Phone;
    std::string Faculty;
    unsigned char Grade;
public:
    Student();
    Student(std::string name, std::string surname, std::string lastname, std::string date, unsigned int year, std::string address, std::string phone, std::string faculty, unsigned char grade);
    ~Student() {}

    void Print();
};

Student::Student() : Student("", "", "", "", 1995, "", "", "", 1)
{
}

Student::Student(std::string name, std::string surname, std::string lastname, std::string date, unsigned year,
    std::string address, std::string phone, std::string faculty, unsigned char grade):
    Name{name}, Surname{surname}, Lastname{lastname},
    BirthDate{date}, BirthYear{year},
    Address{address}, Phone{phone},
    Faculty{faculty}, Grade{grade}
{
}

void Student::Print()
{
    std::cout << Name << ", " << Surname << ", " << Lastname << ", " << BirthDate << ", " << Address << ", " << Phone << ", " << Faculty << ", " << static_cast<unsigned int>(Grade);
}

std::vector<std::string> split(const std::string& s, char sep)
{
    std::vector<std::string> args;
    std::istringstream ss{ s };
    for (std::string arg; std::getline(ss, arg, sep); )
        args.push_back(arg);
    return args;
}

void RemoveSpaces(std::string& str)
{
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

int main()
{
    //setlocale(LC_ALL, "ru_RU.UTF-8");
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::vector<class Student> school;

    std::string data;
    getline(std::cin, data);
    std::string delimiter(". ");
    data += delimiter;
    std::size_t start = 0;
    std::size_t found = data.find(delimiter);
    Student* student{ nullptr };

    while (found != std::string::npos)
    {
        auto current_record = data.substr(start, found - start);
        RemoveSpaces(current_record);
        std::vector<std::string> person = split(current_record, ',');
        if (person.size() == 8) // add student
        {
            delete student;
            student = new Student(
                person.at(0), person.at(1), person.at(2),
                person.at(3), atoi(person.at(3).substr(6, 4).c_str()),
                person.at(4), person.at(5),
                person.at(6), atoi(person.at(7).c_str()));
            school.push_back(*student);
        }
        else if (person.size() == 3) // filters
        {
            int count1{ 0 }, count2{ 0 }, count3{0};
            for (const auto& st : school)
            {
                if (st.Faculty == person.at(0))
                    ++count1;
                if (st.Grade == atoi(person.at(1).c_str()))
                    ++count2;
                if (st.BirthYear > atoi(person.at(2).c_str()))
                    ++count3;
            }

            for (auto st : school)
            {
                if (st.Faculty == person.at(0))
                {
                    st.Print();
                    std::cout << ((--count1 > 0) ? "; " : ". ");
                }
            }
            for (auto st : school) 
            {
                if (st.Grade == atoi(person.at(1).c_str()))
                {
                    st.Print();
                    std::cout << ((--count2 > 0) ? "; " : ". ");
                }
            }
            for (auto st: school)
            {
                if (st.BirthYear > atoi(person.at(2).c_str()))
                {
                    st.Print();
                    std::cout << ((--count3 > 0) ? "; " : ". ");
                }
            }
        }
        start = found + delimiter.size();
        found = data.find(delimiter, start);
    }
    delete student;
}
