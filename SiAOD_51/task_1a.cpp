#include <iostream>

int main() {
    unsigned short int repeat_count, code;
    unsigned char x;
    std::cout << "Введите количество чисел для обнуления 5-го бита: ";
    std::cin >> repeat_count;
    for(int i = 1; i <= repeat_count; i++) {
        std::cout << i << ". Введите значение от 0 до 255: ";
        std::cin >> code;
        if (code > 255) {
            std::cout << "Неправильный ввод. Введите значение от 0 до 255: ";
            std::cin >> code;
        }
        x = (unsigned char) code;
        unsigned char mask = 1;
        x = x & (~(mask << 4));
        std::cout << "Число с 0 в 5-ом бите: " << (int) x << std::endl;
    }
}

