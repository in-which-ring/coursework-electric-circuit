#include "device.h"

Dev::~Dev()
{   // у всех присоединённых устройств обнуляем указатели на заданное устройство;
    for (size_t i = 0; i < m_dev_ports.size(); i++)
        if (m_dev_ports[i] && (m_dev_ports[i]->getPortNum(*this) >= 0))
            m_dev_ports[i]->m_dev_ports[m_dev_ports[i]->getPortNum(*this)] = nullptr;
}

int Dev::getPortNum() const
{
    for (size_t i = 0; i < m_dev_ports.size(); i++)
        if (!m_dev_ports[i])
            return i;

    return -1;
}

int Dev::getPortNum(const Dev& slave) const
{
    for (size_t i = 0; i < m_dev_ports.size(); i++)
        if (m_dev_ports[i] && m_dev_ports[i]->m_dev_name == slave.m_dev_name)
            return i;

    return -1;
}

int Dev::getPortNum(const string& slave_name) const
{
    for (size_t i = 0; i < m_dev_ports.size(); i++)
        if (m_dev_ports[i] && m_dev_ports[i]->m_dev_name == slave_name)
            return i;

    return -1;
}

const Dev* Dev::getPort(const size_t& port_num) const
{
    if (port_num >= m_dev_ports.size())
        return nullptr;

    return m_dev_ports[port_num];
}

int Dev::setPort(const size_t& port_num, Dev* slave)
{
    if (port_num >= m_dev_ports.size())
        return -1;

    m_dev_ports[port_num] = slave;

    return 0;
}

const Dev* Dev::operator[](const string& slave_name) const
{
    for (size_t i = 0; i < m_dev_ports.size(); i++)
        if (m_dev_ports[i] && m_dev_ports[i]->m_dev_name == slave_name)
            return m_dev_ports[i];

    return nullptr;
}