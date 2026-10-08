#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <cstddef>

class DynamicArray {
public:
    explicit DynamicArray(std::size_t size);
    ~DynamicArray();
    std::size_t size() const;
    void print() const;
    void set(int index, int value);
    int get(int index) const;
    DynamicArray(const DynamicArray& other);
    void push_back(int value);
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);

private:
    static constexpr int MIN_VALUE = -100;
    static constexpr int MAX_VALUE = 100;
    void checkIndex(int index) const;
    static void checkValue(int value);
    int* data_;
    std::size_t size_;
};

#endif
