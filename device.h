/* 
*  ������� ����� ��� ��������� ������������� ����� 
*   
*   ��������� ����� �������� ��������� �������������� �����.
*   �������� �������� ����������, ������������ ��������,
*    ������ � ����������� �� ������������ ����������.
*   �������� ������ ��� ��������� ������ ���������� 
*    �����, ������ ����� ������������� ���������� �� ����� 
*    ��� ���������.
*/

#ifndef __DEV_H__
#define __DEV_H__

#include <vector>
#include <string>

#include "displayed_info.h"

using std::vector;
using std::string;

class Dev
{
private:

    string m_dev_name;                               // �������� ����������;
    float m_dev_watt;                                // ������������ ��������;
    vector<Dev*> m_dev_ports;                        // ����� ��� ����������� � ������ �����������;

public:

    Dev(const string& name = "dev", 
        const float& watt = 0.0, 
        const size_t& port_size = 1)
        : m_dev_name(name),
        m_dev_watt(watt),
        m_dev_ports (port_size, nullptr) {}

    virtual ~Dev();

    const string& get_name() const 
        { return m_dev_name; }

    void set_name(
        const string& name) { m_dev_name = name; }

    const float& get_watt() 
        const { return m_dev_watt; }

    void set_watt(
        const float& watt) { m_dev_watt = watt; }

    size_t getPortSize() const
        { return m_dev_ports.size(); }

    int getPortNum() const;                         // ���������� ���������� �� ��������, ��������������� NULL-����������
                                                    // � ������� m_dev_CI;

    int getPortNum(                                 // ���������� ����� �����, � �������� ���������� ���������� slave;
        const Dev& slave) const;

    int getPortNum(                                 // ���������� ����� �����, � �������� ���������� ���������� � ������
        const string& slave_name) const;            // slave_name;

    const Dev* getPort(                             // ���������� ��������� �� ����������, ������������
        const size_t& port_num) const;              // � ����� � ������� port_num;

    int setPort(                                    // ������������� �������� ����� ��� ������� port_num;
        const size_t& port_num,
        Dev* slave = nullptr);

    virtual bool isAnalog() const                   // ��� ������ ����������� ��� ����������� ���� ����������;
        { return false; }
    virtual bool isDigit() const
        { return false; }

    virtual DevInfo getInfo() const                 // ���������� ���������� �� ����������;
        { return DevInfo(*this); }

    const Dev* operator[](                          // ���������� ��������� �� ������������ ���������� � ������
        const string& slave_name) const;            // slave_name, ���� ����� ��� - ���������� nullptr;
};

#endif