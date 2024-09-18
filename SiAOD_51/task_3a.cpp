#include <fstream>
#include <iostream>
#include <vector>

int main() {
    const int SIZE = 10e7;
    const int BIT_SIZE = SIZE / 8;
    std::ifstream file("/Users/licette./CLionProjects/univer/SiAOD_51/file_3a.txt");
    std::vector<unsigned char> array(BIT_SIZE, 0);
    int number;

    if(!file) {
        std::cout << "Не удалось открыть файл" << std::endl;
        return 0;
    }

    auto start = std::chrono::high_resolution_clock::now();

    while(!file.eof()) {
        file >> number;
        array[number / 8] |= (1 << (number % 8));
    }
    file.close();

    std::ofstream result("/Users/licette./CLionProjects/univer/SiAOD_51/result_3a.txt");

    if(!result) {
        std::cout << "Не удалось открыть файл" << std::endl;
        return 0;
    }

    for(int i = 0; i < SIZE; i++) {
        if(array[i / 8] & (1 << (i % 8))) {
            result << i << '\n';
        }
    }
    result.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;

    std::cout << "Время сортировки: " << time.count() << " sec.";
}
