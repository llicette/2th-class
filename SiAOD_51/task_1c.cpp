#include <iostream>
#include <bitset>

int main() {
    unsigned int x = 789263;
    const int n = sizeof(int) * 8;
    unsigned mask = (1 << (n - 1));
    std::cout << "Входное число: " << x << std::endl;
    std::cout << "Начальный вид маски: " << std::bitset<n> (mask) << std::endl;
    std::cout << "Результат: ";
    for(int i = 1; i <= n; i++) {
        std::cout << ((x & mask) >> (n - i));
        mask = mask >> 1;
    }
    std::cout << std::endl;
}

