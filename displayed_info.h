/*
*   ласс Info €вл€етс€ базовым дл€ классов,
*   так или иначе св€занных с обработкой информации
* 
*   ласс DevInfo отвечает за предоставление
*   информации об устройстве
* 
*   ласс LogEntry служит моделью дл€
*   записей в журнале действий
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

    virtual const string toString() const = 0;      // метод дл€ преобразовани€ информации
                                                    // в человеко-читаемую строку;
};

class DevInfo : public Info
{
private:

    void makeConnectedDevsList(const Dev& dev);

protected:

    string m_dev_type;                              // тип устройства;
    string m_dev_name;                              // название устройства;
    float m_dev_watt;                               // потребл€ема€ мощность;
    size_t m_port_size;                             // количество портов у устройства;
    list<string> m_connected_devs;                  // подключЄнные устройства;

    float m_dev_up_volt;                            // верхний порог напр€жени€ (только дл€ аналоговых у-в);
    float m_dev_low_volt;                           // нижний порог напр€жени€ (только дл€ аналоговых у-в);
    float m_dev_sync_freq;                          // частота синхронизации (только дл€ цифровых у-в);

public:

    DevInfo(const Dev& dev);                        // конструкторы дл€ разных типов устройств;
    DevInfo(const DevAnalog& dev);
    DevInfo(const DevDigit& dev);
    DevInfo(const DevConvert& dev);

    virtual const string toString() const;
};

class LogEntry : public Info
{
private:

    int m_id;                                       // id записи;

    int m_operation_code;                           // код операции - нужен дл€ определени€ типа 
                                                    // операции и корректного отображени€ информации о ней;
    int m_status_code;                              // код выполнени€ операции;

    string m_circuit_name;                          // название схемы;
    string m_dev1_name;                             // названи€ устройств;
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