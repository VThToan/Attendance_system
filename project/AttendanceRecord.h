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
    void updateStatus(AttendanceRecord& record, const string& newStatus) {
    	record.status = newStatus;
    }
    string viewAttendanceStatus(const AttendanceRecord& record) {
    	return record.status;
    }
};


