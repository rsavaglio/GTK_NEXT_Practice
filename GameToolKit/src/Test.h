#pragma once
#include <string>


namespace GTK {

	std::string HelloWorld()
	{
		static int number = 0;
		return std::to_string(number++);;
	}
}