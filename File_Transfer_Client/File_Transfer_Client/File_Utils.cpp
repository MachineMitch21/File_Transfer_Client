#include "File_Utils.h"


File_Utils::File_Utils()
{
}

const char* File_Utils::write_file(const char* file_name, const char* data) {
	std::ofstream fout(file_name, std::ofstream::binary);
	
	if (fout) {
		fout << data;
	}

	fout.close();

	return data;
}

const char* File_Utils::read_file(const char* file_name) {
	std::ifstream fin(file_name, std::ifstream::binary);
	char* buffer;

	if (fin.is_open()) {
		//Position file pointer at the end of the file to check the file length 
		//and dynamically allocate buffer size as file length then reset file pointer to beginning of file
		fin.seekg(0, fin.end);
		const int length = fin.tellg();
		fin.seekg(0, fin.beg);

		buffer = new char[length];

		fin.read(buffer, length);
		buffer[length] = '\0';
	}
	else {
		std::cout << "Unable to open " << file_name << "::ERROR CODE:: " << strerror(errno) << std::endl;
	}
	
	fin.close();
	return buffer;
}

File_Utils::~File_Utils()
{
}
