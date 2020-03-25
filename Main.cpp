#include "Steganography.hpp"

#include <iostream>
#include <cstring>

/**
arg[1] - either -e to encode, or -d to decode
	if argv[1] == -e
		argv[2] is either the relative or absolute path of the image
		argv[3] is the message
		argv[4] is the key
	if argv[2] == -d
		argv[2] is either the relative or absolute path of the image
		argv[3] is the key
**/
int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cout << "Enter arguments\n";
	}
	else
	{
		if (!strcmp(argv[1], "-e"))
		{
			LSB l(argv[2], argv[3], std::stoi(argv[4]));
			cv::Mat stego_image = l.embed();
			std::string destination;
			std::cout << "Enter destination: ";
			std::cin >> destination;
			cv::imwrite(destination, stego_image);
		}
		else if (!strcmp(argv[1], "-d"))
		{
			LSB l(argv[2], std::stoi(argv[3]));
			std::string message = l.extract();
			std::cout << message << "\n";
		}
	}
	return 0;
}