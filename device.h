/* 
*  Базовый класс для устройств электрической схемы 
*   
*   Описывает общие свойства устройств элетктрической схемы.
*   Содержит название устройства, потребляемую мощность,
*    массив с указателями на подключенные устройства.
*   Содержит методы для получения номера свободного 
*    порта, номера порта подключенного устройства по имени 
*    или указателю.
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

    string m_dev_name;                               // название устройства;
    float m_dev_watt;                                // потребляемая мощность;
    vector<Dev*> m_dev_ports;                        // порты для подключения к другим устройствам;

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

    int getPortNum() const;                         // возвращает наименьший из индексов, соответствующих NULL-указателям
                                                    // в массиве m_dev_CI;

    int getPortNum(                                 // возвращает номер порта, к которому подключено устройство slave;
        const Dev& slave) const;

    int getPortNum(                                 // возвращает номер порта, к которому подключено устройство с именем
        const string& slave_name) const;            // slave_name;

    const Dev* getPort(                             // возвращает указатель на устройство, подключенное
        const size_t& port_num) const;              // к порту с номером port_num;

    int setPort(                                    // устанавливает значение порта под номером port_num;
        const size_t& port_num,
        Dev* slave = nullptr);

    virtual bool isAnalog() const                   // эти методы понадобятся при определении типа устройства;
        { return false; }
    virtual bool isDigit() const
        { return false; }

    virtual DevInfo getInfo() const                 // возвращает информацию об устройстве;
        { return DevInfo(*this); }

    const Dev* operator[](                          // возвращает указатель на подключённое устройство с именем
        const string& slave_name) const;            // slave_name, если таких нет - возвращает nullptr;
};

#endif