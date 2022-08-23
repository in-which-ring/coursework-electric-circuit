#include <cassert>
#include <iostream>
#include "c_wrapper.h"

//#include "operation.h"

int Dev_Tests()
{
    Dev dev1;                                          // проверяем конструктор;
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);
    assert(dev1.getPortSize() == 1);

    dev1.set_name("dev1");                             // проверяем методы-сеттеры;
    dev1.set_watt(5.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    Dev dev2("dev2", 6.0, 2);                          // проверяем конструктор;
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);
    assert(dev2.getPortSize() == 2);

    assert(dev1.getPortNum() == 0);                    // проверяем getPortNum() до "подключения";
    assert(dev1.getPortNum(dev2) == -1);
    assert(dev1.getPortNum("dev2") == -1);

    assert(dev1["dev2"] == nullptr);                   // проверяем перегруженный оператор []
    assert(dev2["dev1"] == nullptr);                   // до "подключения";

    assert(dev1.setPort(0, &dev2) == 0);               // вручную "подключаем" устройства;
    assert(dev2.setPort(0, &dev1) == 0);

    assert(dev1.getPortNum() == -1);                   // проверяем getPortNum() после "подключения";
    assert(dev1.getPortNum(dev2) == 0);
    assert(dev1.getPortNum("dev2") == 0);
    assert(dev2.getPortNum() == 1);

    assert(dev1["dev2"] == &dev2);                     // проверяем перегруженный оператор []
    assert(dev2["dev1"] == &dev1);                     // после "подключения";

    assert(dev1.getPort(0) == &dev2);                  // проверяем указатели на подключённые устройства;
    assert(dev2.getPort(0) == &dev1);


    assert(dev1.setPort(0) == 0);                      // вручную "отключаем" устройства;
    assert(dev2.setPort(0) == 0);

    assert(dev1.getPortNum() == 0);                    // проверяем getPortNum() после отключения;
    assert(dev1.getPortNum(dev2) == -1);
    assert(dev1.getPortNum("dev2") == -1);
    assert(dev2.getPortNum() == 0);

    assert(dev1["dev2"] == nullptr);                   // проверяем перегруженный оператор []
    assert(dev2["dev1"] == nullptr);                   // после "отключения";

    assert(dev1.getPort(0) == nullptr);                // проверяем указатели после отключения;
    assert(dev2.getPort(0) == nullptr);

    assert(dev1.isAnalog() == false);                  // проверяем тип устройства;
    assert(dev1.isDigit() == false);

    return 0;
}

int DevAnalog_Tests()
{
    DevAnalog dev1;                                    // проверяем конструктор;
    assert(dev1.get_up_volt() == 0.0);
    assert(dev1.get_low_volt() == 0.0);
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);

    dev1.set_name("dev1");                             // проверяем методы-сеттеры;
    dev1.set_watt(5.0);
    dev1.set_up_volt(10.0);
    dev1.set_low_volt(7.0);
    assert(dev1.get_up_volt() == 10.0);
    assert(dev1.get_low_volt() == 7.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    DevAnalog dev2(2.0, -13.0, "dev2", 6.0, 2);        // проверяем конструктор;
    assert(dev2.get_up_volt() == 2.0);
    assert(dev2.get_low_volt() == -13.0);
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);

    assert(dev1.isAnalog() == true);                   // проверяем тип устройства;
    assert(dev1.isDigit() == false);

    // аспекты , касающиеся базового класса Dev, протестированы в Dev_Tests;

    return 0;
}

int DevDigit_Tests()
{
    DevDigit dev1;                                     // проверяем конструктор;
    assert(dev1.get_sync_freq() == 0.0);
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);

    DevDigit dev2(15.0, "dev2", 6.0, 2);               // проверяем конструктор;
    assert(dev2.get_sync_freq() == 15.0);
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);

    dev1.set_name("dev1");                             // проверяем методы-сеттеры;
    dev1.set_watt(5.0);
    dev1.set_sync_freq(10.0);
    assert(dev1.get_sync_freq() == 10.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    assert(dev1.isAnalog() == false);                  // проверяем тип устройства;
    assert(dev1.isDigit() == true);

    // аспекты , касающиеся базового класса Dev, протестированы в Dev_Tests;

    return 0;
}

int DevConvert_Tests()
{
    DevConvert dev1;                                   // проверяем конструктор;
    assert(dev1.get_name() == "dev");
    assert(dev1.get_watt() == 0.0);

    DevConvert dev2("dev2", 6.0);                      // проверяем конструктор;
    assert(dev2.get_name() == "dev2");
    assert(dev2.get_watt() == 6.0);

    dev1.set_name("dev1");                             // проверяем методы-сеттеры;
    dev1.set_watt(5.0);
    assert(dev1.get_name() == "dev1");
    assert(dev1.get_watt() == 5.0);

    assert(dev1.isAnalog() == true);                   // проверяем тип устройства;
    assert(dev1.isDigit() == true);

    // аспекты , касающиеся базового класса Dev, протестированы в Dev_Tests;

    return 0;
}

int Circuit_Tests()
{
    Circuit circuit("circuit");                     // создаём схему и устройство;
    DevAnalog dev;

    assert(circuit.addDev(nullptr) == -1);          // попытка некорректного применения метода;

    assert(circuit.addDev(&dev) == 0);              // добавляем устройство в схему;

    assert(circuit.addDev(&dev) == -2);             // неудача - добавляем уже присутствующее устройство;

    assert(circuit.getDev("dev") == &dev);          // получаем по имени указатель на подключённое устройство;

    assert(circuit.deleteDev("dev") == 0);          // удаляем устройство с заданным именем;

    assert(circuit.deleteDev("dev") == -1);         // неудача - такого устройства нет в схеме;

    assert(circuit.getDev("dev") == nullptr);       // неудача - такого устройства нет в схеме;

    return 0;
}

int AddDev_Tests()
{
    Circuit circuit("circuit");                               // создаём схему;

    AddDevAnalog add_invalid_dev(nullptr);                    // задаём недопустимые параметры;
    AddDevAnalog add_invalid_dev_analog(&circuit,
                                    "inv_an_dev",
                                 0.0, -1.0, -2.0);

    AddDevDigit add_invalid_dev_digit(&circuit,
                                   "inv_d_dev",
                                  0.0, -1.0, 0);

    AddDevConvert add_invalid_dev_convert(&circuit,
                                       "inv_c_dev",
                                              -1.0);

    assert(add_invalid_dev_analog.apply() == ERROR_INCORRECT_PARAMETERS);   // пытаемся добавить устройства в схему,
    assert(add_invalid_dev_digit.apply() == ERROR_INCORRECT_PARAMETERS);    // параметры некорректные - устройства не должны
    assert(add_invalid_dev_convert.apply() == ERROR_INCORRECT_PARAMETERS);  // быть созданы;
    assert(add_invalid_dev.apply() == ERROR_INVALID_CIRCUIT);

    AddDevAnalog add_dev_analog1(&circuit,                    // задаём корректные параметры устройств;
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

    assert(add_dev_analog1.apply() == SUCCESS);               // добавляем устройства в схему,
    assert(add_dev_analog2.apply() == SUCCESS);               // все должны успешно добавиться - имена разные;
    assert(add_dev_analog3.apply() == SUCCESS);
    assert(add_dev_digit1.apply() == SUCCESS);
    assert(add_dev_convert.apply() == SUCCESS);

    assert(add_dev_analog4.apply() == ERROR_DEV_ALREADY_PRESENT);   // пытаемся добавить устройства в схему,
    assert(add_dev_digit2.apply() == ERROR_DEV_ALREADY_PRESENT);    // не должно получиться - имена совпадают 
                                                                    // с уже добавленными;

    add_invalid_dev_analog.makeLogEntry();                          // добавляем записи о всех действиях в журнал;
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
    GetLog get_log(&circuit);                                       // печатаем журнал;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int DeleteDev_Tests()
{
    Circuit circuit("circuit");                               // создаём схему;

    AddDevAnalog add_dev_analog(&circuit,                     // задаём параметры устройств;
                            "dev_analog");

    AddDevDigit add_dev_digit(&circuit,
                           "dev_digit");

    AddDevConvert add_dev_convert(&circuit,
                             "dev_convert");

    assert(add_dev_analog.apply() == SUCCESS);                // добавляем устройства в схему,
    assert(add_dev_digit.apply() == SUCCESS);                 // все должны успешно добавиться;
    assert(add_dev_convert.apply() == SUCCESS);

    add_dev_analog.makeLogEntry();                            // добавляем записи о действиях в журнал;
    add_dev_digit.makeLogEntry();
    add_dev_convert.makeLogEntry();

    DeleteDev del_dev_analog(&circuit,                        // удаляем добавленные устройства;
                         "dev_analog");

    DeleteDev del_dev_digit(&circuit,
                         "dev_digit");

    DeleteDev del_dev_convert(&circuit,
                         "dev_convert");

    assert(del_dev_analog.apply() == SUCCESS);                // устройства должны удалиться успешно;
    assert(del_dev_digit.apply() == SUCCESS);
    assert(del_dev_convert.apply() == SUCCESS);

    del_dev_analog.makeLogEntry();                            // добавляем записи о действиях в журнал;
    del_dev_digit.makeLogEntry();
    del_dev_convert.makeLogEntry();

    DeleteDev del_dev(&circuit,                               // пытаемся удалить несуществующее устройство;
               "dev_no_exists");

    assert(del_dev.apply() == ERROR_NO_SUCH_DEV);             // не должно получиться;

    del_dev.makeLogEntry();                                   // добавляем запись в журнал;

    assert(del_dev_analog.apply() == ERROR_NO_SUCH_DEV);      // пытаемся удалить уже удалённые устройства;
    assert(del_dev_digit.apply() == ERROR_NO_SUCH_DEV);
    assert(del_dev_convert.apply() == ERROR_NO_SUCH_DEV);

    del_dev_analog.makeLogEntry();                            // добавляем записи о действиях в журнал;
    del_dev_digit.makeLogEntry();
    del_dev_convert.makeLogEntry();

    std::cout << "\nDeleteDev_Tests log\n";
    GetLog get_log(&circuit);                                 // печатаем журнал;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int ConnectDevs_Tests()
{
    Circuit circuit("circuit");                               // создаём схему;

    AddDevAnalog add_dev_analog1(&circuit,                    // задаём параметры устройств;
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

    assert(add_dev_analog1.apply() == SUCCESS);               // добавляем устройства в схему,
    assert(add_dev_digit1.apply() == SUCCESS);                // все должны успешно добавиться;

    add_dev_analog1.makeLogEntry();                           // делаем записи в журнал;
    add_dev_digit1.makeLogEntry();

    ConnectDevs con_devs_analog_1_2(&circuit,                 // задаём параметры подключения;
                               "dev_analog1",
                               "dev_analog2");

    ConnectDevs con_devs_digit_2_1(&circuit,
                               "dev_digit2",
                               "dev_digit1");

    assert(con_devs_analog_1_2.apply() == ERROR_DEV2_IS_MISSING);          // неудача - одно из устройств отсутствует в схеме;
    assert(con_devs_digit_2_1.apply() == ERROR_DEV1_IS_MISSING);

    con_devs_analog_1_2.makeLogEntry();                                    // делаем записи в журнал;
    con_devs_digit_2_1.makeLogEntry();

    assert(add_dev_analog2.apply() == SUCCESS);                            // добавляем остальные устройства в схему,
    assert(add_dev_digit2.apply() == SUCCESS);                             // все должны успешно добавиться;
    assert(add_dev_analog3.apply() == SUCCESS);
    assert(add_dev_digit3.apply() == SUCCESS);
    assert(add_dev_convert.apply() == SUCCESS);

    add_dev_analog2.makeLogEntry();                                        // делаем записи в журнал;
    add_dev_digit2.makeLogEntry();
    add_dev_analog3.makeLogEntry();
    add_dev_digit3.makeLogEntry();
    add_dev_convert.makeLogEntry();

    assert(con_devs_analog_1_2.apply() == SUCCESS);                        // повторяем попытку - всё хорошо;
    assert(con_devs_digit_2_1.apply() == SUCCESS);

    con_devs_analog_1_2.makeLogEntry();                                    // делаем записи в журнал;
    con_devs_digit_2_1.makeLogEntry();

    ConnectDevs con_devs_analog_1_3(&circuit,                              // создаём ещё соединения;
                               "dev_analog1",
                               "dev_analog3");

    ConnectDevs con_devs_digit_3_1(&circuit,
                               "dev_digit3",
                               "dev_digit1");

    assert(con_devs_analog_1_3.apply() == ERROR_DEV1_NO_FREE_PORTS);       // неудача - у устройств под номером 1 нет
    assert(con_devs_digit_3_1.apply() == ERROR_DEV2_NO_FREE_PORTS);        // свободных портов;

    con_devs_analog_1_3.makeLogEntry();                                    // делаем записи в журнал;
    con_devs_digit_3_1.makeLogEntry();

    ConnectDevs con_devs_analog_2_3(&circuit,                              // создаём ещё соединения;
                               "dev_analog2",
                               "dev_analog3");

    assert(con_devs_analog_2_3.apply() == SUCCESS);                        // соединяем устройства - всё хорошо;
    con_devs_analog_2_3.makeLogEntry();                                    // делаем запись в журнал;

    assert(con_devs_analog_2_3.apply() == ERROR_DEVS_ALREADY_CONNECTED);   // повторяем попытку - неудача,
                                                                           // устройства уже соединены;
    con_devs_analog_2_3.makeLogEntry();                                    // делаем запись в журнал;


    ConnectDevs con_devs_an2_dig2(&circuit,                                // создаём соединение устройств разных типов;
                             "dev_analog2",
                              "dev_digit3");

    assert(con_devs_an2_dig2.apply() == ERROR_DEVS_NOT_COMPATIBLE);        // неудача - устройства несовместимы;
    con_devs_an2_dig2.makeLogEntry();                                      // делаем запись в журнал;


    ConnectDevs con_devs_conv_dig2(&circuit,                               // создаём подключения к преобразователю;
                              "dev_convert",
                               "dev_digit2");

    ConnectDevs con_devs_conv_an2(&circuit,
                             "dev_convert",
                             "dev_analog2");

    assert(con_devs_conv_dig2.apply() == SUCCESS);                         // соединяем - всё хорошо;
    assert(con_devs_conv_an2.apply() == SUCCESS);

    con_devs_conv_dig2.makeLogEntry();                                     // делаем записи в журнал;
    con_devs_conv_an2.makeLogEntry();

    std::cout << "\nConnectDevs_Tests log\n";
    GetLog get_log(&circuit);                                              // печатаем журнал;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int DisconnectDevs_Tests()
{
    Circuit circuit("circuit");                               // создаём схему;

    AddDevAnalog add_dev_analog1(&circuit,                    // задаём параметры устройств;
                                 "dev_analog1");
    AddDevAnalog add_dev_analog2(&circuit,
                                 "dev_analog2",
                                 0.0, 0.0, 0.0, 3);
    AddDevDigit add_dev_digit1(&circuit,
                               "dev_digit1");
    AddDevDigit add_dev_digit2(&circuit,
                               "dev_digit2",
                               0.0, 0.0, 2);

    assert(add_dev_analog1.apply() == SUCCESS);               // добавляем устройства в схему,
    assert(add_dev_digit1.apply() == SUCCESS);                // все должны успешно добавиться;
    assert(add_dev_analog2.apply() == SUCCESS);
    assert(add_dev_digit2.apply() == SUCCESS);

    add_dev_analog1.makeLogEntry();                           // делаем записи в журнал;
    add_dev_digit1.makeLogEntry();
    add_dev_analog2.makeLogEntry();
    add_dev_digit2.makeLogEntry();

    ConnectDevs con_devs_analog_1_2(&circuit,                 // задаём параметры соединения;
                               "dev_analog1",
                               "dev_analog2");

    ConnectDevs con_devs_digit_2_1(&circuit,
                               "dev_digit2",
                               "dev_digit1");

    assert(con_devs_analog_1_2.apply() == SUCCESS);           // соединяем устройства;
    assert(con_devs_digit_2_1.apply() == SUCCESS);

    con_devs_analog_1_2.makeLogEntry();                       // делаем записи в журнал;
    con_devs_digit_2_1.makeLogEntry();

    DisconnectDevs d_con_devs_analog_1_2(&circuit,            // задаём параметры "разъединения";
                                    "dev_analog1",
                                    "dev_analog2");

    DisconnectDevs d_con_devs_digit_2_1(&circuit,
                                    "dev_digit2",
                                    "dev_digit1");

    assert(d_con_devs_analog_1_2.apply() == SUCCESS);         // разъединяем устройства - всё хорошо;
    assert(d_con_devs_digit_2_1.apply() == SUCCESS);

    d_con_devs_analog_1_2.makeLogEntry();                     // делаем записи в журнал;
    d_con_devs_digit_2_1.makeLogEntry();

    assert(d_con_devs_analog_1_2.apply() == ERROR_DEVS_NOT_CONNECTED);     // разъединяем устройства - ошибка,
    assert(d_con_devs_digit_2_1.apply() == ERROR_DEVS_NOT_CONNECTED);      // устройства уже не соединены;

    d_con_devs_analog_1_2.makeLogEntry();                                  // делаем записи в журнал;
    d_con_devs_digit_2_1.makeLogEntry();

    std::cout << "\nDisconnectDevs_Tests log\n";
    GetLog get_log(&circuit);                                              // печатаем журнал;
    get_log.apply();
    std::cout << get_log.showResult();

    return 0;
}

int GetDevInfo_Tests()
{
    Circuit circuit;

    AddDevAnalog add_dev_analog1(&circuit,                    // задаём корректные параметры устройств;
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

    assert(add_dev_analog1.apply() == SUCCESS);               // добавляем устройства в схему,
    assert(add_dev_analog2.apply() == SUCCESS);               // все должны успешно добавиться;
    assert(add_dev_digit1.apply() == SUCCESS);
    assert(add_dev_digit2.apply() == SUCCESS);
    assert(add_dev_convert.apply() == SUCCESS);

    GetDevInfo get_dev_analog1_info(&circuit,                 // задаём параметры для получения информации;
                               "dev_analog1");

    GetDevInfo get_dev_analog2_info(&circuit,
                               "dev_analog2");

    GetDevInfo get_dev_digit1_info(&circuit,
                               "dev_digit1");

    GetDevInfo get_dev_digit2_info(&circuit,
                               "dev_digit2");

    GetDevInfo get_dev_convert_info(&circuit,
                               "dev_convert");

    GetDevInfo get_dev_invalid1_info(&circuit,                // - для несуществующих устройств;
                                "dev_analog3");

    GetDevInfo get_dev_invalid2_info(&circuit,
                                "dev_invalid");

    assert(get_dev_analog1_info.apply() == SUCCESS);          // получаем информацию об устойствах,
    assert(get_dev_analog2_info.apply() == SUCCESS);          // всё хорошо - устройства присутствуют на схеме;
    assert(get_dev_digit1_info.apply() == SUCCESS);
    assert(get_dev_digit2_info.apply() == SUCCESS);
    assert(get_dev_convert_info.apply() == SUCCESS);

    assert(get_dev_invalid1_info.apply() == ERROR_NO_SUCH_DEV);  // получаем информацию об устойствах, 
    assert(get_dev_invalid2_info.apply() == ERROR_NO_SUCH_DEV);  // неудача - таких устройств на схеме нет;

    std::cout << get_dev_analog1_info.showResult();              // посмотрим результат;
    std::cout << get_dev_analog2_info.showResult();
    std::cout << get_dev_digit1_info.showResult();
    std::cout << get_dev_digit2_info.showResult();
    std::cout << get_dev_convert_info.showResult();
    std::cout << get_dev_invalid1_info.showResult();
    std::cout << get_dev_invalid2_info.showResult();

    ConnectDevs con_devs_analog_1_2(&circuit,                 // задаём параметры подключения;
                               "dev_analog1",
                               "dev_analog2");

    ConnectDevs con_devs_an_conv(&circuit,
                            "dev_analog2",
                            "dev_convert");

    ConnectDevs con_devs_conv_dig(&circuit,
                             "dev_convert",
                              "dev_digit2");

    assert(con_devs_analog_1_2.apply() == SUCCESS);           // соединяем устройства;
    assert(con_devs_an_conv.apply() == SUCCESS);
    assert(con_devs_conv_dig.apply() == SUCCESS);

    assert(get_dev_analog1_info.apply() == SUCCESS);          // получаем информацию об устойствах,
    assert(get_dev_analog2_info.apply() == SUCCESS);          // всё хорошо - устройства присутствуют на схеме;
    assert(get_dev_digit1_info.apply() == SUCCESS);
    assert(get_dev_digit2_info.apply() == SUCCESS);
    assert(get_dev_convert_info.apply() == SUCCESS);

    std::cout << get_dev_analog1_info.showResult();           // посмотрим результат;
    std::cout << get_dev_analog2_info.showResult();
    std::cout << get_dev_digit1_info.showResult();
    std::cout << get_dev_digit2_info.showResult();
    std::cout << get_dev_convert_info.showResult();

    get_dev_analog1_info.makeLogEntry();                      // сделаем записи о некоторых действиях в журнал;
    get_dev_analog2_info.makeLogEntry();
    get_dev_digit1_info.makeLogEntry();
    get_dev_digit2_info.makeLogEntry();
    get_dev_convert_info.makeLogEntry();
    get_dev_invalid1_info.makeLogEntry();
    get_dev_invalid2_info.makeLogEntry();

    std::cout << "\nGetDevInfo_Tests log\n";
    GetLog get_log(&circuit);                                 // печатаем журнал;
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