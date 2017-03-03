#pragma once
#include <vector>
#include <string>

namespace cs3d
{
	inline const std::vector<std::string> splitString(std::string str, std::string splitBy)
	{
		std::vector<std::string> tokens;
		std::string::size_type lastPos = str.find_first_not_of(splitBy, 0);
		std::string::size_type pos = str.find_first_of(splitBy, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			lastPos = str.find_first_not_of(splitBy, pos);
			pos = str.find_first_of(splitBy, lastPos);
		}

		return tokens;
	}

}