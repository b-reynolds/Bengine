#pragma once
#include <string>

class Logger
{

private:

	static Logger *instance;
	Logger();

	static std::string getTimestamp();
	static void writeToFile(const std::string &filePath, const std::string &message);

public:

	static Logger* getInstance();
	~Logger();
	
	/**
	 * Enumeration of logging levels
	 */	
	enum Severity { ERROR, INFO, DEBUG };

	/**
	 * Enumeration of logging output mediums
	 */
	enum LogMode { CONSOLE, FILE, ALL };

	std::string logFile;

	Severity severity;
	LogMode logMode;

	void setLogFile(const std::string &filePath);
	void setLogMode(const LogMode &logMode);

	void log(const Severity &severity, const std::string &message) const;

	
	static void logSDLError(const std::string &message);
	static void logError(const std::string &message);

};

