#pragma once
#include <string>

class Logger
{

public:

	static void logSDLError(const std::string &message);
	static void logError(const std::string &message);

};

