#include <fstream>
#include <iostream>
#include <vector>
#include "types/Value/Value.hpp"
#include "modules/parse/parse.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Invalid argument count" << std::endl;
        return -1;
    }

    std::ifstream source_file;
    source_file.open(argv[1], std::ios::in);

    if (!source_file.is_open()) {
        std::cerr << "Error: Failed to open file " << argv[1] << std::endl;
        return -1;
    }

    ParseContext::ValueList value_list = parse(source_file);
    source_file.close();

    std::cout << "---" << std::endl;
    for (std::size_t i = 0; i < value_list.size(); i++) {
        std::cout << "[" << i << "] " << value_list[i]->to_string() << std::endl;
    };
}
