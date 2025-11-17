#include <iostream>
#include <vector>
#include <string>
#include "Admin.h"
#include "Lecturer.h"
#include "Student.h"
#include "Class.h"
#include "AttendanceRecord.h"
#inchlude "iomanip"
#include <locale>
#include <codecvt> // cần cho xử lý Unicode
using namespace std;

// CSDL trong bộ nhớ
vector<Admin> admins = { Admin() };
vector<Lecturer> lecturers;
vector<Student> students;
vector<ClassRoom> classesDB;
vector<AttendanceRecord> attendanceDB;

// Tiện ích tìm nhanh theo ID
Admin* findAdminById(const string& id)
{
    for (int i = 0;i < admins.size();i++)
        if (admins[i].userName == id)
            return &admins[i];
    return 0;
}
Lecturer* findLecturerById(const string& id)
{
    for (int i = 0;i < lecturers.size();i++)
        if (lecturers[i].lecturerId == id)
            return &lecturers[i];
    return 0;
}
Student* findStudentById(const string& id)
{
    for (int i = 0;i < students.size();i++)
        if (students[i].studentId == id)
            return &students[i];
    return 0;
}

void ClassRoom::display(const vector<Lecturer>& allLecturers, const vector<Student>& allStudents) const
{
    cout << "Class ID: " << classId << "\n";
    cout << "Class Name: " << className << "\n";
    cout << endl;

    // Hiển thị giảng viên với tên đầy đủ
    cout << "Lecturer:\n";
    if (lecturers.empty()) {
        cout << "  Has not Lecturer\n";
    }
    else {
        cout << "No " << "Id " << "\t   Name" << setw(30) << "\t\tEmail" << endl;
        for (int i = 0; i < lecturers.size(); i++) {
            string lecturerName = "";
            string lecturerEmail = "";
            // Tìm thông tin giảng viên từ danh sách allLecturers
            for (int j = 0; j < allLecturers.size(); j++) {
                if (allLecturers[j].lecturerId == lecturers[i]) {
                    lecturerName = allLecturers[j].fullName;
                    lecturerEmail = allLecturers[j].email;
                    break;
                }
            }
             cout << right << (i + 1) << ") " << lecturers[i]<< " - " << setw(30) << lecturerName << "\t\tEmail: " << lecturerEmail << "\n";
             cout << endl;
        }
    }

    // Hiển thị sinh viên với tên đầy đủ
    cout << "Student (" << students.size() << "):\n";
    if (students.empty()) {
        cout << "  Has not student\n";
    }
    else {
        cout << "No " << "Id " << "\t   Name" << setw(30) << "\t\tEmail" << endl;
        for (int i = 0; i < students.size(); i++) {
            string studentName = "";
            string studentEmail = "";
            // Tìm thông tin sinh viên từ danh sách allStudents
            for (int j = 0; j < allStudents.size(); j++) {
                if (allStudents[j].studentId == students[i]) {
                    studentName = allStudents[j].fullName;
                    studentEmail = allStudents[j].email;
                    break;
                }
            }
            cout << left  << (i + 1) << ") " << students[i]<< " - " << setw(30) << studentName << "\t\tEmail: " << studentEmail << "\n";

        }
    }
    cout << endl;
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 >nul");
#endif

    //  Đặt ngôn ngữ hiển thị UTF-8 cho toàn bộ chương trình
    setlocale(LC_ALL, "vi_VN.UTF-8");

    //  locale UTF-8 cho cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.imbue(locale("vi_VN.UTF-8"));

    // Đường dẫn CSV
    const string LEC_CSV = "lecturers.csv";
    const string STU_CSV = "students.csv";
    const string CLS_CSV = "classes.csv";

    // Nạp dữ liệu đã lưu (nếu có)
    admins[0].loadLecturersFromCsv(lecturers, LEC_CSV);
    admins[0].loadStudentsFromCsv(students, STU_CSV);
    admins[0].loadClassesFromCsv(classesDB, CLS_CSV);

    bool running = true;
    while (running) {
        cout << "\n========== STUDENT ATTENDANCE SYSTEM ==========\n";
        cout << "       1. Log In                 2. Exit\n";
        cout << "Enter your choice(number) : ";
        int mainChoice;
        cin >> mainChoice;
        if (mainChoice != 1)
        {
            running = false;
            break;
        }

        // Chọn loại tài khoản an toàn (1/2/3)
        int role = 0;
        int roleAttempts = 0;
        bool roleValid = false;
        while (!roleValid) {
            cout << "\nSelect account type:\t1. Admin\t2. Lecturer\t3. Student\nEnter your choice (number): ";
            cin >> role;
            if (role < 1 || role > 3)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid selection. Please enter 1, 2 or 3.\n";
                cout << endl;
                roleAttempts = roleAttempts + 1;
                if (roleAttempts >= 3)
                {
                    cout << "Too many invalid tries. Back to main menu.\n";
                    roleValid = false;
                    break;
                }
            }
            else
            {
                roleValid = true;
            }
        }
        if (!roleValid) {
            // quay lại vòng lặp lớn
        }
        else {
            // Đăng nhập: tối đa 5 lần
            bool loggedIn = false;
            string id, pw;
            int tries = 0;

            // Biến để lưu thông tin user đang đăng nhập
            string currentUserName = "";
            string currentUserId = "";
            int currentUserRole = 0;
            while (!loggedIn && tries < 5) {
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter password: ";
                cin >> pw;
                tries = tries + 1;
                if (role == 1)
                {
                    Admin* a = findAdminById(id);
                    if (a != 0 && a->password == pw)
                    {
                        loggedIn = true;
                    }
                    else
                    {
                        cout << "\nWrong. Remaining: " << (5 - tries) << endl;
                    }
                }
                else if (role == 2)
                {
                    Lecturer* l = findLecturerById(id);
                    if (l != 0 && l->password == pw)
                    {
                        loggedIn = true;
                        currentUserName = l->fullName;
                        currentUserId = l->lecturerId;
                        currentUserRole = 2;
                    }
                    else
                        cout << "\nWrong. Remaining: " << (5 - tries) << endl;
                }
                else if (role == 3)
                {
                    Student* s = findStudentById(id);
                    if (s != 0 && s->password == pw)
                    {
                        loggedIn = true;
                        currentUserName = s->fullName;
                        currentUserId = s->studentId;
                        currentUserRole = 2;
                    }
                    else
                    {
                        cout << "\nWrong. Remaining: " << (5 - tries) << endl;

                    }

                }

            }
            if (loggedIn) {
                // MENU ADMIN
                if (role == 1) {
                    Admin* a = findAdminById(id);
                    bool inAdmin = true;
                    while (inAdmin) {
                        cout << "\n                         ============= [ADMIN] ============= \n";
                        cout << "1. View accounts               2. Create user account              3. Edit user\n";
                        cout << "\n4. Create a class              5. Edit class name                  6. Add member to class\n";
                        cout << "\n7. View classes                8. Reset user password              9. Log out\n";
                        cout << "\nEnter your choice (number): ";
                        int ac;
                        cin >> ac;
                        if (ac == 1)
                        {
                            a->viewAccountUser(lecturers, students);
                        }
                        else if (ac == 2)
                        {
                            a->createUserAccount(lecturers, students, LEC_CSV, STU_CSV);
                        }
                        else if (ac == 3)
                        {
                            a->editUser(lecturers, students);
                        }
                        else if (ac == 4)
                        {
                            a->createClassAndSave(classesDB, CLS_CSV);
                        }
                        else if (ac == 5)
                        {
                            a->editClass(classesDB);
                            a->saveClassesToCsv(classesDB, CLS_CSV);
                        }
                        else if (ac == 6)
                        {
                            a->addMemberToClass(classesDB, lecturers, students);
                            a->saveClassesToCsv(classesDB, CLS_CSV);
                        }
                        else if (ac == 7)
                        {
                            for (int i = 0;i < classesDB.size();i++)
                                classesDB[i].display(lecturers, students);
                        }
                        else if (ac == 8)
                        {
                            a->resetPassword(lecturers, students, LEC_CSV, STU_CSV);
                        }
                        else if (ac == 9)
                        {
                            inAdmin = false;
                        }
                        else
                        {
                            cout << "Invalid.\n";
                        }
                    }
                }
                // MENU LECTURER
                else if (role == 2) {
                    Lecturer* l = findLecturerById(id);
                    bool inLect = true;
                    while (inLect) {
                        cout << "\n                         ============= [LECTURER] =============\n";
                        cout << "Welcome: " << currentUserName << "\n";
                        cout << "1. View my classes             2. Mark attendance            3. View attendance board\n";
                        cout << "\n4. Log out\n";
                        cout << "\nEnter your choice (number): ";
                        int ac;
                        cin >> ac;
                        if (ac == 1)
                        {
                            l->viewMyClasses(classesDB, lecturers, students);
                        }
                        else if (ac == 2)
                        {
                            l->markAttendanceByIndex(attendanceDB, classesDB);
                        }
                        else if (ac == 3)
                        {
                            l->viewAttendance(attendanceDB);
                        }
                        else if (ac == 4)
                        {
                            inLect = false;
                        }
                        else
                        {
                            cout << "Invalid.\n";
                        }
                    }
                }
                // MENU STUDENT
                else if (role == 3) {
                    Student* s = findStudentById(id);
                    bool inStu = true;
                    while (inStu) {
                        cout << "\n                         ============= [STUDENT] =============\n";
                        cout << "Welcome: " << currentUserName << "\n";
                        cout << "1. Attendance            2. View my attendance history              3. Log out\n";
                        cout << "\nEnter your choice : ";
                        int ac;
                        cin >> ac;
                        if (ac == 1)
                        {
                            s->selfAttendance(attendanceDB, classesDB);
                        }
                        else if (ac == 2)
                        {
                            s->viewAttendanceHistory(attendanceDB);
                        }
                        else if (ac == 3)
                        {
                            inStu = false;
                        }
                        else
                        {
                            cout << "Invalid.\n";
                        }
                    }
                }
            }
            else
            {
                cout << "Back to main menu.\n";
            }
        }
    }

    // Lưu dữ liệu trước khi thoát
    admins[0].saveLecturersToCsv(lecturers, "lecturers.csv");
    admins[0].saveStudentsToCsv(students, "students.csv");
    admins[0].saveClassesToCsv(classesDB, "classes.csv");

    cout << "Goodbye!\n";
    return 0;
}
