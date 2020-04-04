//
// Created by aaron on 12/29/2017.
//

#ifndef IOBOT_UTIL_H
#define IOBOT_UTIL_H

#include <sstream>

namespace Util {
	///Trims whitespace from the left of a string.
	std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
	///Trims whitespace from the right of a string.
	std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
	///Trims whitespace from the ends of a string.
	std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");

	///Checks if the carry flag should be set from the result of a mathematical operation.
	bool checkCF(uint32_t res);
	///Checks if the sign flag should be set from the result of a mathematical operation.
	bool checkSF(uint16_t res);
	///Checks if the zero flag should be set from the result of a mathematical operation.
	bool checkZF(uint16_t res);

	/**
	 * Parses an int from a string, assuming it is trimmed. (At least at the beginning.)
	 *
	 * Works with hex (prefixed with 0x), binary (prefixed with 0b), and decimal (no prefix)
	 * @param str The string to parse, with no beginning whitespace.
	 * @return The parsed integer.
	 */
	int parseNumber(std::string& str);
}

#endif //IOBOT_UTIL_H
