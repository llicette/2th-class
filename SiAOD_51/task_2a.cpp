#include <iostream>

int main() {
    unsigned short int repeat_count, number, n = 7;
    unsigned char result = 0;
    std::cout << "Введите количество чисел для сортировки (не более 8): ";
    std::cin >> repeat_count;
    for(int i = 1; i <= repeat_count; i++) {
        std::cout << i << ". Введите значение от 0 до 7: ";
        std::cin >> number;
        if (number > 7) {
            std::cout << "Неправильный ввод. Введите значение от 0 до 7: ";
            std::cin >> number;
        }
        result = result | (1 << (n - number));
    }
    std::cout << "Получившийся бинарный массив: " << std::bitset<8> (result) << std::endl;
    std::cout << "Получившийся отсортированный массив чисел: ";
    unsigned mask = (1 << n);
    for(int i = n; i >= 0; i--) {
        if((result & mask) != 0) {
            std::cout << (n - i) << " ";
        }
        mask = mask >> 1;
    }
}

