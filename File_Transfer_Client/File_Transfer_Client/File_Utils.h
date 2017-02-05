#pragma once
#include <fstream>
#include <iostream>

class File_Utils
{
public:
	File_Utils();
	~File_Utils();

	const char* read_file(const char* file_name);
	const char* write_file(const char* file_name, const char* data);
};

