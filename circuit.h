/*
*  �����, ������������ ������������� �����
*
*   �������� �������� �����, ����� ��������� �� �����,
*    � ����� ������ ��������.
*   �������� ������ ��� ���������� � �������� ���������,
*    ��������� ��������� �� ���������� �� ��������,
*    ���������� ������ � �������� � ������.
*/

#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <map>
#include <list>

#include "device.h"
#include "displayed_info.h"

using std::map;
using std::list;
using std::string;

class AddDev;

class Circuit
{
private:

    string m_circuit_name;                          // �������� �����;
    map<string, Dev*> m_devs;                       // ����� ��������� � �����;
    list<LogEntry*> m_log;                          // ������ ��������;
    int m_LogEntryIDGenerator;                      // ������� ������� � ������;

public:

    Circuit(const string& circuit_name = "circuit");

    ~Circuit();

    const string& get_name() const
        { return m_circuit_name; }

    const int& getLogEntryID() const
        { return m_LogEntryIDGenerator; }

    int addDev(Dev* dev);                           // ��������� ���������� �� �����;

    int deleteDev(                                  // ������� ���������� �� �����;
        const string& dev_name);

    bool isContain(                                 // ���������, ���������� �� � ����� ����������
        const string& dev_name);                    // � ������ dev_name;

    Dev* getDev(                                    // ���������� ��������� �� ���������� � ������ dev_name;
        const string& dev_name);

    void addLogEntry                                // ��������� ������ � ���;
        (LogEntry* log_entry);

    const list<LogEntry*>& getLog() const           // ���������� ������ ��������;
        { return m_log; }
};

#endif