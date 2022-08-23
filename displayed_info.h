/*
*  ����� Info �������� ������� ��� �������,
*   ��� ��� ����� ��������� � ���������� ����������
* 
*  ����� DevInfo �������� �� ��������������
*   ���������� �� ����������
* 
*  ����� LogEntry ������ ������� ���
*   ������� � ������� ��������
*/

#ifndef __INFO_H__
#define __INFO_H__

#include <string>
#include <list>

using std::string;
using std::list;

class Circuit;
class Dev;
class DevAnalog;
class DevDigit;
class DevConvert;

class Info
{
public:

    virtual const string toString() const = 0;      // ����� ��� �������������� ����������
                                                    // � ��������-�������� ������;
};

class DevInfo : public Info
{
private:

    void makeConnectedDevsList(const Dev& dev);

protected:

    string m_dev_type;                              // ��� ����������;
    string m_dev_name;                              // �������� ����������;
    float m_dev_watt;                               // ������������ ��������;
    size_t m_port_size;                             // ���������� ������ � ����������;
    list<string> m_connected_devs;                  // ������������ ����������;

    float m_dev_up_volt;                            // ������� ����� ���������� (������ ��� ���������� �-�);
    float m_dev_low_volt;                           // ������ ����� ���������� (������ ��� ���������� �-�);
    float m_dev_sync_freq;                          // ������� ������������� (������ ��� �������� �-�);

public:

    DevInfo(const Dev& dev);                        // ������������ ��� ������ ����� ���������;
    DevInfo(const DevAnalog& dev);
    DevInfo(const DevDigit& dev);
    DevInfo(const DevConvert& dev);

    virtual const string toString() const;
};

class LogEntry : public Info
{
private:

    int m_id;                                       // id ������;

    int m_operation_code;                           // ��� �������� - ����� ��� ����������� ���� 
                                                    // �������� � ����������� ����������� ���������� � ���;
    int m_status_code;                              // ��� ���������� ��������;

    string m_circuit_name;                          // �������� �����;
    string m_dev1_name;                             // �������� ���������;
    string m_dev2_name;

public:

    LogEntry(const int& operation_code,
             const int& status_code,
             const string& circuit_name,
             const string& dev1_name,
             const string& dev2_name)
        : m_id(0),
        m_operation_code(operation_code),
        m_status_code(status_code),
        m_circuit_name(circuit_name),
        m_dev1_name(dev1_name),
        m_dev2_name(dev2_name) {}

    void setID(const int& id)
        { m_id = id; }

    virtual const string toString() const;
};

#endif