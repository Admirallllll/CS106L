template <typename T>
MyClass<T>::MyClass() : value(T()) {}

template <typename T>
MyClass<T>::MyClass(T value) {
    validateValue(value);
    this->value = value;
}

template <typename T>
T MyClass<T>::getValue() const {
    return value;
}

template <typename T>
void MyClass<T>::setValue(T value) {
    validateValue(value);
    this->value = value;
}

template <typename T>
void MyClass<T>::validateValue(T value) {}