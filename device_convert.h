/*
*  ����� - ����������-���������������
*
*   �������� ������ Dev; ��������� ��� ����������
*    ���������� � �������� �������� ����� �����.
*   ��� ����������� �� ������ ������ ������ �����������
*    � ������ Dev.
*/

#ifndef __DEVCONVERT_H__
#define __DEVCONVERT_H__

#include "device.h"
#include "displayed_info.h"

using std::string;

class DevConvert : public Dev
{
private:

public:

    DevConvert(const string& name = "dev",
               const float& watt = 0.0)
        : Dev(name, watt, 2) {}

    virtual bool isAnalog() const                   // ������ ��� ����������� ���� ����������;
        { return true; }
    virtual bool isDigit() const
        { return true; }

    virtual DevInfo getInfo() const                 // ���������� ���������� �� ����������;
        { return DevInfo(*this); }
};

#endif