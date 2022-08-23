#include "circuit.h"

Circuit::Circuit(const string& circuit_name)
    : m_circuit_name(circuit_name)
{
    LogEntry* log_entry = new LogEntry(-1, 0,                      // ��������� ������ � �������� �����;
                                circuit_name,
                                    "no_dev",
                                    "no_dev");
    m_log.push_back(log_entry);

    m_LogEntryIDGenerator = 1;                                     // ������������� id ��� ��������� ������;
}

Circuit::~Circuit()
{
    for (auto iter = m_devs.begin(); iter != m_devs.end(); iter++) // ������ ������ ��-��� ���������;
        delete iter->second;

    for (auto iter = m_log.begin(); iter != m_log.end(); iter++)   // ������ ������ ��-��� �������;
        delete *iter;
}

int Circuit::addDev(Dev* dev)
{
    if (!dev)                                                      // ��������� ��������� �� ����������;
        return -1;

    if (m_devs.count(dev->get_name()))                             // ���������, ��� �� �� ����� ����������
        return -2;                                                 // � ����� �� ������, ��� � *dev;

    m_devs.insert(std::pair<string, Dev*>(dev->get_name(), dev));  // ��������� ����������;

    return 0;
}

int Circuit::deleteDev(const string& dev_name)
{
    auto iter = m_devs.find(dev_name);

    if (m_devs.end() == iter)                                  // ���������, ���� �� �� ����� ����������
        return -1;                                             // � ����� ������, ��� � *dev;

    m_devs.erase(iter);                                        // ������� ����������;

    return 0;
}

bool Circuit::isContain(const string& dev_name)
{
    return m_devs.count(dev_name);
}

Dev* Circuit::getDev(const string& dev_name)
{
    auto iter = m_devs.find(dev_name);

    if (m_devs.end() == iter)                                  // ���������, ���� �� �� ����� ����������
        return nullptr;                                        // � ����� ������, ��� � dev*;

    return iter->second;
}

void Circuit::addLogEntry(LogEntry* log_entry)
{
    m_log.push_back(log_entry);                                // ��������� ������ � ������;
    log_entry->setID(m_LogEntryIDGenerator);                   // ������������� id ������;
    m_LogEntryIDGenerator++;                                   // ����������� ������� �������;
}
