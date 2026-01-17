#ifndef MYCLASS_H
#define MYCLASS_H

template <typename T>
class MyClass
{
public:
    MyClass();
    MyClass(T value);
    T getValue() const; // wont't modify the object
    void setValue(T value);

private:
    T value;
    void validateValue(T value);
};

#include "class.cpp"
#endif