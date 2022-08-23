/*
*  Здесь содержатся классы всех операций со схемой/устройствами
*  Поля классов - параметры операции
*  Для каждой операции есть виртуальный метод apply(),
*   выполняющий эту операцию
* 
*  AddDev и его потомки - добавить устройство с заданными
*   параметрами в схему
*
*  DeleteDev - удалить из схемы устройство с заданным именем
* 
*  ConnectDevs - соединить устройства с заданными именами
* 
*  DisconnectDevs - разъединить устройства с заданными именами
* 
*  GetDevInfo - получить информацию об устройстве с заданным именем
* 
*  GetLog - получить журнал действий
*/

#ifndef __OPERATION_H__
#define __OPERATION_H__

#include "circuit.h"
#include "device.h"
#include "device_analog.h"
#include "device_digit.h"
#include "device_convert.h"

using std::string;

enum Operations
{
    CREATE_CIRCUIT = -1,
    OPERATION,
    UNARY_OPERATION,
    BINARY_OPERATION,
    ADD_DEV,
    DELETE_DEV,
    CONNECT_DEVS,
    DISCONNECT_DEVS,
    GET_DEV_INFO
};

enum StatusCodes
{
    NOT_COMPLETE = -1,
    SUCCESS = 0,
    ERROR_INVALID_CIRCUIT,
    ERROR_INCORRECT_PARAMETERS,
    ERROR_NO_SUCH_DEV,
    ERROR_DEV_ALREADY_PRESENT,
    ERROR_DEV1_IS_MISSING,
    ERROR_DEV2_IS_MISSING,
    ERROR_DEVS_NOT_COMPATIBLE,
    ERROR_DEV1_NO_FREE_PORTS,
    ERROR_DEV2_NO_FREE_PORTS,
    ERROR_DEVS_ALREADY_CONNECTED,
    ERROR_DEVS_NOT_CONNECTED
};

class Operation
{
protected:

    Circuit* m_circuit;

    int m_operation_code;                           // код операции;
    int m_status_code;                              // код выполнения;

public:

    Operation(Circuit* circuit = nullptr,
              const int& opertaion_code = OPERATION,
              const int& status_code = NOT_COMPLETE)
        : m_circuit(circuit),
        m_operation_code(opertaion_code),
        m_status_code(status_code) {}

    virtual int apply() = 0;                        // возвращает код выполнения;
};

class UnaryOperation : public Operation
{
protected:

    string m_dev_name;

    UnaryOperation(Circuit* circuit = nullptr,
                   const string& dev_name = "dev",
                   const int& operation_code = UNARY_OPERATION)
        : Operation(circuit, operation_code),
        m_dev_name(dev_name) {}

public:

    void makeLogEntry();                            // делает запись о действии в журнал;
};

class BinaryOperation : public Operation
{
protected:

    string m_dev1_name;
    string m_dev2_name;

    BinaryOperation(Circuit* circuit = nullptr,
                    const string& dev1_name = "dev1",
                    const string& dev2_name = "dev2",
                    const int& operation_code = BINARY_OPERATION)
        : Operation(circuit, operation_code),
        m_dev1_name(dev1_name),
        m_dev2_name(dev2_name) {}

public:

    void makeLogEntry();                            // делает запись о действии в журнал;
};

class AddDev : public UnaryOperation
{
protected:

    float m_dev_watt;
    size_t m_dev_ports_num;

    AddDev(Circuit* circuit = nullptr, 
           const string& dev_name = "dev",
           const float& watt = 0.0, 
           const size_t& port_size = 1)
        : UnaryOperation(circuit, dev_name, ADD_DEV),
        m_dev_watt(watt),
        m_dev_ports_num(port_size) {}

public:

    virtual int apply() = 0;
};

class AddDevAnalog : public AddDev
{
private:

    float m_dev_up_volt;
    float m_dev_low_volt;

public:

    AddDevAnalog(Circuit* circuit = nullptr, 
                 const string& dev_name = "dev",
                 const float& watt = 0.0, 
                 const float& up_volt = 0.0, 
                 const float& low_volt = 0.0, 
                 const size_t& port_size = 1)
        : AddDev(circuit, dev_name, watt, port_size),
        m_dev_up_volt(up_volt),
        m_dev_low_volt(low_volt) {}

    virtual int apply();
};

class AddDevDigit : public AddDev
{
private:

    float m_dev_sync_freq;

public:

    AddDevDigit(Circuit* circuit = nullptr, 
                const string& dev_name = "dev",
                const float& watt = 0.0, 
                const float& sync_freq = 0.0,
                const size_t& port_size = 1)
        : AddDev(circuit, dev_name, watt, port_size),
        m_dev_sync_freq(sync_freq) {}

    virtual int apply();
};

class AddDevConvert : public AddDev
{
public:

    AddDevConvert(Circuit* circuit = nullptr, 
                  const string& dev_name = "dev",
                  const float& watt = 0.0)
        : AddDev(circuit, dev_name, watt, 2) {}

    virtual int apply();
};

class DeleteDev : public UnaryOperation
{
public:

    DeleteDev(Circuit* circuit = nullptr, 
              const string& dev_name = "dev")
        : UnaryOperation(circuit, dev_name, DELETE_DEV) {}

    virtual int apply();
};

class ConnectDevs : public BinaryOperation
{
public:

    ConnectDevs(Circuit* circuit = nullptr, 
                const string& dev1_name = "dev1",
                const string& dev2_name = "dev2")
        : BinaryOperation(circuit, dev1_name, dev2_name, CONNECT_DEVS) {}

    virtual int apply();
};

class DisconnectDevs : public BinaryOperation
{
public:

    DisconnectDevs(Circuit* circuit = nullptr, 
                   const string& dev1_name = "dev1",
                   const string& dev2_name = "dev2")
        : BinaryOperation(circuit, dev1_name, dev2_name, DISCONNECT_DEVS) {}

    virtual int apply();
};

class GetDevInfo : public UnaryOperation
{
private:

    string m_dev_info;

public:

    GetDevInfo(Circuit* circuit = nullptr,
               const string& dev_name = "dev")
        : UnaryOperation(circuit, dev_name, GET_DEV_INFO),
        m_dev_info("\nNo_info\n") {}

    virtual int apply();

    const string& showResult() const
        { return m_dev_info; }
};

class GetLog : public Operation
{
private:

    string m_log;

public:

    GetLog(Circuit* circuit = nullptr)
        : Operation(circuit) {}

    virtual int apply();

    const string& showResult() const
        { return m_log; }
};

#endif