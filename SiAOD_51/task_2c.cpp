#include <iostream>

int main() {
    unsigned short int repeat_count, number, n = 7;
    unsigned char result[9];
    for(int i = 0; i <= n; i++) {
        result[i] = 0;
    }
    std::cout << "Введите количество чисел для сортировки (не более 64): ";
    std::cin >> repeat_count;
    for(int i = 1; i <= repeat_count; i++) {
        std::cout << i << ". Введите значение от 0 до 63: ";
        std::cin >> number;
        if (number > 63) {
            std::cout << "Неправильный ввод. Введите значение от 0 до 7: ";
            std::cin >> number;
        }
        result[number / 8] |= (1 << (n - number % 8));
    }
    std::cout << "Получившийся бинарный массив: ";
    for(int i = 0; i <= n; i++) {
        std::cout << std::bitset<8> (result[i]) << " ";
    }
    std::cout << std::endl << "Получившийся отсортированный массив чисел: ";
    for(int i = 0; i <= n; i++) {
        unsigned mask = (1 << n);
        for(int j = n; j >= 0; j--) {
            if((result[i] & mask) != 0) {
                std::cout << ((n - j) + 8 * i) << " ";
            }
            mask = mask >> 1;
        }
    }
}

