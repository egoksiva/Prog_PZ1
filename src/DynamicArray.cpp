#include "../include/DynamicArray.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

DynamicArray::DynamicArray(std::size_t size) : data_(new int[size]()), size_(size) {}
DynamicArray::~DynamicArray() {
    delete[] data_;
}

std::size_t DynamicArray::size() const {
    return size_;
}

void DynamicArray::print() const {
    std::cout << '[';
    for (std::size_t i = 0; i < size_; ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << data_[i];
    }
    std::cout << "]\n";
}

void DynamicArray::checkIndex(int index) const {
    if (index < 0 || static_cast<std::size_t>(index) >= size_) {
        throw std::out_of_range("DynamicArray: индекс выходит за границы массива");
    }
}

void DynamicArray::checkValue(int value) {
    if (value < MIN_VALUE || value > MAX_VALUE) {
        throw std::invalid_argument("DynamicArray: значение вне промежутка [-100; 100]");
    }
}

void DynamicArray::set(int index, int value) {
    checkIndex(index);
    checkValue(value);
    data_[index] = value;
}

int DynamicArray::get(int index) const {
    checkIndex(index);
    return data_[index];
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(new int[other.size_]), size_(other.size_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

void DynamicArray::push_back(int value) {
    checkValue(value);
    int* newData = new int[size_ + 1];
    std::copy(data_, data_ + size_, newData);
    newData[size_] = value;
    delete[] data_;
    data_ = newData;
    ++size_;
}

void DynamicArray::add(const DynamicArray& other) {
    const std::size_t common = std::min(size_, other.size_);
    for (std::size_t i = 0; i < common; ++i) {
        data_[i] += other.data_[i];
    }
}

void DynamicArray::sub(const DynamicArray& other) {
    const std::size_t common = std::min(size_, other.size_);
    for (std::size_t i = 0; i < common; ++i) {
        data_[i] -= other.data_[i];
    }
}
