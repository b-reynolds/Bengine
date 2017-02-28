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
	severity_ = kSeverityDefault;
	log_mode_ = kLogModeDefault;
	log_file_name_ = kLogFileDefault;
	log_directory_ = kLogDirectoryDefault;
}

/**
* \brief Returns a reference to the singleton instance of the Logger class
*/
BG::Logger& BG::Logger::instance()
{
	static Logger instance;
	return instance;
}

/**
* \brief Set the current log mode
* \param log_mode log mode
*/
void BG::Logger::set_log_mode(const LogMode& log_mode)
{
	this->log_mode_ = log_mode;
}

/**
 * \brief Set the current severity level
 * \param severity severity level
 */
void BG::Logger::set_severity(const Severity& severity)
{
	this->severity_ = severity;
}

/**
* \brief Set the name of the log file
* \param file_name name of the log file
*/
void BG::Logger::set_log_file(const std::string& file_name)
{
	log_file_name_ = file_name;
}

/**
* \brief Set the directory log files are created in
* \param directory directory
*/
void BG::Logger::set_log_directory(const std::string& directory)
{
	log_directory_ = directory;
}

/**
* \brief Output a message to the console and or log file depending on Severity and LogMode levels
* \param severity severity level of the log
* \param message message to log
*/
void BG::Logger::log(const Severity& severity, const std::string& message)
{
	// If the severity level of the log is less than our set severity level discontinue
	if (this->severity_ < severity)
	{
		return;
	}

	// Format the destination path and output message
	std::string output = date_time("[%d-%m-%Y %H:%M:%S] ") + severity_to_string(severity) + ": " + message;
	std::string destination = log_directory_ + "/" + log_file_name_;
	
	if(CreateDirectory(log_directory_.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		std::fstream file(log_directory_ + "/" + log_file_name_, std::ios::out | std::ios::app);
		switch (log_mode_)
		{
			case kConsole:
				std::cout << output << std::endl;
				break;
			case kFile:
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
std::string BG::Logger::severity_to_string(const Severity& severity) const
{
	switch(severity)
	{
		case ERROR:
			return "Error";
		case kDebug:
			return "Debug";
		default:
			return "Info";
	}
}

/**
 * \brief Returns a string containing the system's locale time in the specified format
 * \param format desired format of the time stamp (e.g. D-M-Y H:M:S)
 */
std::string BG::Logger::date_time(const std::string &format) const
{
	time_t t = time(nullptr);
	tm time = *localtime(&t);
	std::stringstream stringStream;
	stringStream << std::put_time(&time, format.c_str());
	return stringStream.str();
}