#include "../include/DynamicArray.h"
#include <algorithm>
#include <iostream>

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

bool DynamicArray::indexInRange(int index) const {
    return index >= 0 && static_cast<std::size_t>(index) < size_;
}

bool DynamicArray::valueInRange(int value) {
    return value >= MIN_VALUE && value <= MAX_VALUE;
}

bool DynamicArray::set(int index, int value) {
    if (!indexInRange(index) || !valueInRange(value)) {
        return false;
    }
    data_[index] = value;
    return true;
}

bool DynamicArray::get(int index, int& value) const {
    if (!indexInRange(index)) {
        return false;
    }
    value = data_[index];
    return true;
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(new int[other.size_]), size_(other.size_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

bool DynamicArray::push_back(int value) {
    if (!valueInRange(value)) {
        return false;
    }
    int* newData = new int[size_ + 1];
    std::copy(data_, data_ + size_, newData);
    newData[size_] = value;
    delete[] data_;
    data_ = newData;
    ++size_;
    return true;
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
