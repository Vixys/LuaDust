#ifndef LUA_DUST_HPP
#define LUA_DUST_HPP

#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <list>

#include <lua.hpp>

#include "LuaDustRef.hpp"
#include "LuaDustException.hpp"

template <typename RetType, typename... Args> class LuaDustFunction;
template <typename Type> class LuaDustRefVar;

class LuaDust
{
	public:
		LuaDust();
		~LuaDust();

		template <typename RetType, typename... Args>
		LuaDustFunction<RetType, Args...> *addFunction(const std::string &name, RetType (*)(Args...));

		template <typename Type>
		LuaDustRef *addRefGlobal(const std::string &name, Type *value);

		bool addGlobal(const std::string &name, int value);
		bool addGlobal(const std::string &name, double value);
		bool addGlobal(const std::string &name, const std::string &value);

		bool doFile(const std::string &file);
		bool doString(const std::string &lua);

		lua_State *getState() const;

	protected:
		lua_State *_state;
		std::list<LuaDustRef *> _refs;
};

#include "LuaDustRefVar.hpp"
#include "LuaDustFunction.hpp"
#include "LuaDust.inl"

#endif // LUA_DUST_HPP