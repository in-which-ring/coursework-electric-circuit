#ifndef C_WRAPPER_H
#define C_WRAPPER_H

#include "operation.h"

extern "C"
{
    __declspec(dllexport) Circuit* create_circuit(char* circuit_name);

    __declspec(dllexport) char* get_circuit_name(Circuit* circuit);

    __declspec(dllexport) void delete_circuit(Circuit* circuit);

    __declspec(dllexport) int add_dev_analog(Circuit* circuit,
                                             char* dev_name,
                                             float dev_watt,
                                             float dev_up_volt,
                                             float dev_low_volt,
                                             int dev_port_size);

    __declspec(dllexport) int add_dev_digit(Circuit* circuit,
                                            char* dev_name,
                                            float dev_watt,
                                            float dev_sync_freq,
                                            int dev_port_size);

    __declspec(dllexport) int add_dev_convert(Circuit* circuit,
                                              char* dev_name,
                                              float dev_watt);

    __declspec(dllexport) int delete_dev(Circuit* circuit,
                                         char* dev_name);

    __declspec(dllexport) int connect_devs(Circuit* circuit,
                                           char* dev1_name,
                                           char* dev2_name);

    __declspec(dllexport) int disconnect_devs(Circuit* circuit,
                                              char* dev1_name,
                                              char* dev2_name);

    __declspec(dllexport) char** create_dev_info();

    __declspec(dllexport) void delete_dev_info(char** dev_info);

    __declspec(dllexport) char* show_dev_info(char** dev_info);

    __declspec(dllexport) int get_dev_info(Circuit* circuit,
                                           char* dev_name,
                                           char** dev_info);

    __declspec(dllexport) int get_log(Circuit* circuit,
                                      char** log);

    __declspec(dllexport) char** create_log();

    __declspec(dllexport) void delete_log(char** log);

    __declspec(dllexport) char* show_log(char** log);
}
#endif
