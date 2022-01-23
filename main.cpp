#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Invalid count argument: " << argc << " != 3";
        return 5;
    }


    const std::string mode(argv[1]);
    if (mode == "-e")
    {
        std::cout << "Input some text:\n";
        std::string line;
        std::getline(std::cin, line);


        std::cout << "Password:";
        unsigned long long password;
        std::cin >> password;
        srand(password);


        for (auto& letter : line)
        {
            letter ^= static_cast<char>(rand() % 126);
            letter  = (letter << 2) | (letter >> 6);
        }


        std::ofstream file(argv[2]);
        if (!file.is_open())
        {
            std::cerr << "Not found " << argv[2];
            return 5;
        }
        file << line;
        file.close();
    }
    else if (mode == "-d")
    {
        std::ifstream file(argv[2]);
        if (!file.is_open())
        {
            std::cerr << "Not found " << argv[2];
            return 5;
        }
        std::string line;
        file >> line;


        std::cout << "Password:";
        unsigned long long password;
        std::cin >> password;
        srand(password);


        for(auto& letter : line)
        {
            letter  = (letter >> 2 & 0b0011'1111) | (letter << 6);
            letter ^= static_cast<char>(rand() % 126);
        }


        std::cout << "Decryption text:\n" << line << '\n';
    }
    else
    {
        std::cerr << "Invalid flag:" << mode;
        return 5;
    }


    return 0;
}

