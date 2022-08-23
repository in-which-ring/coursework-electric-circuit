#include "c_wrapper.h"

Circuit* create_circuit(char* circuit_name)
{
    return new Circuit(circuit_name);
}

char* get_circuit_name(Circuit* circuit)
{
    return _strdup(circuit->get_name().c_str());
}

void delete_circuit(Circuit* circuit)
{
    delete circuit;
}

int add_dev_analog(Circuit* circuit,
                   char* dev_name,
                   float dev_watt,
                   float dev_up_volt,
                   float dev_low_volt,
                   int dev_port_size)
{
    AddDevAnalog add_dev(circuit,
                        dev_name,
                        dev_watt,
                     dev_up_volt,
                    dev_low_volt,
                   dev_port_size);

    int result = add_dev.apply();
    add_dev.makeLogEntry();

    return result;
}

int add_dev_digit(Circuit* circuit,
                  char* dev_name,
                  float dev_watt,
                  float dev_sync_freq,
                  int dev_port_size)
{
    AddDevDigit add_dev(circuit,
                       dev_name,
                       dev_watt,
                  dev_sync_freq,
                  dev_port_size);

    int result = add_dev.apply();
    add_dev.makeLogEntry();

    return result;
}

int add_dev_convert(Circuit* circuit,
                    char* dev_name,
                    float dev_watt)
{
    AddDevConvert add_dev(circuit,
                         dev_name,
                         dev_watt);

    int result = add_dev.apply();
    add_dev.makeLogEntry();

    return result;
}

int delete_dev(Circuit* circuit,
               char* dev_name)
{
    DeleteDev delete_dev(circuit,
                        dev_name);

    int result = delete_dev.apply();
    delete_dev.makeLogEntry();

    return result;
}

int connect_devs(Circuit* circuit,
                 char* dev1_name,
                 char* dev2_name)
{
    ConnectDevs connect_devs(circuit,
                           dev1_name,
                           dev2_name);

    int result = connect_devs.apply();
    connect_devs.makeLogEntry();

    return result;
}

int disconnect_devs(Circuit* circuit,
                    char* dev1_name,
                    char* dev2_name)
{
    DisconnectDevs disconnect_devs(circuit,
                                 dev1_name,
                                 dev2_name);

    int result = disconnect_devs.apply();
    disconnect_devs.makeLogEntry();

    return result;
}

char** create_dev_info()
{
    char** dev_info = new char*;
    *dev_info = nullptr;
    return dev_info;
}

void delete_dev_info(char** dev_info)
{
    delete* dev_info;
    delete dev_info;
}

char* show_dev_info(char** dev_info)
{
    return *dev_info;
}

int get_dev_info(Circuit* circuit,
                 char* dev_name,
                 char** dev_info)
{
    GetDevInfo get_dev_info(circuit,
                           dev_name);

    int result = get_dev_info.apply();
    *dev_info = _strdup(get_dev_info.showResult().c_str());
    get_dev_info.makeLogEntry();
        
    return result;
}

char** create_log()
{
    char** log = new char*;
    *log = nullptr;
    return log;
}

void delete_log(char** log)
{
    delete* log;
    delete log;
}

char* show_log(char** log)
{
    return *log;
}

int get_log(Circuit* circuit,
            char** log)
{
    GetLog get_log(circuit);

    int result = get_log.apply();
    *log = _strdup(get_log.showResult().c_str());

    return result;
}
