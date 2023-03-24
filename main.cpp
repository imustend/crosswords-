#include <iostream>
#include <fstream>
#include <vector>

const char FILENAME[] = "crossword.crwds";
std::ifstream file(FILENAME);




int main()
{
    // READING THE FILE
    file.seekg(0, std::ios_base::end);
    const unsigned int file_length = file.tellg();
    file.seekg(0);
    std::vector<char> file_data(file_length);
    file.read(&file_data[0], file_length);

    for(auto item: file_data) {
        if(item == '\n') {
            std::cout << std::endl << "-------------------" << std::endl;
            continue;
        }
        std::cout << item;
    }

	return 0;
}
