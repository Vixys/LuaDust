#include "LuaDustException.hpp"

namespace LuaDust
{
	LuaDustException::LuaDustException(const std::string &error)
	{
		this->_message = error;
	}

	LuaDustException::~LuaDustException() throw()
	{

	}

	const char * LuaDustException::what() const throw()
	{
		std::string msg = "LuaDustException: " + this->_message;

		return msg.c_str();
	}
} // End LuaDust namespace
