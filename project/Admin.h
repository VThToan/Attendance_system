#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Lecturer.h"
#include "Student.h"
#include "Class.h"
#include <windows.h>
using namespace std;

class Admin
{
public:
    string userName;
    string password;
    string fullName;
    string email;
    string phoneNumber;

    Admin(string un = "admin", string pw = "123", string fn = "Administrator", string em = "admin@school.com", string pn = "000")
        : userName(un), password(pw), fullName(fn), email(em), phoneNumber(pn) {
    }

    // xem danh sách giảng viên và sinh viên
    void viewAccountUser(const vector<Lecturer>& lecturersDB, const vector<Student>& studentsDB)
    {
        cout << "\n--- Lecturers ---\n";
        for (int i = 0; i < lecturersDB.size(); i++) {
            cout << (i + 1) << ") " << lecturersDB[i].lecturerId << " - " << lecturersDB[i].fullName << endl;
        }
        cout << "\n--- Students ---\n";
        for (int i = 0; i < studentsDB.size(); i++) {
            cout << (i + 1) << ") " << studentsDB[i].studentId << " - " << studentsDB[i].fullName << endl;
        }
    }


    // tạo tài khoản giảng viên hoặc sinh viên mới
    void createUserAccount(vector<Lecturer>& lecturersDB, vector<Student>& studentsDB, const string& lecturersCsvPath, const string& studentsCsvPath) {
        cout << "Create (1) Lecturer or (2) Student: ";
        int type; cin >> type;
        if (type == 1) {
            Lecturer l;
            cout << "Enter Lecturer ID: ";
            cin >> l.lecturerId;
            cout << "Full name: ";
            cin.ignore();
            getline(cin, l.fullName);
            cout << "Email: ";
            getline(cin, l.email);
            cout << "Phone: ";
            getline(cin, l.phoneNumber);
            cout << "Password: ";
            cin >> l.password;
            lecturersDB.push_back(l);
            saveLecturersToCsv(lecturersDB, lecturersCsvPath); // save ngay
            cout << "Lecturer created and saved!\n";
        }
        else if (type == 2) {
            Student s;
            cout << "Enter Student ID: ";
            cin >> s.studentId;
            cout << "Full name: ";
            cin.ignore();
            getline(cin, s.fullName);
            cout << "Email: ";
            getline(cin, s.email);
            cout << "Phone: ";
            getline(cin, s.phoneNumber);
            cout << "Password: ";
            cin >> s.password;
            studentsDB.push_back(s);
            saveStudentsToCsv(studentsDB, studentsCsvPath); // save ngay
            cout << "Student created and saved!\n";
        }
        else {
            cout << "Invalid type.\n";
        }
    }

    //chỉnh sửa thông tin giảng viên hoặc sinh viên
    void editUser(vector<Lecturer>& lecturersDB, vector<Student>& studentsDB) {
        cout << "Edit (1) Lecturer or (2) Student: ";
        int type;
        cin >> type;
        if (type == 1) {
            string id;
            cout << "Enter Lecturer ID to edit: ";
            cin >> id;
            int i;
            bool found = false;
            for (i = 0; i < lecturersDB.size(); i++)
            {
                if (lecturersDB[i].lecturerId == id)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                cout << "New full name (leave empty to skip): ";
                cin.ignore();
                string name;
                getline(cin, name);
                if (name.size() > 0)
                {
                    lecturersDB[i].fullName = name;
                }
                cout << "New email (leave empty to skip): ";
                string em;
                getline(cin, em);
                if (em.size() > 0)
                {
                    lecturersDB[i].email = em;
                }
                cout << "New phone (leave empty to skip): ";
                string ph;
                getline(cin, ph);
                if (ph.size() > 0)
                {
                    lecturersDB[i].phoneNumber = ph;
                }
                cout << "New password (leave empty to skip): ";
                string pw;
                getline(cin, pw);
                if (pw.size() > 0)
                {
                    lecturersDB[i].password = pw;
                }
                cout << "Updated lecturer!\n";
            }
            else
            {
                cout << "Lecturer not found.\n";
            }
        }
        else if (type == 2)
        {
            string id;
            cout << "Enter Student ID to edit: ";
            cin >> id;
            int i;
            bool found = false;
            for (i = 0; i < studentsDB.size(); i++)
            {
                if (studentsDB[i].studentId == id)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                cout << "New full name (leave empty to skip): ";
                cin.ignore();
                string name;
                getline(cin, name);
                if (name.size() > 0)
                {
                    studentsDB[i].fullName = name;
                }
                cout << "New email (leave empty to skip): ";
                string em;
                getline(cin, em);
                if (em.size() > 0)
                {
                    studentsDB[i].email = em;
                }
                cout << "New phone (leave empty to skip): ";
                string ph;
                getline(cin, ph);
                if (ph.size() > 0)
                {
                    studentsDB[i].phoneNumber = ph;
                }
                cout << "New password (leave empty to skip): ";
                string pw;
                getline(cin, pw);
                if (pw.size() > 0)
                {
                    studentsDB[i].password = pw;
                }
                cout << "Updated student!\n";
            }
            else
            {
                cout << "Student not found.\n";
            }
        }
        else { cout << "Invalid type.\n"; }
    }

    // tạo lớp học mới
    void createClassAndSave(vector<ClassRoom>& classesDB, const string& classesCsvPath) {
        ClassRoom c;
        cout << "Class ID: ";
        cin >> c.classId;
        cout << "Class Name: ";
        cin.ignore();
        getline(cin, c.className);
        classesDB.push_back(c);
        saveClassesToCsv(classesDB, classesCsvPath); // save ngay
        cout << "Class created and saved!\n";
    }

    // chỉnh sửa lớp học
    void editClass(vector<ClassRoom>& classesDB) {
        cout << "Enter Class ID to edit: ";
        string cid;
        cin >> cid;
        int i;
        bool found = false;
        for (i = 0; i < classesDB.size(); i++)
        {
            if (classesDB[i].classId == cid)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            cout << "New class name: ";
            cin.ignore();
            string newName;
            getline(cin, newName);
            if (newName.size() > 0)
            {
                classesDB[i].className = newName;
            }
            cout << "Updated class!\n";
        }
        else
        {
            cout << "Class not found.\n";
        }
    }

    // thêm giảng viên hoặc sinh viên vào lớp học
    void addMemberToClass(vector<ClassRoom>& classesDB, const vector<Lecturer>& lecturersDB, const vector<Student>& studentsDB) {
        cout << "Enter Class ID: ";
        string cid;
        cin >> cid;
        int classIndex = -1;
        for (int i = 0; i < classesDB.size(); i++)
        {
            if (classesDB[i].classId == cid)
            {
                classIndex = (int)i;
                break;
            }
        }
        if (classIndex == -1)
        {
            cout << "Class not found.\n";
            return;
        }
        cout << "Add (1) Lecturer or (2) Student: ";
        int type;
        cin >> type;
        if (type == 1)
        {
            if (classesDB[classIndex].lecturers.size() >= 1)
            {
                cout << "This class already has a lecturer.\n";
                return;
            }
            cout << "Enter Lecturer ID to add: ";
            string lid;
            cin >> lid;
            bool exists = false;
            for (int i = 0; i < lecturersDB.size(); i++)
            {
                if (lecturersDB[i].lecturerId == lid)
                {
                    exists = true;
                }
            }
            if (!exists)
            {
                cout << "Lecturer not found.\n";
                return;
            }
            classesDB[classIndex].addLecturer(lid);
            cout << "Lecturer added to class.\n";
        }
        else if (type == 2)
        {
            cout << "Enter Student ID to add: ";
            string sid;
            cin >> sid;
            bool exists = false;
            for (int i = 0; i < studentsDB.size(); i++)
            {
                if (studentsDB[i].studentId == sid)
                {
                    exists = true;
                }
            }
            if (!exists)
            {
                cout << "Student not found.\n";
                return;
            }
            classesDB[classIndex].addStudent(sid);
            cout << "Student added to class.\n";
        }
        else
        {
            cout << "Invalid type.\n";
        }
    }

    // lưu dữ liệu giảng viên, sinh viên vào file
    void saveLecturersToCsv(const vector<Lecturer>& lecturersDB, const string& path)
    {
        ofstream f(path.c_str());
        if (!f.is_open())
        {
            cout << "Cannot open file: " << path << endl;
            return;
        }
        f << "lecturerId,fullName,email,phone,password\n";
        for (int i = 0; i < lecturersDB.size(); i++)
        {
            f << lecturersDB[i].lecturerId << "," << lecturersDB[i].fullName << "," << lecturersDB[i].email << ","
                << lecturersDB[i].phoneNumber << "," << lecturersDB[i].password << "\n";
        }
        f.close();
    }

    void saveStudentsToCsv(const vector<Student>& studentsDB, const string& path)
    {
        ofstream f(path.c_str());
        if (!f.is_open())
        {
            cout << "Cannot open file: " << path << endl;
            return;
        }
        f << "studentId,fullName,email,phone,password\n";
        for (int i = 0; i < studentsDB.size(); i++)
        {
            f << studentsDB[i].studentId << ","
                << studentsDB[i].fullName << ","
                << studentsDB[i].email << ","
                << studentsDB[i].phoneNumber << ","
                << studentsDB[i].password << "\n";
        }
        f.close();
    }

    // load dữ liệu giảng viên, sinh viên từ fie
    void loadLecturersFromCsv(vector<Lecturer>& lecturersDB, const string& path) {
        ifstream f(path.c_str());
        if (!f.is_open())
        {
            return; lecturersDB.clear();
        }
        string line;
        if (getline(f, line))
        {
        }
        while (getline(f, line))
        {
            stringstream ss(line);
            string id, name, email, phone, pw;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');
            getline(ss, pw, ',');
            lecturersDB.push_back(Lecturer(id, name, email, phone, pw));
        }
        f.close();
    }

    void loadStudentsFromCsv(vector<Student>& studentsDB, const string& path) {
        ifstream f(path.c_str());
        if (!f.is_open())
        {
            return;
        }
        studentsDB.clear();
        string line;
        if (getline(f, line))
        {
        }
        while (getline(f, line))
        {
            stringstream ss(line);
            string id, name, email, phone, pw;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');
            getline(ss, pw, ',');
            studentsDB.push_back(Student(id, name, email, phone, pw));
        }
        f.close();
    }

    // lưu lớp đã tạo vào file
    void saveClassesToCsv(const vector<ClassRoom>& classesDB, const string& path) {
        ofstream f(path.c_str());
        if (!f.is_open())
        {
            cout << "Cannot open file: " << path << endl;
            return;
        }
        f << "classId,className,lecturerId,studentIds\n";
        for (int i = 0; i < classesDB.size(); i++)
        {
            string lec = "";
            if (classesDB[i].lecturers.size() > 0)
            {
                lec = classesDB[i].lecturers[0];
            }
            string stuJoined = "";
            for (int j = 0; j < classesDB[i].students.size(); j++)
            {
                stuJoined += classesDB[i].students[j];
                if (j + 1 < classesDB[i].students.size())
                {
                    stuJoined += ";";
                }
            }
            f << classesDB[i].classId << "," << classesDB[i].className << "," << lec << "," << stuJoined << "\n";
        }
        f.close();
    }

// load lớp đã tạo từ file
    void loadClassesFromCsv(vector<ClassRoom>& classesDB, const string& path) {
        ifstream f(path.c_str());
        if (!f.is_open())
        {
            return;
        }
        classesDB.clear();
        string line;
        if (getline(f, line)) {}
        while (getline(f, line))
        {
            stringstream ss(line);
            string cid, cname, lec, joined;
            getline(ss, cid, ',');
            getline(ss, cname, ',');
            getline(ss, lec, ',');
            getline(ss, joined, ',');
            ClassRoom c(cid, cname);
            if (lec.size() > 0)
            {
                c.addLecturer(lec);
            }
            string sid;
            stringstream s2(joined);
            while (getline(s2, sid, ';'))
            {
                if (sid.size() > 0)
                {
                    c.addStudent(sid);
                }
            }
            classesDB.push_back(c);
        }
        f.close();
    }

    // reset password khi đăng nhập thất bại
    void resetPassword(vector<Lecturer>& lecturersDB, vector<Student>& studentsDB,
        const string& lecturersCsvPath, const string& studentsCsvPath) {
        cout << "Reset password for (1) Lecturer or (2) Student: ";
        int type;
        cin >> type;

        if (type == 1) {
            string lecturerId;
            cout << "Enter Lecturer ID to reset password: ";
            cin >> lecturerId;

            bool found = false;
            for (int i = 0; i < lecturersDB.size(); i++) {
                if (lecturersDB[i].lecturerId == lecturerId) {
                    found = true;
                    string newPassword;
                    cout << "Enter new password for lecturer " << lecturerId << ": ";
                    cin >> newPassword;

                    lecturersDB[i].password = newPassword;
                    saveLecturersToCsv(lecturersDB, lecturersCsvPath);
                    cout << "Password reset successfully for lecturer " << lecturerId << "!\n";
                    break;
                }
            }

            if (!found) {
                cout << "Lecturer ID not found.\n";
            }

        }
        else if (type == 2) {
            string studentId;
            cout << "Enter Student ID to reset password: ";
            cin >> studentId;

            bool found = false;
            for (int i = 0; i < studentsDB.size(); i++) {
                if (studentsDB[i].studentId == studentId) {
                    found = true;
                    string newPassword;
                    cout << "Enter new password for student " << studentId << ": ";
                    cin >> newPassword;

                    studentsDB[i].password = newPassword;
                    saveStudentsToCsv(studentsDB, studentsCsvPath);
                    cout << "Password reset successfully for student " << studentId << "!\n";
                    break;
                }
            }

            if (!found) {
                cout << "Student ID not found.\n";
            }

        }
        else {
            cout << "Invalid type.\n";
        }
    }
};

