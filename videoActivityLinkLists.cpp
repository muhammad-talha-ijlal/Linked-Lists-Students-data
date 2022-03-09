#include <iostream>
#include <windows.h>
using namespace std;

//Creating Structures
struct marks
{
    string subject;
    float data;
    marks *next;
};

struct student
{
    string name;
    student *next;
    marks *m_next;
};

//Required Global Variables

student *studentHead = NULL;
student *loginStudent = NULL;
marks *loginStudentSubject = NULL;

//To find the student of specific name in the list
bool findInStudents(string name)
{
    student *temp = studentHead;
    while (temp != NULL)
    {
        if (temp->name == name)
        {
            loginStudent = temp;
            return true;
        }
        temp = temp->next;
    }
    return false;
}
//To find specific subject in the marks list of given student
bool findInMarks(string subject)
{
    marks *temp = loginStudent->m_next;
    while (temp != NULL)
    {
        if (temp->subject == subject)
        {
            loginStudentSubject = temp;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//To get last subject at list of a specific student
marks *getLastSubject()
{
    marks *temp = loginStudent->m_next;
    while (temp->next != NULL)
    {
        /* code */
        temp = temp->next;
    }
    return temp;
}

//Get last student of the list
student *getLastStudent()
{
    student *temp = studentHead;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp;
}




//To add new subject at the end of list
void addNewSubject(string subject, int mark)
{
    marks *record = new marks;
    record->data = mark;
    record->subject = subject;
    record->next = NULL;

    if (loginStudent->m_next == NULL)
    {
        loginStudent->m_next = record;
    }
    else
    {
        getLastSubject()->next = record;
    }
}

//To add new student
void addNewStudent(string name, string subject, int marks)
{
    student *point = new student;
    point->name = name;
    loginStudent = point;
    loginStudent->m_next = NULL;
    addNewSubject(subject, marks);
    point->next = NULL;
    if (studentHead == NULL)
    {
        studentHead = point;
    }
    else
    {
        getLastStudent()->next = point;
    }
}

// PRINTING RECORD FUNCTIONS
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void printList()
{
    int x = 0;
    int y = 0;
    student *temp = studentHead;
    marks *point = temp->m_next;
    while (temp != NULL)
    {
        gotoxy(x, y);
        cout << temp->name;
        point = temp->m_next;
        int count = 0;
        while (point != NULL)
        {
            x = 20;
            gotoxy(x, y);
            cout << point->subject << ": " << point->data;
            point = point->next;
            x = x + 10;
            y++;
        }
        x = 0;
        gotoxy(x, y);
        cout << "_________________________________";
        y++;
        temp = temp->next;
    }
}
main()
{
    while (true)
    {
        system("cls");
        string name;
        cout << "Enter Name: ";
        cin >> name;
        string subject;
        cout << "Subject: ";
        cin >> subject;
        int marks;
        cout << "Enter Marks: ";
        cin >> marks;

        if (findInStudents(name))
        {
            if (findInMarks(subject))
            {
                loginStudentSubject->data = marks;
            }
            else
            {
                addNewSubject(subject, marks);
            }
        }
        else
        {
            addNewStudent(name, subject, marks);
        }
        system("cls");
        printList();
        cout << endl;
        system("pause");
    }
}
