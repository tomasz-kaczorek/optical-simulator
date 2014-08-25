#include "orders.h"

Orders::Orders() :
    m_orders(0)
{
}

Orders::Orders(Order order) :
    m_orders(1 << order)
{
}

Orders::Orders(const Orders & orders) :
    m_orders(orders.m_orders)
{
}

int Orders::size()
{
    return 6;
}

void Orders::set(Orders::Order order, bool state)
{
    m_orders = (m_orders & ~(1<<order)) | (state<<order);
}

void Orders::operator=(Orders const & orders)
{
    m_orders = orders.m_orders;
}

bool Orders::operator[](int index) const
{
    return m_orders & (1 << index);
}

Orders Orders::operator|(Orders::Order order) const
{
    return Orders(m_orders | (1 << order));
}

Orders Orders::operator|(Orders orders) const
{
    return Orders(m_orders | orders.m_orders);
}

void Orders::operator|=(Orders orders)
{
    m_orders |= orders.m_orders;
}

Orders Orders::operator&(Orders orders)
{
    return Orders(m_orders & orders.m_orders);
}

void Orders::operator&=(Orders orders)
{
    m_orders &= orders.m_orders;
}

bool Orders::operator==(Orders orders)
{
    return m_orders == orders.m_orders;
}

Orders::Orders(char orders)
{
    m_orders = orders;
}

Orders operator|(Orders::Order order1, Orders::Order order2)
{
    return Orders(order1) | Orders(order2);
}


Orders operator|(Orders::Order order, Orders orders)
{
    return Orders(order) | orders;
}
