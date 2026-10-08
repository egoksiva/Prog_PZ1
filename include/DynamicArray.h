#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <cstddef>

class DynamicArray {
public:
    explicit DynamicArray(std::size_t size);
    ~DynamicArray();
    std::size_t size() const;
    void print() const;
    bool set(int index, int value);
    bool get(int index, int& value) const;

    DynamicArray(const DynamicArray& other);

    bool push_back(int value);

    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);

private:
    static constexpr int MIN_VALUE = -100;
    static constexpr int MAX_VALUE = 100;

    bool indexInRange(int index) const;
    static bool valueInRange(int value);

    int* data_;
    std::size_t size_;
};

#endif
