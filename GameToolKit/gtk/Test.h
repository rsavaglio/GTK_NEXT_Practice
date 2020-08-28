#pragma once
#include <string>


namespace gtk {

	std::string HelloWorld()
	{
		static int number = 0;
		return std::to_string(number++);;
	}
}