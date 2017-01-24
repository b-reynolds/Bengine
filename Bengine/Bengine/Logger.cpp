#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <iostream>
#include <SDL_error.h>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger* Logger::instance = nullptr;

Logger::Logger()
{
	severity = DEBUG;
	logMode = ALL;
	logFile = "log.txt";
}

/**
 * Returns a string containing a timestamp in format [D-M-Y H-M-S]
 */
std::string Logger::getTimestamp()
{
	auto t = time(nullptr);
	auto time = *localtime(&t);
	std::stringstream stringStream;
	stringStream << std::put_time(&time, "%d-%m-%Y %H-%M-%S");
	return "[" + stringStream.str() + "]";
}

/**
* Returns a pointer to the singleton instance of the Logger class
*/
Logger* Logger::getInstance()
{
	if(instance == nullptr)
	{
		instance = new Logger();
	}
	return instance;
}

Logger::~Logger()
{
	delete instance;
}

/**
* Set the file path of the log file
* @param filePath The file path
*/
void Logger::setLogFile(const std::string& filePath)
{
	logFile = filePath;
}

/**
* Set the log mode
* @param logMode The log mode
*/
void Logger::setLogMode(const LogMode& logMode)
{
	this->logMode = logMode;
}

/**
 * Log a message to the console and or log file depending on Severity and LogMode level
 * @param severity The Severity level of the log
 * @param message The message to log
 */
void Logger::log(const Severity& severity, const std::string& message) const
{
	if (this->severity < severity) return;
	std::string messageType = "";
	switch(severity)
	{
		case ERROR:
			messageType = "ERROR";
			break;
		case INFO:
			messageType = "INFO";
			break;
		case DEBUG:
			messageType = "DEBUG";
			break;
	}
	std::string timeStamp = getTimestamp();
	std::string output = timeStamp + " " + messageType + ": " + message;
	switch(logMode)
	{
		case CONSOLE:
			std::cout << output << std::endl;
			break;
		case FILE:
			writeToFile(logFile, output);
			break;
		case ALL:
			std::cout << output << std::endl;
			writeToFile(logFile, output);
			break;
	}
}

/**
 * Append a string to a file
 * @param filePath The path to the file
 * @param message The message to be written
 */
void Logger::writeToFile(const std::string& filePath, const std::string& message)
{
	std::ofstream logFile(filePath.c_str(), std::ios_base::out | std::ios_base::app);
	logFile << message << std::endl;
}

/**
 * Outputs an error message to the console followed by SDL_GetError information
 * @param message The message to output
 */
void Logger::logSDLError(const std::string& message)
{
	std::cout << "Error: " << message << ": " << SDL_GetError() << std::endl;
}

/**
* Outputs an error message to the console
* @param message The message to output
*/
void Logger::logError(const std::string& message)
{
	std::cout << "Error: " << message << ": " << std::endl;
}
