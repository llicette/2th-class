#include <iostream>

int main() {
    unsigned short int repeat_count, number, n = 63;
    unsigned long long result = 0;
    std::cout << "Введите количество чисел для сортировки (не более 64): ";
    std::cin >> repeat_count;
    for(int i = 1; i <= repeat_count; i++) {
        std::cout << i << ". Введите значение от 0 до 63: ";
        std::cin >> number;
        if (number > 63) {
            std::cout << "Неправильный ввод. Введите значение от 0 до 63: ";
            std::cin >> number;
        }
        result = result |  (1L << (n - number));
    }
    std::cout << "Получившийся бинарный массив: " << std::bitset<64> (result) << std::endl;
    std::cout << "Получившийся отсортированный массив чисел: ";
    unsigned long long mask = (1L << n);
    for(int i = n; i >= 0; i--) {
        if((result & mask) != 0) {
            std::cout << (n - i) << " ";
        }
        mask = mask >> 1;
    }
}

