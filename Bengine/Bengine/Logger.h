#pragma once
#include <string>

namespace BG
{
	/**
	 * \brief Logging Class
	 * Handles the logging of messages messages of different severity levels to the console and or log files.
	 */ 
	class Logger
	{

	public:

		/* Enumeration of log severity levels */
		enum Severity { ERROR, INFO, DEBUG };

		/* Enumeration of log modes */
		enum LogMode { CONSOLE, FILE, ALL };

		/* Holds the currently set log mode */
		LogMode logMode;

		/* Holds the currently set severity level */
		Severity severity;

		/* Returns a reference to the singleton instance of the Logger class */
		static Logger& getInstance();

		/* Set the current log mode */
		void setLogMode(const LogMode &logMode);

		/* Set the current severity level */
		void setSeverity(const Severity &severity);

		/* Set the name of the log file */
		void setLogFile(const std::string &fileName);

		/* Set the directory log files are created in */
		void setLogDirectory(const std::string &directory);

		/* Output a message to the console and or log file depending on Severity and LogMode levels */
		void log(const Severity &severity, const std::string &message);

	private:

		/* Default file name of the log file */
		const std::string LOG_FILE_DEFAULT = "log.txt";
		
		/* Default directory log files are created in */
		const std::string LOG_DIRECTORY_DEFAULT = "Logs";

		/* Default log mode */
		const LogMode LOG_MODE_DEFAULT = ALL;

		/* Default severity level */
		const Severity SEVERITY_DEFAULT = INFO;

		/* File name of the log file */
		std::string logFile;

		/* Directory log files are created in */
		std::string logDirectory;

		/* Constructor */
		Logger();
		
		/* Returns a string representation of the severity level */
		std::string toString(const Severity &severity) const;
		
		/* Returns a time stamp in the specified format */
		std::string getDateTime(const std::string &format) const;

		/* Appends data to a file */
		void writeToFile(const std::string &filePath, const std::string &data);

	};
}
