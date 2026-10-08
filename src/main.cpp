#include <cstddef>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include "../include/DynamicArray.h"
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    DynamicArray a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);
    std::cout << "a: ";
    a.print();

    std::cout << "\n=== std::out_of_range ===\n";
    try {
        a.get(5);
    } catch (const std::out_of_range& e) {
        std::cout << "get(5): выявлено std::out_of_range: " << e.what() << '\n';
    }

    std::cout << "\n=== std::invalid_argument ===\n";
    a.set(0, 100);
    std::cout << "set(0, 100) выполнен, граница включается: a = ";
    a.print();
    try {
        a.set(0, 101);
    } catch (const std::invalid_argument& e) {
        std::cout << "set(0, 101): выявлено std::invalid_argument: " << e.what() << '\n';
    }

    std::cout << "\n=== std::bad_alloc ===\n";
    try {
        // размер заведомо больше любой доступной памяти
        DynamicArray huge(std::numeric_limits<std::size_t>::max() / 4 / sizeof(int));
    } catch (const std::bad_alloc& e) {
        std::cout << "огромный массив: выявлено std::bad_alloc: " << e.what() << '\n';
    }

    std::cout << "\n=== Операции из части 1 по-прежнему работают ===\n";
    a.push_back(40);
    std::cout << "push_back(40): a = ";
    a.print();
    DynamicArray b(a);
    b.add(a);
    std::cout << "b - копия a, b.add(a): b = ";
    b.print();
    b.sub(a);
    std::cout << "b.sub(a): b = ";
    b.print();

    return 0;
}
