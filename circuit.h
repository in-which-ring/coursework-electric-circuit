/*
*  Класс, моделирующий электрическую схему
*
*   Содержит название схемы, набор устройств на схеме,
*    а также журнал действий.
*   Содержит методы для добавления и удаления устройств,
*    получения указателя на устройство по названию,
*    добавления записи о действии в журнал.
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

    string m_circuit_name;                          // название схемы;
    map<string, Dev*> m_devs;                       // набор устройств в схеме;
    list<LogEntry*> m_log;                          // журнал действий;
    int m_LogEntryIDGenerator;                      // счётчик записей в журнал;

public:

    Circuit(const string& circuit_name = "circuit");

    ~Circuit();

    const string& get_name() const
        { return m_circuit_name; }

    const int& getLogEntryID() const
        { return m_LogEntryIDGenerator; }

    int addDev(Dev* dev);                           // добавляет устройство на схему;

    int deleteDev(                                  // удаляет устройство со схемы;
        const string& dev_name);

    bool isContain(                                 // проверяет, содержится ли в схеме устройство
        const string& dev_name);                    // с именем dev_name;

    Dev* getDev(                                    // возвращает указатель на устройство с именем dev_name;
        const string& dev_name);

    void addLogEntry                                // добавляет запись в лог;
        (LogEntry* log_entry);

    const list<LogEntry*>& getLog() const           // возвращает журнал действий;
        { return m_log; }
};

#endif