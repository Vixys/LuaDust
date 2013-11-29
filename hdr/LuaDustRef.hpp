#ifndef LUA_DUST_REF_HPP
#define LUA_DUST_REF_HPP

#include <string>

class LuaDustRef
{
	public:
		virtual ~LuaDustRef() { }

		virtual void updateRef() = 0;
		virtual void pushRef() = 0;

		virtual const std::string &getName() const = 0;
		virtual const void *getRefPtr() const = 0;
		virtual std::string getStringValue() const = 0;

	private:

};

#endif // LUA_DUST_REF_HPP