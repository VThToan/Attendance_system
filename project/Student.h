#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "AttendanceRecord.h"
#include "Class.h"
using namespace std;

class Student
{
public:
    string studentId;
    string fullName;
    string email;
    string phoneNumber;
    string password;

    Student(string sid = "student", string fn = "Student", string em = "student@mail.com", string pn = "012345", string pw = "123")
        : studentId(sid), fullName(fn), email(em), phoneNumber(pn), password(pw) {
    }

    // SV tự điểm danh
    void selfAttendance(vector<AttendanceRecord>& attendanceDB, const vector<ClassRoom>& classesDB) const
    {
        vector<int> myClasses;
        for (int i = 0; i < classesDB.size(); i++)
        {
            bool belong = false;
            for (int j = 0; j < classesDB[i].students.size(); j++) {
                if (classesDB[i].students[j] == studentId)
                {
                    belong = true;
                    break;
                }
            }
            if (belong)
            {
                myClasses.push_back((int)i);
            }
        }
        if (myClasses.size() == 0)
        {
            cout << "You don't have a class.\n";
            return;
        }
        cout << "Select class: \n";
        for (int k = 0; k < myClasses.size(); k++)
        {
            cout << (k + 1) << ") " << classesDB[myClasses[k]].classId << " - " << classesDB[myClasses[k]].className << endl;
        }
        int choice;
        cin >> choice;
        if (choice < 1 || choice >(int)myClasses.size())
        {
            cout << "Invalid choice.\n";
            return;
        }
        cout << "Status (Present/Late/Absent): ";
        string st;
        cin >> st;
        string recId = "rec" + to_string((int)attendanceDB.size() + 1);
        attendanceDB.push_back(AttendanceRecord(recId, studentId, classesDB[myClasses[choice - 1]].classId, st));
        cout << "Marked!\n";
    }

    // Xem lịch sử điểm danh
    void viewAttendanceHistory(const vector<AttendanceRecord>& attendanceDB) const
    {
        cout << "\nMy attendance history:\n";
        for (int i = 0; i < attendanceDB.size(); i++)
        {
            if (attendanceDB[i].studentId == studentId)
            {
                cout << "Class: " << attendanceDB[i].classId << ", Status: " << attendanceDB[i].status << endl;
            }
        }
    }
};

