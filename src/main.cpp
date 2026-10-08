#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include "../include/DynamicArray.h"
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace {

void demoNumeric() {
    std::cout << "=== Числовой тип: DynamicArray<int> ===\n";

    DynamicArray<int> a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);
    std::cout << "a = " << a << '\n';

    try {
        a.set(0, 101);
    } catch (const std::invalid_argument& e) {
        std::cout << "set(0, 101): выявлено std::invalid_argument: " << e.what() << '\n';
    }

    a.push_back(40);
    std::cout << "push_back(40): a = " << a << '\n';

    DynamicArray<int> b(a);
    b.set(0, 1);
    std::cout << "b (копия a, b[0] = 1) = " << b << '\n';
    b.add(a);
    std::cout << "b.add(a) = " << b << '\n';
    b.sub(a);
    std::cout << "b.sub(a) = " << b << '\n';

    DynamicArray<int> p(2);
    DynamicArray<int> q(2);
    q.set(0, 3);
    q.set(1, 4);
    std::cout << "p = " << p << ", q = " << q << '\n';
    std::cout << "p.distance(q) = " << p.distance(q) << '\n';
    try {
        p.distance(a);
    } catch (const std::invalid_argument& e) {
        std::cout << "p.distance(a): выявлено std::invalid_argument: " << e.what() << '\n';
    }
}

void demoNonNumeric() {
    std::cout << "\n=== Нечисловой тип: DynamicArray<std::string> ===\n";

    DynamicArray<std::string> s(2);
    s.set(0, "hello");
    s.set(1, "world");
    std::cout << "s = " << s << '\n';

    s.push_back("!");
    std::cout << "push_back(\"!\"): s = " << s << '\n';

    DynamicArray<std::string> t(s);
    t.set(0, "bye");
    std::cout << "t (копия s, t[0] = \"bye\") = " << t << '\n';
    std::cout << "s = " << s << '\n';

    try {
        s.distance(t);
    } catch (const std::bad_typeid& e) {
        std::cout << "s.distance(t): выявлено std::bad_typeid: " << e.what() << '\n';
    }
}

}  // namespace

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    demoNumeric();
    demoNonNumeric();

    return 0;
}
