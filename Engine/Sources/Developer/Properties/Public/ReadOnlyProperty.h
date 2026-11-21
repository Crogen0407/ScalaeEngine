#pragma once

template <typename T, typename Owner>
class ReadOnlyProperty {
public:
    ReadOnlyProperty() = default;
    ReadOnlyProperty(const T& v) : value(v) {}

    operator const T& () const { return value; } 
    const T& Get() const { return value; }

private:
    friend Owner;
    ReadOnlyProperty& operator=(const T& v) { value = v; return *this; }
    T value;
};