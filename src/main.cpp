#include <initializer_list>
#include <iostream>
#include "../include/DynamicArray.h"
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace {

void fill(DynamicArray& arr, std::initializer_list<int> values) {
    int index = 0;
    for (int value : values) {
        arr.set(index++, value);
    }
}

void show(const char* name, const DynamicArray& arr) {
    std::cout << name << " (размер " << arr.size() << "): ";
    arr.print();
}

void report(const char* action, bool ok) {
    std::cout << "  " << action << " -> " << (ok ? "выполнено" : "отклонено проверкой") << '\n';
}

}  // namespace

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "=== Задание 1: конструктор, print, set, get ===\n";
    DynamicArray a(5);
    show("a после конструктора", a);
    fill(a, {10, 20, 30, 40, 50});
    show("a после set", a);

    int value = 0;
    report("get(2, value)", a.get(2, value));
    std::cout << "  value = " << value << '\n';
    report("set(5, 1)   индекс вне границ массива", a.set(5, 1));
    report("set(1, 101) значение вне диапазона", a.set(1, 101));

    std::cout << "\n=== Задание 2: конструктор копирования ===\n";
    DynamicArray b(a);
    b.set(0, 1);
    show("a", a);
    show("b (копия a, b[0] = 1)", b);

    std::cout << "\n=== Задание 3: добавление в конец ===\n";
    report("push_back(60)", a.push_back(60));
    report("push_back(101)", a.push_back(101));
    show("a", a);

    std::cout << "\n=== Задание 4: сложение и вычитание ===\n";
    DynamicArray x(3);
    DynamicArray y(3);
    fill(x, {1, 2, 3});
    fill(y, {10, 20, 30});
    show("x", x);
    show("y", y);
    x.add(y);
    show("x.add(y)", x);
    x.sub(y);
    show("x.sub(y)", x);

    DynamicArray shorter(2);
    fill(shorter, {5, 5});
    x.add(shorter);
    show("x.add(shorter), недостающий элемент считается нулём", x);

    return 0;
}
