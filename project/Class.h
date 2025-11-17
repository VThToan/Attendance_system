// Class.h
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Lecturer;
class Student;

using namespace std;

// Lớp đại diện cho một lớp học
class ClassRoom {
public:
    string classId;
    string className;
    vector<string> lecturers; // lecturerId
    vector<string> students; // studentId
    ClassRoom(string cid = "001", string cname = "CNTT") : classId(cid), className(cname) {}


    void display(const vector<Lecturer>& allLecturers, const vector<Student>& allStudents) const;

    void displayBrief() const
    {
        cout << classId << " - " << className << endl;
    }

    bool addLecturer(const string& lid)
    {
        if (find(lecturers.begin(), lecturers.end(), lid) == lecturers.end())
        {
            lecturers.push_back(lid);
            return true;
        }
        return false;
    }

    bool addStudent(const string& sid)
    {
        if (find(students.begin(), students.end(), sid) == students.end())
        {
            students.push_back(sid);
            return true;
        }
        return false;
    }

    void removeLecturer(const string& lid)
    {
        vector<string> tmp;
        for (int i = 0;i < lecturers.size();i++)
        {
            if (lecturers[i] != lid) tmp.push_back(lecturers[i]);
        }
        lecturers = tmp;
    }
 // Xóa sinh viên khỏi lớp
    void removeStudent(const string& sid)
    {
        vector<string> tmp;
        for (int i = 0;i < students.size();i++)
        {
            if (students[i] != sid) tmp.push_back(students[i]);
        }
        students = tmp;
    }

    void MarkAttendance() {}

    void ViewClassList() const {}
};
