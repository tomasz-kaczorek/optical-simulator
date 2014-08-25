#ifndef ORDERS_H
#define ORDERS_H

class Orders
{
public:
    enum Order : char
    {
        SecondNegative,
        FirstNegative,
        Zero,
        FirstPositive,
        SecondPositive,
        Max
    };
    Orders();
    Orders(Order order);
    Orders(Orders const & orders);
    int size();
    void set(Order order, bool state);
    void operator=(Orders const & orders);
    bool operator[](int index) const;
    Orders operator|(Order order) const;
    Orders operator|(Orders orders) const;
    void operator|=(Orders orders);
    Orders operator&(Orders orders);
    void operator&=(Orders orders);
    bool operator==(Orders orders);
private:
    Orders(char orders);
    template<typename T> operator T () const;
    char m_orders;
};

Orders operator|(Orders::Order order1, Orders::Order order2);
Orders operator|(Orders::Order order, Orders orders);

#endif // ORDERS_H
