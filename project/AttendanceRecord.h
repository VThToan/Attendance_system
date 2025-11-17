// AttendanceRecord.h
#pragma once
#include <string>
using namespace std;
class AttendanceRecord {
public:
    string recordId;
    string studentId;
    string classId;
    string status;
    AttendanceRecord(string recid, string sid, string cid, string st)
        : recordId(recid), studentId(sid), classId(cid), status(st) {
    }
//Cập nhật trạng thái điểm danh
    void updateStatus(AttendanceRecord& record, const string& newStatus) {
    	record.status = newStatus;
    }
//Xem trạng thái điểm danh
    string viewAttendanceStatus(const AttendanceRecord& record) {
    	return record.status;
    }
};


