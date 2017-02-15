#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Windows.h"

/*
 * \brief Constructor
 * Assigns default values to class members
 */
BG::Logger::Logger()	
{
	severity = SEVERITY_DEFAULT;
	logMode = LOG_MODE_DEFAULT;
	logFileName = LOG_FILE_DEFAULT;
	logDirectory = LOG_DIRECTORY_DEFAULT;
}

/**
* \brief Returns a reference to the singleton instance of the Logger class
*/
BG::Logger& BG::Logger::getInstance()
{
	static Logger instance;
	return instance;
}

/**
* \brief Set the current log mode
* \param logMode log mode
*/
void BG::Logger::setLogMode(const LogMode& logMode)
{
	this->logMode = logMode;
}

/**
 * \brief Set the current severity level
 * \param severity severity level
 */
void BG::Logger::setSeverity(const Severity& severity)
{
	this->severity = severity;
}

/**
* \brief Set the name of the log file
* \param fileName name of the log file
*/
void BG::Logger::setLogFile(const std::string& fileName)
{
	logFileName = fileName;
}

/**
* \brief Set the directory log files are created in
* \param directory directory
*/
void BG::Logger::setLogDirectory(const std::string& directory)
{
	logDirectory = directory;
}

/**
* \brief Output a message to the console and or log file depending on Severity and LogMode levels
* \param severity severity level of the log
* \param message message to log
*/
void BG::Logger::log(const Severity& severity, const std::string& message)
{
	// If the severity level of the log is less than our set severity level discontinue
	if (this->severity < severity)
	{
		return;
	}

	// Format the destination path and output message
	std::string output = getDateTime("[%d-%m-%Y %H:%M:%S] ") + toString(severity) + ": " + message;
	std::string destination = logDirectory + "/" + logFileName;
	
	if(CreateDirectory(logDirectory.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		std::fstream file(logDirectory + "/" + logFileName, std::ios::out | std::ios::app);
		switch (logMode)
		{
			case CONSOLE:
				std::cout << output << std::endl;
				break;
			case FILE:
				file << output << std::endl;
				break;
			default:
				std::cout << output << std::endl;
				file << output << std::endl;
				break;
		}
		file.close();
	}
}

/**
 * \brief Returns the string representation of a severity level
 * \param severity severity level
 */
std::string BG::Logger::toString(const Severity& severity) const
{
	switch(severity)
	{
		case ERROR:
			return "Error";
		case DEBUG:
			return "Debug";
		default:
			return "Info";
	}
}

/**
 * \brief Returns a string containing the system's locale time in the specified format
 * \param format desired format of the time stamp (e.g. D-M-Y H:M:S)
 */
std::string BG::Logger::getDateTime(const std::string &format) const
{
	time_t t = time(nullptr);
	tm time = *localtime(&t);
	std::stringstream stringStream;
	stringStream << std::put_time(&time, format.c_str());
	return stringStream.str();
}