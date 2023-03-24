#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const char FILENAME[] = "crossword.crwds";

struct Question
{
	bool vertical;
	size_t x;
	size_t y;
	std::string question;
};

class Crossword
{
public:
	size_t height;
	size_t width;

	char **correct;
	char **current;

	std::vector<Question> questions;

	Crossword(std::ifstream &file)
	{
		file >> height >> width;

		correct = new char *[height];
		current = new char *[height];

		for (size_t i = 0; i < height; i++)
		{
			correct[i] = new char[width];
			current[i] = new char[width];
		}

		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				file >> correct[i][j];
				if (correct[i][j] == '#')
				{
					current[i][j] = '#';
				}
				else
				{
					current[i][j] = '_';
				}
			}
		}

		size_t questionCount;

		file >> questionCount;

		for (size_t i = 0; i < questionCount; i++)
		{
			Question q;

			char verticalChar;

			file >> q.x >> q.y >> verticalChar;

			q.vertical = verticalChar == 'v';

			file.ignore();

			std::getline(file, q.question);

			questions.push_back(q);
		}

		file.close();
	}

	void print()
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				std::cout << current[i][j] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;

		for (auto &q : questions)
		{
			std::cout << q.x + 1 << " " << q.y + 1 << " " << (q.vertical ? "v" : "h") << " " << q.question << std::endl;
		}
	}

	~Crossword()
	{
		for (size_t i = 0; i < height; i++)
		{
			delete[] correct[i];
		}

		delete[] correct;
	}
};

int main()
{
	// READING THE FILE
	std::ifstream file(FILENAME);

	auto c = Crossword(file);

	bool game = true;

	while (game)
	{
		c.print();

		char what;

		std::cin >> what;

		if (what == 'a')
		{
			size_t x, y;
			std::cin >> x >> y;

			x--;
			y--;

			char letter;
			std::cin >> letter;

			bool vertical = letter == 'v';

			std::string word;

			std::cin >> word;

			if (vertical)
			{
				for (size_t i = 0; i < word.length(); i++)
				{
					if(x >= c.width)
						break;

					if(y + i >= c.height)
						break;

					if(c.current[y + i][x] == '#')
						break;

					c.current[y + i][x] = word[i];
				}
			}
			else
			{
				for (size_t i = 0; i < word.length(); i++)
				{
					if(x + i >= c.width)
						break;

					if(y >= c.height)
						break;

					if(c.current[y][x + i] == '#')
						break;

					c.current[y][x + i] = word[i];
				}
			}
		}
		else if(what == 'c') {
			for(auto queston : c.questions) {
				std::string word;
				std::string correctWord;

				if(queston.vertical) {
					for(int i = 0;; i++) {
						if(queston.x >= c.width)
							break;

						if(queston.y + i >= c.height)
							break;

						if(c.current[queston.y + i][queston.x] == '#')
							break;

						word += c.current[queston.y + i][queston.x];
						correctWord += c.correct[queston.y + i][queston.x];
					}
				} else {
					for(int i = 0;; i++) {
						if(queston.x + i >= c.width)
							break;

						if(queston.y >= c.height)
							break;

						if(c.current[queston.y][queston.x + i] == '#')
							break;

						word += c.current[queston.y][queston.x + i];
						correctWord += c.correct[queston.y][queston.x + i];
					}
				}

				std::cout << queston.question << std::endl;
				std::cout << "yuor answer: " << word << std::endl;
				std::cout << "the answer is " << (correctWord == word ? "correct" : "wrong") << std::endl << std::endl;
			}
		}
		else if (what == 'q')
		{
			game = false;
		}
	}

	return 0;
}
