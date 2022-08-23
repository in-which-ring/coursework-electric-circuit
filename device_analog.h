/* 
*  Класс, моделирующий аналоговое устройство 
*
*   Подкласс класса Dev; дополнительно содержит
*    верхний и нижний уровни напряжения.
*   Все необходимые на данный момент методы реализованы
*    в классе Dev.
*/

#ifndef __DEVANALOG_H__
#define __DEVANALOG_H__

#include "device.h"
#include "displayed_info.h"

using std::string;

class DevAnalog: public Dev
{
private:

    float m_dev_up_volt;                            // dev_up_volt и dev_low_volt задают
    float m_dev_low_volt;                           // рабочий диапазон напряжений;

public:

    DevAnalog(const float& up_volt = 0.0, 
              const float& low_volt = 0.0, 
              const string& name = "dev", 
              const float& watt = 0.0, 
              const size_t& port_size = 1)
        : Dev(name, watt, port_size),
        m_dev_up_volt(up_volt),
        m_dev_low_volt(low_volt) {}

    const float& get_up_volt() const 
        { return m_dev_up_volt; }

    void set_up_volt(
        const float& up_volt) { m_dev_up_volt = up_volt; }

    const float& get_low_volt() const 
        { return m_dev_low_volt; }

    void set_low_volt(
        const float& low_volt) { m_dev_low_volt = low_volt; }

    virtual bool isAnalog() const                   // методы для определения типа устройства;
        { return true; }
    virtual bool isDigit() const
        { return false; }

    virtual DevInfo getInfo() const                 // возвращает информацию об устройстве;
        { return DevInfo(*this); }
};

#endif