/*
*  Класс - устройство-преобразователь
*
*   Подкласс класса Dev; необходим для соединения
*    аналоговых и цифровых устройтв между собой.
*   Все необходимые на данный момент методы реализованы
*    в классе Dev.
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

    virtual bool isAnalog() const                   // методы для определения типа устройства;
        { return true; }
    virtual bool isDigit() const
        { return true; }

    virtual DevInfo getInfo() const                 // возвращает информацию об устройстве;
        { return DevInfo(*this); }
};

#endif