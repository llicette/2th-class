#include <fstream>
#include <iostream>
#include <vector>

int main() {
    const int BIT_SIZE = 1024 * 1024;
    const int SIZE = BIT_SIZE * 8;
    std::ifstream file("/Users/licette./CLionProjects/univer/SiAOD_51/file_3b.txt");
    std::vector<unsigned char> array(BIT_SIZE, 0);
    int number;

    if(!file) {
        std::cout << "Не удалось открыть файл" << std::endl;
        return 0;
    }

    std::cout << "Объём оперативной памяти, занимаемый битовым массивом: "
              << (array.size() * sizeof(unsigned char)) / 1000000.0 << " МБ." << std::endl;


    while(!file.eof()) {
        file >> number;
        if(number < SIZE) {
            array[number / 8] |= (1 << (number % 8));
        }
    }
    file.close();

    std::cout << "Объём оперативной памяти, занимаемый битовым массивом: "
              << (array.size() * sizeof(unsigned char)) / 1000000.0 << " МБ." << std::endl;


    std::ofstream result("/Users/licette./CLionProjects/univer/SiAOD_51/result_3b.txt");

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
}
