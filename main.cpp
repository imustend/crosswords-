#include <iostream>
#include <fstream>
#include <vector>

const char FILENAME[] = "crossword.crwds";

class Crossword {
	public:
		size_t height;
		size_t width;
		std::vector<std::vector<char>> solved;
		
		Crossword(std::vector<char> file) {
			height = file[0] - '0';
			width = file[1] - '0';
			solved.resize(width);
			for (auto item: solved)
			{
				item.resize(height);
			}
			std::cout << std::endl << height << width << std::endl;
			char c = file[5];
			for (int i = 0; i < file.size(); ++i)
			{
				if(file[i] == '%') {
					i+=2;
					for (int j = 0; j < height; ++j)
					{
						for (int k = 0; k < width; ++k)
						{
							solved[j][k] = file[i];
							i++;
						}
					}
					
				}
			}

			
		}
};


int main()
{
    // READING THE FILE
	std::ifstream file(FILENAME);
    file.seekg(0, std::ios_base::end);
    const unsigned int file_length = file.tellg();
    file.seekg(0);
    std::vector<char> file_data(file_length);
    file.read(&file_data[0], file_length);
	// END
	
	auto c = Crossword(file_data);

	return 0;
}
