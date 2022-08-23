#include "Operation.h"

void DevInfo::makeConnectedDevsList(const Dev& dev)
{
    for (size_t i = 0; i < dev.getPortSize(); i++)
        if (dev.getPort(i))
            m_connected_devs.push_back(dev.getPort(i)->get_name());
}

DevInfo::DevInfo(const Dev& dev)                    // получаем информацию об устройстве из самого устройства
    : m_dev_type("No_type"),
    m_dev_name(dev.get_name()),
    m_dev_watt(dev.get_watt()),
    m_port_size(dev.getPortSize()),
    m_dev_up_volt(-1.0),
    m_dev_low_volt(-1.0),
    m_dev_sync_freq(-1.0)
{
    makeConnectedDevsList(dev);
}

DevInfo::DevInfo(const DevAnalog& dev)
    : m_dev_type("Analog"),
    m_dev_name(dev.get_name()),
    m_dev_watt(dev.get_watt()),
    m_port_size(dev.getPortSize()),
    m_dev_up_volt(dev.get_up_volt()),
    m_dev_low_volt(dev.get_low_volt()),
    m_dev_sync_freq(-1.0)
{
    makeConnectedDevsList(dev);
}

DevInfo::DevInfo(const DevDigit& dev)
    : m_dev_type("Digital"),
    m_dev_name(dev.get_name()),
    m_dev_watt(dev.get_watt()),
    m_port_size(dev.getPortSize()),
    m_dev_up_volt(-1.0),
    m_dev_low_volt(-1.0),
    m_dev_sync_freq(dev.get_sync_freq())
{
    makeConnectedDevsList(dev);
}

DevInfo::DevInfo(const DevConvert& dev)
    : m_dev_type("Converter"),
    m_dev_name(dev.get_name()),
    m_dev_watt(dev.get_watt()),
    m_port_size(dev.getPortSize()),
    m_dev_up_volt(-1.0),
    m_dev_low_volt(-1.0),
    m_dev_sync_freq(-1.0)
{
    makeConnectedDevsList(dev);
}

string join(list<string> list, string split = "")             // вспомогательная функция для объединения
{                                                             // списка в одну строку;
    string out;

    if (!list.empty())
    {
        auto last = std::prev(list.end());
        for (auto iter = list.begin(); iter != last; iter++)
            out.append(*iter + split);
        out.append(*last);
    }

    return out;
}

const string DevInfo::toString() const
{
    string out;

    out.append("\n");
    out.append("Device name:       " + m_dev_name +                  "\n" +
               "Device type:       " + m_dev_type +                  "\n" +
               "Required power:    " + std::to_string(m_dev_watt) +  "\n");

    if (m_dev_type == "Analog")
        out.append("Operating voltage: from " + std::to_string(m_dev_low_volt) +
                                       " to " + std::to_string(m_dev_up_volt) + "\n");
    else if (m_dev_type == "Digital")
        out.append("Sync frequency:    " + std::to_string(m_dev_sync_freq) + "\n");

    out.append("Number of ports:   " + std::to_string(m_port_size) + "\n" +
               "Connected devices: " + join(m_connected_devs, ", "));

    out.append("\n");

    return out;
}

const string LogEntry::toString() const
{
    string out;

    out.append("\nLog entry No " + std::to_string(m_id) + "\n" +
                 "Circuit: " + m_circuit_name +          "\n" +
                 "Action:  ");

    switch (m_operation_code)
    {
        case ADD_DEV:
            out.append("adding device " + m_dev1_name + "\n" +
                       "Result:  ");
            switch (m_status_code)
            {
                case SUCCESS:
                    out.append("action completed successfully\n");
                    break;
                case ERROR_INCORRECT_PARAMETERS:
                    out.append("error - incorrect parameters of the device\n");
                    break;
                case ERROR_DEV_ALREADY_PRESENT:
                    out.append("error - the device is already present in the circuit\n");
                    break;
                default:
                    out = "\nInvalid log entry: unknown status code in ADD_DEV\n";
                    break;
            }
            break;
        case DELETE_DEV:
            out.append("deleting device " + m_dev1_name + "\n" +
                       "Result:  ");
            switch (m_status_code)
            {
                case SUCCESS:
                    out.append("action completed successfully\n");
                    break;
                case ERROR_NO_SUCH_DEV:
                    out.append("error - there is no such device in the circuit\n");
                    break;
                default:
                    out = "\nInvalid log entry: unknown status code in DELETE_DEV\n";
                    break;
            }
            break;
        case CONNECT_DEVS:
            out.append("connecting devices " + m_dev1_name + " and " + m_dev2_name + "\n" +
                       "Result:  ");
            switch (m_status_code)
            {
                case SUCCESS:
                    out.append("action completed successfully\n");
                    break;
                case ERROR_DEV1_IS_MISSING:
                    out.append("error - there is no device " + m_dev1_name + " in the circuit\n");
                    break;
                case ERROR_DEV2_IS_MISSING:
                    out.append("error - there is no device " + m_dev2_name + " in the circuit\n");
                    break;
                case ERROR_DEVS_NOT_COMPATIBLE:
                    out.append("error - devices are not compatible\n");
                    break;
                case ERROR_DEV1_NO_FREE_PORTS:
                    out.append("error - " + m_dev1_name + " has no free ports\n");
                    break;
                case ERROR_DEV2_NO_FREE_PORTS:
                    out.append("error - " + m_dev1_name + " has no free ports\n");
                    break;
                case ERROR_DEVS_ALREADY_CONNECTED:
                    out.append("error - devices are already connected\n");
                    break;
                default:
                    out = "\nInvalid log entry: unknown status code in CONNECT_DEVS\n";
                    break;
            }
            break;
        case DISCONNECT_DEVS:
            out.append("disconnecting devices " + m_dev1_name + " and " + m_dev2_name + "\n" +
                       "Result:  ");
            switch (m_operation_code)
            {
                case SUCCESS:
                    out.append("action completed successfully\n");
                    break;
                case ERROR_DEV1_IS_MISSING:
                    out.append("error - there is no device " + m_dev1_name + " in the circuit\n");
                    break;
                case ERROR_DEV2_IS_MISSING:
                    out.append("error - there is no device " + m_dev2_name + " in the circuit\n");
                    break;
                case ERROR_DEVS_NOT_CONNECTED:
                    out.append("error - devices are not connected\n");
                    break;
                default:
                    out = "\nInvalid log entry: unknown status code in DISCONNECT_DEVS\n";
                    break;
            }
            break;
        case GET_DEV_INFO:
            out.append("getting information about device " + m_dev1_name + "\n" +
                       "Result:  ");
            switch (m_status_code)
            {
                case SUCCESS:
                    out.append("action completed successfully\n");
                    break;
                case ERROR_NO_SUCH_DEV:
                    out.append("error - there is no such device in the circuit\n");
                    break;
                default:
                    out = "\nInvalid log entry: unknown status code in GET_DEV_INFO\n";
                    break;
            }
            break;
        case CREATE_CIRCUIT:
            out.append("creating circuit " + m_circuit_name + "\n");
            break;
        default:
            out = "\nInvalid log entry: unknown operation code\n";
            break;
    };

    return out;
}