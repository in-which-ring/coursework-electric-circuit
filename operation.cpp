#include "operation.h"

void UnaryOperation::makeLogEntry()
{
    if (m_circuit && (m_status_code != NOT_COMPLETE))
    {
        LogEntry* log_entry = new LogEntry(m_operation_code,    // делаем запись в лог;
                                              m_status_code,
                                      m_circuit->get_name(),
                                                 m_dev_name,
                                                   "no_dev");

        m_circuit->addLogEntry(log_entry);
    }
}

void BinaryOperation::makeLogEntry()
{
    if (m_circuit)
    {
        LogEntry* log_entry = new LogEntry(m_operation_code,    // делаем запись в лог;
                                              m_status_code,
                                      m_circuit->get_name(),
                                                m_dev1_name,
                                                m_dev2_name);

        m_circuit->addLogEntry(log_entry);
    }
}

int AddDevAnalog::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;

    else if (m_dev_up_volt   < 0.0 ||                           // проверяем корректность параметров;
             m_dev_low_volt  < 0.0 ||
             m_dev_watt      < 0.0 ||
             m_dev_ports_num < 1)
        m_status_code = ERROR_INCORRECT_PARAMETERS;

    else if (m_circuit->isContain(m_dev_name))                  // проверяем, нет ли в схеме устройства
        m_status_code = ERROR_DEV_ALREADY_PRESENT;              // с именем m_dev_name;

    else                                                        // если всё хорошо;
    {
        m_status_code = SUCCESS;

        DevAnalog* dev = new DevAnalog(m_dev_up_volt,           // создаём устройство с заданными параметрами;
                                       m_dev_low_volt,
                                       m_dev_name,
                                       m_dev_watt,
                                       m_dev_ports_num);

        m_circuit->addDev(dev);                                 // добавляем устройство на схему;
    }

    return m_status_code;
}

int AddDevDigit::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;

    else if (m_dev_sync_freq < 0.0 ||                           // проверяем корректность параметров;
             m_dev_watt      < 0.0 ||
             m_dev_ports_num < 1)
        m_status_code = ERROR_INCORRECT_PARAMETERS;

    else if (m_circuit->isContain(m_dev_name))                  // проверяем, нет ли в схеме устройства
        m_status_code = ERROR_DEV_ALREADY_PRESENT;              // с именем m_dev_name;

    else                                                        // если всё хорошо;
    {
        m_status_code = SUCCESS;

        DevDigit* dev = new DevDigit(m_dev_sync_freq,           // создаём устройство с заданными параметрами;
                                     m_dev_name,
                                     m_dev_watt,
                                     m_dev_ports_num);

        m_circuit->addDev(dev);                                 // добавляем устройство на схему;
    }

    return m_status_code;
}

int AddDevConvert::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;

    else if (m_dev_watt      < 0.0 ||                           // проверяем корректность параметров;
             m_dev_ports_num < 1)
        m_status_code = ERROR_INCORRECT_PARAMETERS;

    else if (m_circuit->isContain(m_dev_name))                  // проверяем, нет ли в схеме устройства
        m_status_code = ERROR_DEV_ALREADY_PRESENT;              // с именем m_dev_name;
 
    else                                                        // если всё хорошо;
    {
        m_status_code = SUCCESS;

        DevConvert* dev = new DevConvert(m_dev_name,            // создаём устройство с заданными параметрами;
                                         m_dev_watt);

        m_circuit->addDev(dev);                                 // добавляем устройство на схему;
    }

    return m_status_code;
}

int DeleteDev::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;
    else
    {
        Dev* dev = m_circuit->getDev(m_dev_name);               // ищем устройство с заданным именем;

        if (dev)                                                // если нашли;
        {
            m_status_code = SUCCESS;
            
            m_circuit->deleteDev(m_dev_name);                   // удаляем устройство и освобождаем память;
            delete dev;
        }
        else                                                    // иначе;
            m_status_code = ERROR_NO_SUCH_DEV;
    }

    return m_status_code;
}

int ConnectDevs::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;
    else
    {
        Dev* dev1 = m_circuit->getDev(m_dev1_name);
        Dev* dev2 = m_circuit->getDev(m_dev2_name);

        if (!dev1)                                            // проверяем указатели на устройства - 
            m_status_code = ERROR_DEV1_IS_MISSING;            // есть ли на схеме устройства с такими именами;

        else if (!dev2)
            m_status_code = ERROR_DEV2_IS_MISSING;

        else
        {
            if (dev1->isAnalog() && dev2->isAnalog() ||       // проверяем совместимость типов устройств;
                dev1->isDigit() && dev2->isDigit())
            {
                int dev1_port_num = dev1->getPortNum();       // ищем свободные порты для подключения;
                int dev2_port_num = dev2->getPortNum();

                if (dev1_port_num == -1)                      // проверяем, есть ли свободные порты у dev1;
                    m_status_code = ERROR_DEV1_NO_FREE_PORTS;

                else if (dev2_port_num == -1)                 // проверяем, есть ли свободные порты у dev2;
                    m_status_code = ERROR_DEV2_NO_FREE_PORTS;

                else if ((dev1->getPortNum(*dev2) != -1) ||   // проверяем, не подключены ли устройства
                         (dev2->getPortNum(*dev1) != -1))     // друг к другу;
                    m_status_code = ERROR_DEVS_ALREADY_CONNECTED;

                else
                {
                    m_status_code = SUCCESS;

                    dev1->setPort(dev1_port_num, dev2);       // подключаем устройства;
                    dev2->setPort(dev2_port_num, dev1);
                }
            }
            else
                m_status_code = ERROR_DEVS_NOT_COMPATIBLE;    // - в случае несовместимости устройств;
        }
    }

    return m_status_code;
}

int DisconnectDevs::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;
    else
    {
        Dev* dev1 = m_circuit->getDev(m_dev1_name);
        Dev* dev2 = m_circuit->getDev(m_dev2_name);

        if (!dev1)                                            // проверяем указатели на устройства - 
            m_status_code = ERROR_DEV1_IS_MISSING;            // есть ли на схеме устройства с такими именами;

        else if (!dev2)
            m_status_code = ERROR_DEV2_IS_MISSING;

        else
        {
            int dev1_port_num = dev1->getPortNum(*dev2);      // ищем порты подключения;
            int dev2_port_num = dev2->getPortNum(*dev1);

            if (dev1_port_num == -1 || dev2_port_num == -1)   // проверяем, подключено ли к устройства
                m_status_code = ERROR_DEVS_NOT_CONNECTED;     // друг к другу;

            else
            {
                m_status_code = SUCCESS;

                dev1->setPort(dev1_port_num, nullptr);        // отключаем устройства;
                dev2->setPort(dev2_port_num, nullptr);

            }
        }
    }

    return m_status_code;
}

int GetDevInfo::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;
    else
    {
        Dev* dev = m_circuit->getDev(m_dev_name);               // ищем устройство с заданным именем;

        if (dev)                                                // если нашли;
        {
            m_status_code = SUCCESS;

            m_dev_info = dev->getInfo().toString();             // получаем данные об устройстве;
        }
        else                                                    // иначе;
            m_status_code = ERROR_NO_SUCH_DEV;
    }

    return m_status_code;
}

int GetLog::apply()
{
    if (!m_circuit)
        m_status_code = ERROR_INVALID_CIRCUIT;

    else
    {
        m_status_code = SUCCESS;

        for (auto iter = m_circuit->getLog().begin(); iter != m_circuit->getLog().end(); iter++)
            m_log.append((*iter)->toString());
    }

    return m_status_code;
}