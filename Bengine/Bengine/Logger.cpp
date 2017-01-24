#include "Logger.h"
#include <iostream>
#include <SDL_error.h>

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
