#ifndef LUA_DUST_HPP
#define LUA_DUST_HPP

#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <list>

#include <lua.hpp>

#include "IVarRef.hpp"
#include "LuaDustException.hpp"

namespace LuaDust
{

	template <typename RetType, typename... Args> class Function;
	template <typename RetType, typename Class, typename... Args> class Method;
	template <typename Type> class VarRef;
	template <typename Type> class Array;

	class LuaDust
	{
		public:
			LuaDust();
			~LuaDust();

			template <typename RetType, typename... Args>
			Function<RetType, Args...> *addFunction(const std::string &name, RetType (*)(Args...));

			template <typename RetType, typename Class, typename... Args>
			Method<RetType, Class, Args...> *addFunction(const std::string &name, Class *ptr, RetType (Class::*)(Args...));

			template <typename Type>
			IVarRef *addRefGlobal(const std::string &name, Type *value);

			template <typename Type>
			Array<Type> *addArray(const std::string &name, Type *value);

			bool addGlobal(const std::string &name, bool value);
			bool addGlobal(const std::string &name, int value);
			bool addGlobal(const std::string &name, double value);
			bool addGlobal(const std::string &name, const char *value);
			bool addGlobal(const std::string &name, const std::string &value);

			bool doFile(const std::string &file);
			bool doString(const std::string &lua);

			lua_State *getState() const;

			const std::list<IVarRef *> &getReferences() const;

		protected:
			lua_State *_state;
			std::list<IVarRef *> _refs;
	};

} // End LuaDust namespace


#include "VarRef.hpp"
#include "Function.hpp"
#include "Method.hpp"
#include "Array.hpp"

namespace LuaDust
{
	#include "LuaDust.inl"
} // End LuaDust namespace

#endif // LUA_DUST_HPP