/* 
*  ����� - �������� ����������  
*
*   �������� ������ Dev; ������������� ��������
*    ������� ������������� ����������.
*   ��� ����������� �� ������ ������ ������ �����������
*    � ������ Dev.
*/

#ifndef __DEVDIGIT_H__
#define __DEVDIGIT_H__

#include "device.h"
#include "displayed_info.h"

using std::string;

class DevDigit: public Dev
{
private:

    float m_dev_sync_freq;                          // ������� ������������� ����������;

public:

    DevDigit(const float& sync_freq = 0.0, 
             const string& name = "dev",
             const float& watt = 0.0, 
             const size_t& port_size = 1)
        : Dev(name, watt, port_size),
        m_dev_sync_freq(sync_freq) {}

    const float& get_sync_freq() const 
        { return m_dev_sync_freq; }

    void set_sync_freq(
        const float& sync_freq) { m_dev_sync_freq = sync_freq; }

    virtual bool isAnalog() const                   // ������ ��� ����������� ���� ����������;
        { return false; }
    virtual bool isDigit() const
        { return true; }

    virtual DevInfo getInfo() const                 // ���������� ���������� �� ����������;
        { return DevInfo(*this); }
};

#endif