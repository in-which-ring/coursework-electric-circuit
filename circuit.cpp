#include "circuit.h"

Circuit::Circuit(const string& circuit_name)
    : m_circuit_name(circuit_name)
{
    LogEntry* log_entry = new LogEntry(-1, 0,                      // добавляем запись о создании схемы;
                                circuit_name,
                                    "no_dev",
                                    "no_dev");
    m_log.push_back(log_entry);

    m_LogEntryIDGenerator = 1;                                     // устанавливаем id для следующей записи;
}

Circuit::~Circuit()
{
    for (auto iter = m_devs.begin(); iter != m_devs.end(); iter++) // чистка памяти из-под устройств;
        delete iter->second;

    for (auto iter = m_log.begin(); iter != m_log.end(); iter++)   // чистка памяти из-под журнала;
        delete *iter;
}

int Circuit::addDev(Dev* dev)
{
    if (!dev)                                                      // проверяем указатель на устройство;
        return -1;

    if (m_devs.count(dev->get_name()))                             // проверяем, нет ли на схеме устройства
        return -2;                                                 // с таким же именем, как у *dev;

    m_devs.insert(std::pair<string, Dev*>(dev->get_name(), dev));  // добавляем устройство;

    return 0;
}

int Circuit::deleteDev(const string& dev_name)
{
    auto iter = m_devs.find(dev_name);

    if (m_devs.end() == iter)                                  // проверяем, есть ли на схеме устройство
        return -1;                                             // с таким именем, как у *dev;

    m_devs.erase(iter);                                        // удаляем устройство;

    return 0;
}

bool Circuit::isContain(const string& dev_name)
{
    return m_devs.count(dev_name);
}

Dev* Circuit::getDev(const string& dev_name)
{
    auto iter = m_devs.find(dev_name);

    if (m_devs.end() == iter)                                  // проверяем, есть ли на схеме устройство
        return nullptr;                                        // с таким именем, как у dev*;

    return iter->second;
}

void Circuit::addLogEntry(LogEntry* log_entry)
{
    m_log.push_back(log_entry);                                // добавляем запись в журнал;
    log_entry->setID(m_LogEntryIDGenerator);                   // устанавливаем id записи;
    m_LogEntryIDGenerator++;                                   // увеличиваем счётчик записей;
}
