#ifndef LUA_DUST_EXCEPTION_HPP
#define LUA_DUST_EXCEPTION_HPP

#include <exception>
#include <string>

class LuaDustException : public std::exception
{
	public:
		LuaDustException(const std::string &error);
		virtual ~LuaDustException() throw();

		virtual const char * what() const throw();

	private:
		std::string _message;

};

#endif // LUA_DUST_EXCEPTION_HPP