#pragma once
#include <fstream>

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
		enum Severity { kError, kInfo, kDebug };

		/* Enumeration of log modes */
		enum LogMode { kConsole, kFile, kAll };

		/* Holds the currently set log mode */
		LogMode log_mode_;

		/* Holds the currently set severity level */
		Severity severity_;

		/* Returns a reference to the singleton instance of the Logger class */
		static Logger& instance();

		/* Set the current log mode */
		void set_log_mode(const LogMode &log_mode);

		/* Set the current severity level */
		void set_severity(const Severity &severity);

		/* Set the name of the log file */
		void set_log_file(const std::string &file_name);

		/* Set the directory log files are created in */
		void set_log_directory(const std::string &directory);

		/* Output a message to the console and or log file depending on Severity and LogMode levels */
		void log(const Severity &severity, const std::string &message);

	private:

		/* Default file name of the log file */
		const std::string kLogFileDefault = "log.txt";
		
		/* Default directory log files are created in */
		const std::string kLogDirectoryDefault = "Logs";

		/* Default log mode */
		const LogMode kLogModeDefault = kAll;

		/* Default severity level */
		const Severity kSeverityDefault = kDebug;

		/* File name of the log file */
		std::string log_file_name_;

		/* Directory log files are created in */
		std::string log_directory_;

		/* Constructor */
		Logger();
		
		/* Returns a string representation of the severity level */
		std::string severity_to_string(const Severity &severity) const;
		
		/* Returns a time stamp in the specified format */
		std::string date_time(const std::string &format) const;

	};
}
