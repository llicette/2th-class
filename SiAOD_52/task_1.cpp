#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <fstream>
#include <string>
#include <unordered_map>
#include <limits>

const int N = 100;
const std::string VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
auto rng = std::default_random_engine {};

//генератор случайных номеров читательских билетов
void number_generator(std::array<int, 100>& library_card_numbers) {
    int number = 10000;
    for(int i = 0; i < N; i++) {
        number += rand() % (700) + 1;
        library_card_numbers.at(i) = number;
    }
    std::shuffle(library_card_numbers.begin(), library_card_numbers.end(), rng);
}

//генерация случайных строк
std::string string_generation() {
    unsigned short int string_size = rand() % (20) + 3;
    std::uniform_int_distribution<int> distribution(0,VALID_CHARS.size() - 1);
    std::string your_random_string;
    std::generate_n(std::back_inserter(your_random_string), string_size, [&]()
    {
        return VALID_CHARS[distribution(rng)];
    });
    return your_random_string;
}

//генерация случайного адреса
std::string address_generation() {
    unsigned short int string_size = rand() % (20) + 3;
    unsigned short int number_house = rand() % (400) + 1;
    std::uniform_int_distribution<int> distribution(0,VALID_CHARS.size() - 1);
    std::string your_random_string = "ул.";
    std::generate_n(std::back_inserter(your_random_string), string_size, [&]()
    {
        return VALID_CHARS[distribution(rng)];
    });
    your_random_string += ", д." + std::to_string(number_house);
    return your_random_string;
}

//запись в файл library_subscription.txt
void input_to_file(std::ofstream& library_subscription, std::array<int, 100>& library_card_numbers) {
    for(int i = 0; i < N; i++) {
        std::string last_name = string_generation();
        std::string first_name = string_generation();
        std::string middle_name = string_generation();
        std::string address = address_generation();
        library_subscription << "Номер читательского билета: " << library_card_numbers.at(i)
            << ", ФИО: " << last_name << " " << first_name << " " << middle_name
            << ", Адрес: " << address << '\n';
    }
}

//перенос ключей в двоичный файл
void serialization(std::ofstream& library_card_numbers_binary, std::unordered_map<int, std::streampos> &index_table) {
    std::ifstream library_subscription("/Users/licette./CLionProjects/univer/SiAOD_52/library_subscription.txt");
    std::string record;
    int card_number;

    while (std::getline(library_subscription, record)) {
        std::string tmp = record.substr(52, 5);
        card_number = stoi(tmp);
        library_card_numbers_binary.write(reinterpret_cast<const char *>(&card_number), sizeof(card_number));

        std::streampos pos = library_card_numbers_binary.tellp();
        index_table[card_number] = pos;
    }
}

//линейный поиск записи
void search_record() {
    int key;
    bool flag = false;
    std::cout << "Введите 5-значный номер читательского билета для получения полной информации о человеке: ";
    std::cin >> key;
    while(key < 10000 || key > 99999) {
        std::cout << "Некорректный ввод. Введите 5-значный номер читательского билета для получения полной информации о человеке: " ;
        std::cin >> key;
    }

    std::ifstream library_card_numbers_binary("/Users/licette./CLionProjects/univer/SiAOD_52/library_card_numbers.bin");
    std::ifstream library_subscription("/Users/licette./CLionProjects/univer/SiAOD_52/library_subscription.txt");

    std::string record;
    int number;

    auto start = std::chrono::high_resolution_clock::now();
    while(library_card_numbers_binary.read(reinterpret_cast<char *>(&number), sizeof(int))) {
        if(number == key) {
            while (getline(library_subscription, record)) {
                if(record.find(std::to_string(number))!=std::string::npos){
                    std::cout << record << std::endl;
                }
            }
            flag = true;
            break;
        }
    }

    if(!flag) {
        std::cout << "Такой записи не существует";
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Время поиска: " << duration.count() << " sec.";

    library_card_numbers_binary.close();
    library_subscription.close();
}

//бинарный однородный поиск
void search_record_from_index(std::streampos pos) {
    std::ifstream library_subscription("/Users/licette./CLionProjects/univer/SiAOD_52/library_subscription.txt");

    static const int max_line = std::numeric_limits<std::streamsize>::max();

    for(int i = 0; i < pos / 4 - 1; i++) {
        library_subscription.ignore(max_line, '\n');
    }
    std::cout << pos;

    std::string record;
    std::getline(library_subscription, record);
    std::cout << record << std::endl;

    library_subscription.close();
}

void search_index(const std::unordered_map<int, std::streampos> &index_table) {
    int key;
    bool flag = false;
    std::cout << "Введите 5-значный номер читательского билета для получения полной информации о человеке: ";
    std::cin >> key;
    while(key < 10000 || key > 99999) {
        std::cout << "Некорректный ввод. Введите 5-значный номер читательского билета для получения полной информации о человеке: " ;
        std::cin >> key;
    }

    auto start = std::chrono::high_resolution_clock::now();

    auto iterator = index_table.find(key);
    if(iterator != index_table.end()) {
        search_record_from_index(iterator->second);
    } else {
        std::cout << "Такой записи не существует" << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Время поиска: " << duration.count() << " sec.";
}

int main() {
    std::array<int, N> library_card_numbers;
    library_card_numbers.fill(0);
    number_generator(library_card_numbers);

    std::ofstream library_subscription("/Users/licette./CLionProjects/univer/SiAOD_52/library_subscription.txt");
    input_to_file(library_subscription, library_card_numbers);
    library_subscription.close();

    std::ofstream library_card_numbers_binary("/Users/licette./CLionProjects/univer/SiAOD_52/library_card_numbers.bin");
    std::unordered_map<int, std::streampos> index_table;
    serialization(library_card_numbers_binary, index_table);
    library_card_numbers_binary.close();

    search_record();
    //search_index(index_table);
}