#include <cassert>
#include <iostream>
#include "c_wrapper.h"

//#include "operation.h"

int Dev_Tests()
{
    Dev dev1;                                          // ��������� �����������;
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);
    assert(dev1.getPortSize() == 1);

    dev1.set_name("dev1");                             // ��������� ������-�������;
    dev1.set_watt(5.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    Dev dev2("dev2", 6.0, 2);                          // ��������� �����������;
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);
    assert(dev2.getPortSize() == 2);

    assert(dev1.getPortNum() == 0);                    // ��������� getPortNum() �� "�����������";
    assert(dev1.getPortNum(dev2) == -1);
    assert(dev1.getPortNum("dev2") == -1);

    assert(dev1["dev2"] == nullptr);                   // ��������� ������������� �������� []
    assert(dev2["dev1"] == nullptr);                   // �� "�����������";

    assert(dev1.setPort(0, &dev2) == 0);               // ������� "����������" ����������;
    assert(dev2.setPort(0, &dev1) == 0);

    assert(dev1.getPortNum() == -1);                   // ��������� getPortNum() ����� "�����������";
    assert(dev1.getPortNum(dev2) == 0);
    assert(dev1.getPortNum("dev2") == 0);
    assert(dev2.getPortNum() == 1);

    assert(dev1["dev2"] == &dev2);                     // ��������� ������������� �������� []
    assert(dev2["dev1"] == &dev1);                     // ����� "�����������";

    assert(dev1.getPort(0) == &dev2);                  // ��������� ��������� �� ������������ ����������;
    assert(dev2.getPort(0) == &dev1);


    assert(dev1.setPort(0) == 0);                      // ������� "���������" ����������;
    assert(dev2.setPort(0) == 0);

    assert(dev1.getPortNum() == 0);                    // ��������� getPortNum() ����� ����������;
    assert(dev1.getPortNum(dev2) == -1);
    assert(dev1.getPortNum("dev2") == -1);
    assert(dev2.getPortNum() == 0);

    assert(dev1["dev2"] == nullptr);                   // ��������� ������������� �������� []
    assert(dev2["dev1"] == nullptr);                   // ����� "����������";

    assert(dev1.getPort(0) == nullptr);                // ��������� ��������� ����� ����������;
    assert(dev2.getPort(0) == nullptr);

    assert(dev1.isAnalog() == false);                  // ��������� ��� ����������;
    assert(dev1.isDigit() == false);

    return 0;
}

int DevAnalog_Tests()
{
    DevAnalog dev1;                                    // ��������� �����������;
    assert(dev1.get_up_volt() == 0.0);
    assert(dev1.get_low_volt() == 0.0);
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);

    dev1.set_name("dev1");                             // ��������� ������-�������;
    dev1.set_watt(5.0);
    dev1.set_up_volt(10.0);
    dev1.set_low_volt(7.0);
    assert(dev1.get_up_volt() == 10.0);
    assert(dev1.get_low_volt() == 7.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    DevAnalog dev2(2.0, -13.0, "dev2", 6.0, 2);        // ��������� �����������;
    assert(dev2.get_up_volt() == 2.0);
    assert(dev2.get_low_volt() == -13.0);
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);

    assert(dev1.isAnalog() == true);                   // ��������� ��� ����������;
    assert(dev1.isDigit() == false);

    // ������� , ���������� �������� ������ Dev, �������������� � Dev_Tests;

    return 0;
}

int DevDigit_Tests()
{
    DevDigit dev1;                                     // ��������� �����������;
    assert(dev1.get_sync_freq() == 0.0);
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);

    DevDigit dev2(15.0, "dev2", 6.0, 2);               // ��������� �����������;
    assert(dev2.get_sync_freq() == 15.0);
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);

    dev1.set_name("dev1");                             // ��������� ������-�������;
    dev1.set_watt(5.0);
    dev1.set_sync_freq(10.0);
    assert(dev1.get_sync_freq() == 10.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    assert(dev1.isAnalog() == false);                  // ��������� ��� ����������;
    assert(dev1.isDigit() == true);

    // ������� , ���������� �������� ������ Dev, �������������� � Dev_Tests;

    return 0;
}

int DevConvert_Tests()
{
    DevConvert dev1;                                   // ��������� �����������;
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);

    DevConvert dev2("dev2", 6.0);                      // ��������� �����������;
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);

    dev1.set_name("dev1");                             // ��������� ������-�������;
    dev1.set_watt(5.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    assert(dev1.isAnalog() == true);                   // ��������� ��� ����������;
    assert(dev1.isDigit() == true);

    // ������� , ���������� �������� ������ Dev, �������������� � Dev_Tests;

    return 0;
}

int Circuit_Tests()
{
    Circuit circuit("circuit");                     // ������ ����� � ����������;
    DevAnalog dev;

    assert(circuit.addDev(nullptr) == -1);          // ������� ������������� ���������� ������;

    assert(circuit.addDev(&dev) == 0);              // ��������� ���������� � �����;

    assert(circuit.addDev(&dev) == -2);             // ������� - ��������� ��� �������������� ����������;

    assert(circuit.getDev("dev") == &dev);          // �������� �� ����� ��������� �� ������������ ����������;

    assert(circuit.deleteDev("dev") == 0);          // ������� ���������� � �������� ������;

    assert(circuit.deleteDev("dev") == -1);         // ������� - ������ ���������� ��� � �����;

    assert(circuit.getDev("dev") == nullptr);       // ������� - ������ ���������� ��� � �����;

    return 0;
}

int AddDev_Tests()
{
    Circuit circuit("circuit");                               // ������ �����;

    AddDevAnalog add_invalid_dev(nullptr);                    // ����� ������������ ���������;
    AddDevAnalog add_invalid_dev_analog(&circuit,
                                    "inv_an_dev",
                                 0.0, -1.0, -2.0);

    AddDevDigit add_invalid_dev_digit(&circuit,
                                   "inv_d_dev",
                                  0.0, -1.0, 0);

    AddDevConvert add_invalid_dev_convert(&circuit,
                                       "inv_c_dev",
                                              -1.0);

    assert(add_invalid_dev_analog.apply() == ERROR_INCORRECT_PARAMETERS);   // �������� �������� ���������� � �����,
    assert(add_invalid_dev_digit.apply() == ERROR_INCORRECT_PARAMETERS);    // ��������� ������������ - ���������� �� ������
    assert(add_invalid_dev_convert.apply() == ERROR_INCORRECT_PARAMETERS);  // ���� �������;
    assert(add_invalid_dev.apply() == ERROR_INVALID_CIRCUIT);

    AddDevAnalog add_dev_analog1(&circuit,                    // ����� ���������� ��������� ���������;
                            "dev_analog1");

    AddDevAnalog add_dev_analog2(&circuit,
                            "dev_analog2",
                         0.0, 0.0, 0.0, 3);

    AddDevAnalog add_dev_analog3(&circuit,
                                   "dev3",
                         0.0, 0.0, 0.0, 2);

    AddDevAnalog add_dev_analog4(&circuit,
                            "dev_analog2");

    AddDevDigit add_dev_digit1(&circuit,
                           "dev_digit1");

    AddDevDigit add_dev_digit2(&circuit,
                           "dev_digit1");

    AddDevConvert add_dev_convert(&circuit,
                             "dev_convert");

    assert(add_dev_analog1.apply() == SUCCESS);               // ��������� ���������� � �����,
    assert(add_dev_analog2.apply() == SUCCESS);               // ��� ������ ������� ���������� - ����� ������;
    assert(add_dev_analog3.apply() == SUCCESS);
    assert(add_dev_digit1.apply() == SUCCESS);
    assert(add_dev_convert.apply() == SUCCESS);

    assert(add_dev_analog4.apply() == ERROR_DEV_ALREADY_PRESENT);   // �������� �������� ���������� � �����,
    assert(add_dev_digit2.apply() == ERROR_DEV_ALREADY_PRESENT);    // �� ������ ���������� - ����� ��������� 
                                                                    // � ��� ������������;

    add_invalid_dev_analog.makeLogEntry();                          // ��������� ������ � ���� ��������� � ������;
    add_invalid_dev_digit.makeLogEntry();
    add_invalid_dev_convert.makeLogEntry();
    add_dev_analog1.makeLogEntry();
    add_dev_analog2.makeLogEntry();
    add_dev_analog3.makeLogEntry();
    add_dev_digit1.makeLogEntry();
    add_dev_convert.makeLogEntry();
    add_dev_analog4.makeLogEntry();
    add_dev_digit2.makeLogEntry();

    std::cout << "\nAddDev_Tests log\n";
    GetLog get_log(&circuit);                                       // �������� ������;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int DeleteDev_Tests()
{
    Circuit circuit("circuit");                               // ������ �����;

    AddDevAnalog add_dev_analog(&circuit,                     // ����� ��������� ���������;
                            "dev_analog");

    AddDevDigit add_dev_digit(&circuit,
                           "dev_digit");

    AddDevConvert add_dev_convert(&circuit,
                             "dev_convert");

    assert(add_dev_analog.apply() == SUCCESS);                // ��������� ���������� � �����,
    assert(add_dev_digit.apply() == SUCCESS);                 // ��� ������ ������� ����������;
    assert(add_dev_convert.apply() == SUCCESS);

    add_dev_analog.makeLogEntry();                            // ��������� ������ � ��������� � ������;
    add_dev_digit.makeLogEntry();
    add_dev_convert.makeLogEntry();

    DeleteDev del_dev_analog(&circuit,                        // ������� ����������� ����������;
                         "dev_analog");

    DeleteDev del_dev_digit(&circuit,
                         "dev_digit");

    DeleteDev del_dev_convert(&circuit,
                         "dev_convert");

    assert(del_dev_analog.apply() == SUCCESS);                // ���������� ������ ��������� �������;
    assert(del_dev_digit.apply() == SUCCESS);
    assert(del_dev_convert.apply() == SUCCESS);

    del_dev_analog.makeLogEntry();                            // ��������� ������ � ��������� � ������;
    del_dev_digit.makeLogEntry();
    del_dev_convert.makeLogEntry();

    DeleteDev del_dev(&circuit,                               // �������� ������� �������������� ����������;
               "dev_no_exists");

    assert(del_dev.apply() == ERROR_NO_SUCH_DEV);             // �� ������ ����������;

    del_dev.makeLogEntry();                                   // ��������� ������ � ������;

    assert(del_dev_analog.apply() == ERROR_NO_SUCH_DEV);      // �������� ������� ��� �������� ����������;
    assert(del_dev_digit.apply() == ERROR_NO_SUCH_DEV);
    assert(del_dev_convert.apply() == ERROR_NO_SUCH_DEV);

    del_dev_analog.makeLogEntry();                            // ��������� ������ � ��������� � ������;
    del_dev_digit.makeLogEntry();
    del_dev_convert.makeLogEntry();

    std::cout << "\nDeleteDev_Tests log\n";
    GetLog get_log(&circuit);                                 // �������� ������;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int ConnectDevs_Tests()
{
    Circuit circuit("circuit");                               // ������ �����;

    AddDevAnalog add_dev_analog1(&circuit,                    // ����� ��������� ���������;
                            "dev_analog1");

    AddDevAnalog add_dev_analog2(&circuit,
                            "dev_analog2",
                         0.0, 0.0, 0.0, 3);

    AddDevAnalog add_dev_analog3(&circuit,
                            "dev_analog3",
                         0.0, 0.0, 0.0, 2);

    AddDevDigit add_dev_digit1(&circuit,
                           "dev_digit1");

    AddDevDigit add_dev_digit2(&circuit,
                           "dev_digit2",
                            0.0, 0.0, 2);

    AddDevDigit add_dev_digit3(&circuit,
                           "dev_digit3");

    AddDevConvert add_dev_convert(&circuit,
                             "dev_convert");

    assert(add_dev_analog1.apply() == SUCCESS);               // ��������� ���������� � �����,
    assert(add_dev_digit1.apply() == SUCCESS);                // ��� ������ ������� ����������;

    add_dev_analog1.makeLogEntry();                           // ������ ������ � ������;
    add_dev_digit1.makeLogEntry();

    ConnectDevs con_devs_analog_1_2(&circuit,                 // ����� ��������� �����������;
                               "dev_analog1",
                               "dev_analog2");

    ConnectDevs con_devs_digit_2_1(&circuit,
                               "dev_digit2",
                               "dev_digit1");

    assert(con_devs_analog_1_2.apply() == ERROR_DEV2_IS_MISSING);          // ������� - ���� �� ��������� ����������� � �����;
    assert(con_devs_digit_2_1.apply() == ERROR_DEV1_IS_MISSING);

    con_devs_analog_1_2.makeLogEntry();                                    // ������ ������ � ������;
    con_devs_digit_2_1.makeLogEntry();

    assert(add_dev_analog2.apply() == SUCCESS);                            // ��������� ��������� ���������� � �����,
    assert(add_dev_digit2.apply() == SUCCESS);                             // ��� ������ ������� ����������;
    assert(add_dev_analog3.apply() == SUCCESS);
    assert(add_dev_digit3.apply() == SUCCESS);
    assert(add_dev_convert.apply() == SUCCESS);

    add_dev_analog2.makeLogEntry();                                        // ������ ������ � ������;
    add_dev_digit2.makeLogEntry();
    add_dev_analog3.makeLogEntry();
    add_dev_digit3.makeLogEntry();
    add_dev_convert.makeLogEntry();

    assert(con_devs_analog_1_2.apply() == SUCCESS);                        // ��������� ������� - �� ������;
    assert(con_devs_digit_2_1.apply() == SUCCESS);

    con_devs_analog_1_2.makeLogEntry();                                    // ������ ������ � ������;
    con_devs_digit_2_1.makeLogEntry();

    ConnectDevs con_devs_analog_1_3(&circuit,                              // ������ ��� ����������;
                               "dev_analog1",
                               "dev_analog3");

    ConnectDevs con_devs_digit_3_1(&circuit,
                               "dev_digit3",
                               "dev_digit1");

    assert(con_devs_analog_1_3.apply() == ERROR_DEV1_NO_FREE_PORTS);       // ������� - � ��������� ��� ������� 1 ���
    assert(con_devs_digit_3_1.apply() == ERROR_DEV2_NO_FREE_PORTS);        // ��������� ������;

    con_devs_analog_1_3.makeLogEntry();                                    // ������ ������ � ������;
    con_devs_digit_3_1.makeLogEntry();

    ConnectDevs con_devs_analog_2_3(&circuit,                              // ������ ��� ����������;
                               "dev_analog2",
                               "dev_analog3");

    assert(con_devs_analog_2_3.apply() == SUCCESS);                        // ��������� ���������� - �� ������;
    con_devs_analog_2_3.makeLogEntry();                                    // ������ ������ � ������;

    assert(con_devs_analog_2_3.apply() == ERROR_DEVS_ALREADY_CONNECTED);   // ��������� ������� - �������,
                                                                           // ���������� ��� ���������;
    con_devs_analog_2_3.makeLogEntry();                                    // ������ ������ � ������;


    ConnectDevs con_devs_an2_dig2(&circuit,                                // ������ ���������� ��������� ������ �����;
                             "dev_analog2",
                              "dev_digit3");

    assert(con_devs_an2_dig2.apply() == ERROR_DEVS_NOT_COMPATIBLE);        // ������� - ���������� ������������;
    con_devs_an2_dig2.makeLogEntry();                                      // ������ ������ � ������;


    ConnectDevs con_devs_conv_dig2(&circuit,                               // ������ ����������� � ���������������;
                              "dev_convert",
                               "dev_digit2");

    ConnectDevs con_devs_conv_an2(&circuit,
                             "dev_convert",
                             "dev_analog2");

    assert(con_devs_conv_dig2.apply() == SUCCESS);                         // ��������� - �� ������;
    assert(con_devs_conv_an2.apply() == SUCCESS);

    con_devs_conv_dig2.makeLogEntry();                                     // ������ ������ � ������;
    con_devs_conv_an2.makeLogEntry();

    std::cout << "\nConnectDevs_Tests log\n";
    GetLog get_log(&circuit);                                              // �������� ������;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int DisconnectDevs_Tests()
{
    Circuit circuit("circuit");                               // ������ �����;

    AddDevAnalog add_dev_analog1(&circuit,                    // ����� ��������� ���������;
                                 "dev_analog1");
    AddDevAnalog add_dev_analog2(&circuit,
                                 "dev_analog2",
                                 0.0, 0.0, 0.0, 3);
    AddDevDigit add_dev_digit1(&circuit,
                               "dev_digit1");
    AddDevDigit add_dev_digit2(&circuit,
                               "dev_digit2",
                               0.0, 0.0, 2);

    assert(add_dev_analog1.apply() == SUCCESS);               // ��������� ���������� � �����,
    assert(add_dev_digit1.apply() == SUCCESS);                // ��� ������ ������� ����������;
    assert(add_dev_analog2.apply() == SUCCESS);
    assert(add_dev_digit2.apply() == SUCCESS);

    add_dev_analog1.makeLogEntry();                           // ������ ������ � ������;
    add_dev_digit1.makeLogEntry();
    add_dev_analog2.makeLogEntry();
    add_dev_digit2.makeLogEntry();

    ConnectDevs con_devs_analog_1_2(&circuit,                 // ����� ��������� ����������;
                               "dev_analog1",
                               "dev_analog2");

    ConnectDevs con_devs_digit_2_1(&circuit,
                               "dev_digit2",
                               "dev_digit1");

    assert(con_devs_analog_1_2.apply() == SUCCESS);           // ��������� ����������;
    assert(con_devs_digit_2_1.apply() == SUCCESS);

    con_devs_analog_1_2.makeLogEntry();                       // ������ ������ � ������;
    con_devs_digit_2_1.makeLogEntry();

    DisconnectDevs d_con_devs_analog_1_2(&circuit,            // ����� ��������� "������������";
                                    "dev_analog1",
                                    "dev_analog2");

    DisconnectDevs d_con_devs_digit_2_1(&circuit,
                                    "dev_digit2",
                                    "dev_digit1");

    assert(d_con_devs_analog_1_2.apply() == SUCCESS);         // ����������� ���������� - �� ������;
    assert(d_con_devs_digit_2_1.apply() == SUCCESS);

    d_con_devs_analog_1_2.makeLogEntry();                     // ������ ������ � ������;
    d_con_devs_digit_2_1.makeLogEntry();

    assert(d_con_devs_analog_1_2.apply() == ERROR_DEVS_NOT_CONNECTED);     // ����������� ���������� - ������,
    assert(d_con_devs_digit_2_1.apply() == ERROR_DEVS_NOT_CONNECTED);      // ���������� ��� �� ���������;

    d_con_devs_analog_1_2.makeLogEntry();                                  // ������ ������ � ������;
    d_con_devs_digit_2_1.makeLogEntry();

    std::cout << "\nDisconnectDevs_Tests log\n";
    GetLog get_log(&circuit);                                              // �������� ������;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int GetDevInfo_Tests()
{
    Circuit circuit;

    AddDevAnalog add_dev_analog1(&circuit,                    // ����� ���������� ��������� ���������;
                            "dev_analog1");

    AddDevAnalog add_dev_analog2(&circuit,
                            "dev_analog2",
                         0.0, 0.0, 0.0, 3);

    AddDevDigit add_dev_digit1(&circuit,
                           "dev_digit1");

    AddDevDigit add_dev_digit2(&circuit,
                           "dev_digit2",
                          5.0, 130.0, 2);

    AddDevConvert add_dev_convert(&circuit,
                             "dev_convert");

    assert(add_dev_analog1.apply() == SUCCESS);               // ��������� ���������� � �����,
    assert(add_dev_analog2.apply() == SUCCESS);               // ��� ������ ������� ����������;
    assert(add_dev_digit1.apply() == SUCCESS);
    assert(add_dev_digit2.apply() == SUCCESS);
    assert(add_dev_convert.apply() == SUCCESS);

    GetDevInfo get_dev_analog1_info(&circuit,                 // ����� ��������� ��� ��������� ����������;
                               "dev_analog1");

    GetDevInfo get_dev_analog2_info(&circuit,
                               "dev_analog2");

    GetDevInfo get_dev_digit1_info(&circuit,
                               "dev_digit1");

    GetDevInfo get_dev_digit2_info(&circuit,
                               "dev_digit2");

    GetDevInfo get_dev_convert_info(&circuit,
                               "dev_convert");

    GetDevInfo get_dev_invalid1_info(&circuit,                // - ��� �������������� ���������;
                                "dev_analog3");

    GetDevInfo get_dev_invalid2_info(&circuit,
                                "dev_invalid");

    assert(get_dev_analog1_info.apply() == SUCCESS);          // �������� ���������� �� ����������,
    assert(get_dev_analog2_info.apply() == SUCCESS);          // �� ������ - ���������� ������������ �� �����;
    assert(get_dev_digit1_info.apply() == SUCCESS);
    assert(get_dev_digit2_info.apply() == SUCCESS);
    assert(get_dev_convert_info.apply() == SUCCESS);

    assert(get_dev_invalid1_info.apply() == ERROR_NO_SUCH_DEV);  // �������� ���������� �� ����������, 
    assert(get_dev_invalid2_info.apply() == ERROR_NO_SUCH_DEV);  // ������� - ����� ��������� �� ����� ���;

    std::cout << get_dev_analog1_info.showResult();              // ��������� ���������;
    std::cout << get_dev_analog2_info.showResult();
    std::cout << get_dev_digit1_info.showResult();
    std::cout << get_dev_digit2_info.showResult();
    std::cout << get_dev_convert_info.showResult();
    std::cout << get_dev_invalid1_info.showResult();
    std::cout << get_dev_invalid2_info.showResult();

    ConnectDevs con_devs_analog_1_2(&circuit,                 // ����� ��������� �����������;
                               "dev_analog1",
                               "dev_analog2");

    ConnectDevs con_devs_an_conv(&circuit,
                            "dev_analog2",
                            "dev_convert");

    ConnectDevs con_devs_conv_dig(&circuit,
                             "dev_convert",
                              "dev_digit2");

    assert(con_devs_analog_1_2.apply() == SUCCESS);           // ��������� ����������;
    assert(con_devs_an_conv.apply() == SUCCESS);
    assert(con_devs_conv_dig.apply() == SUCCESS);

    assert(get_dev_analog1_info.apply() == SUCCESS);          // �������� ���������� �� ����������,
    assert(get_dev_analog2_info.apply() == SUCCESS);          // �� ������ - ���������� ������������ �� �����;
    assert(get_dev_digit1_info.apply() == SUCCESS);
    assert(get_dev_digit2_info.apply() == SUCCESS);
    assert(get_dev_convert_info.apply() == SUCCESS);

    std::cout << get_dev_analog1_info.showResult();           // ��������� ���������;
    std::cout << get_dev_analog2_info.showResult();
    std::cout << get_dev_digit1_info.showResult();
    std::cout << get_dev_digit2_info.showResult();
    std::cout << get_dev_convert_info.showResult();

    get_dev_analog1_info.makeLogEntry();                      // ������� ������ � ��������� ��������� � ������;
    get_dev_analog2_info.makeLogEntry();
    get_dev_digit1_info.makeLogEntry();
    get_dev_digit2_info.makeLogEntry();
    get_dev_convert_info.makeLogEntry();
    get_dev_invalid1_info.makeLogEntry();
    get_dev_invalid2_info.makeLogEntry();

    std::cout << "\nGetDevInfo_Tests log\n";
    GetLog get_log(&circuit);                                 // �������� ������;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int C_Dll_Tests()
{
    char circuit_name[] = "circuit";
    char dev_name[] = "dev";
    int* dev_info_res = new int;

    Circuit* circuit = create_circuit(circuit_name);
    int add_res = add_dev_convert(circuit, dev_name, 0.0);
    char* dev_info = get_dev_info(circuit, dev_name, dev_info_res);

    std::cout << add_res;
    std::cout << *dev_info_res;
    std::cout << dev_info;

    free_C_string(dev_info);
    //delete[] circuit_name;
    //delete[] dev_name;

    return 0;
}

int main()
{
    Dev_Tests();
    DevAnalog_Tests();
    DevDigit_Tests();
    DevConvert_Tests();
    Circuit_Tests();
    AddDev_Tests();
    DeleteDev_Tests();
    ConnectDevs_Tests();
    DisconnectDevs_Tests();
    GetDevInfo_Tests();
    C_Dll_Tests();

    return 0;
}