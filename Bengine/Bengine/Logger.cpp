#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <iostream>
#include <SDL_error.h>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

BG::Logger* BG::Logger::instance = nullptr;

BG::Logger::Logger()
{
	severity = INFO;
	logMode = ALL;
	logFile = "log.txt";
}

/**
 * @brief Returns a string containing the system's locale time in format D-M-Y H-M-S
 * @return std::string
 */
std::string BG::Logger::getTimestamp()
{
	auto t = time(nullptr);
	auto time = *localtime(&t);
	std::stringstream stringStream;
	stringStream << std::put_time(&time, "%d-%m-%Y %H:%M:%S");
	return stringStream.str();
}

/**
* @brief Returns a pointer a singleton instance of the Logger class
* @return Logger*
*/
BG::Logger* BG::Logger::getInstance()
{
	if(instance == nullptr)
	{
		instance = new Logger();
	}
	return instance;
}

/** Deconstructor
 * Delete dynamically allocated Logger instance 
 */
BG::Logger::~Logger()
{
	delete instance;
}


/**
* @brief Set the destination file path of the log file
* @param filePath The destination file path of the log file
* @return void
*/
void BG::Logger::setLogFile(const std::string& filePath)
{
	logFile = filePath;
}

/**
* @brief Set the log mode
* @param logMode The log mode
*/
void BG::Logger::setLogMode(const LogMode& logMode)
{
	this->logMode = logMode;
}

/**
 * @brief Log a message to the console and or log file depending on Severity and LogMode level
 * @param severity The Severity level of the log
 * @param message The message to log
 * @return void
 */
void BG::Logger::log(const Severity& severity, const std::string& message) const
{
	if (this->severity < severity) return;
	std::string messageType = "";
	switch(severity)
	{
		case ERROR:
			messageType = "ERROR";
			break;
		case DEBUG:
			messageType = "DEBUG";
			break;
		default:
			messageType = "INFO";
			break;
	}
	std::string timeStamp = getTimestamp();
	std::string output = "[" + timeStamp + "] " + messageType + ": " + message;
	switch(logMode)
	{
		case CONSOLE:
			std::cout << output << std::endl;
			break;
		case FILE:
			writeToFile(logFile, output);
			break;
		default:
			std::cout << output << std::endl;
			writeToFile(logFile, output);
			break;
	}
}

/**
 * @brief Append a string to a file
 * @param filePath The path to the file
 * @param message The message to be written
 * @return void
 */
void BG::Logger::writeToFile(const std::string& filePath, const std::string& message)
{
	std::ofstream logFile(filePath.c_str(), std::ios_base::out | std::ios_base::app);
	if (logFile.is_open())
	{
		logFile << message << std::endl;
	}
	logFile.close();
}