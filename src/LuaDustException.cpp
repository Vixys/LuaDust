#include "LuaDustException.hpp"

LuaDustException::LuaDustException(const std::string &error)
{
	this->_message = error;
}

LuaDustException::~LuaDustException() throw()
{

}

const char * LuaDustException::what() const throw()
{
	return this->_message.c_str();
}
