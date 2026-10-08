#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

template <typename T>
class DynamicArray {
public:
    explicit DynamicArray(std::size_t size) : data_(new T[size]()), size_(size) {}

    DynamicArray(const DynamicArray& other) : data_(new T[other.size_]), size_(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    ~DynamicArray() {
        delete[] data_;
    }

    std::size_t size() const {
        return size_;
    }

    void print() const {
        std::cout << *this << '\n';
    }

    void set(int index, const T& value) {
        checkIndex(index);
        checkValue(value);
        data_[index] = value;
    }

    T get(int index) const {
        checkIndex(index);
        return data_[index];
    }

    void push_back(const T& value) {
        checkValue(value);
        T* newData = new T[size_ + 1]();
        std::copy(data_, data_ + size_, newData);
        newData[size_] = value;
        delete[] data_;
        data_ = newData;
        ++size_;
    }

    void add(const DynamicArray& other) {
        const std::size_t common = std::min(size_, other.size_);
        for (std::size_t i = 0; i < common; ++i) {
            data_[i] += other.data_[i];
        }
    }

    void sub(const DynamicArray& other) {
        const std::size_t common = std::min(size_, other.size_);
        for (std::size_t i = 0; i < common; ++i) {
            data_[i] -= other.data_[i];
        }
    }

    double distance(const DynamicArray& other) const {
        if constexpr (std::is_arithmetic_v<T>) {
            if (size_ != other.size_) {
                throw std::invalid_argument("DynamicArray::distance: размеры массивов не совпадают");
            }
            double sum = 0;
            for (std::size_t i = 0; i < size_; ++i) {
                double diff = static_cast<double>(data_[i]) - other.data_[i];
                sum += diff * diff;
            }
            return std::sqrt(sum);
        } else {
            throw std::bad_typeid();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << '[';
        for (std::size_t i = 0; i < arr.size_; ++i) {
            if (i > 0) {
                os << ", ";
            }
            os << arr.data_[i];
        }
        return os << ']';
    }

private:
    static constexpr int MIN_VALUE = -100;
    static constexpr int MAX_VALUE = 100;

    T* data_;
    std::size_t size_;

    void checkIndex(int index) const {
        if (index < 0 || static_cast<std::size_t>(index) >= size_) {
            throw std::out_of_range("DynamicArray: индекс выходит за границы массива");
        }
    }

    static void checkValue(const T& value) {
        if constexpr (std::is_integral_v<T>) {
            if (value > MAX_VALUE) {
                throw std::invalid_argument("DynamicArray: значение вне промежутка [-100; 100]");
            }
            if constexpr (std::is_signed_v<T>) {
                if (value < MIN_VALUE) {
                    throw std::invalid_argument("DynamicArray: значение вне промежутка [-100; 100]");
                }
            }
        }
    }
};

#endif
