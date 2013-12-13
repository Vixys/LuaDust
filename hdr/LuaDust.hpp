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

	/**
	 * Represent a lua environment and its state.
	 */
	class LuaDust
	{
		public:
			/**
			 * Constructor
			 */
			LuaDust();
			/**
			 * Desctructor
			 */
			~LuaDust();

			/**
			 * Add a function to the lua state from a C++ function
			 *
			 * \param name Lua function name
			 * \param func C++ function pointer
			 */
			template <typename RetType, typename... Args>
			Function<RetType, Args...> *addFunction(const std::string &name, RetType (*func)(Args...));

			/**
			 * Add a function to the lua state from a C++ class method
			 *
			 * \param name Lua function name
			 * \param ptr Class pointer use to call the class method
			 * \param meth C++ class method pointer
			 */
			template <typename RetType, typename Class, typename... Args>
			Method<RetType, Class, Args...> *addFunction(const std::string &name, Class *ptr, RetType (Class::*meth)(Args...));

			/**
			 * Add a C++ reference to the lua state.
			 *
			 * \param name Lua variable name
			 * \param value C++ reference
			 * \return Lua reference class
			 */
			template <typename Type>
			IVarRef *addRefGlobal(const std::string &name, Type *value);

			/**
			 * Add an array to the lua state from an C++ array container.
			 *
			 * \param name Lua array name
			 * \param value C++ array container reference
			 * \return Lua array class
			 */
			template <typename Type>
			Array<Type> *addArray(const std::string &name, Type *value);

			/**
			 * Add a global boolean variable to the lua state 
			 * @param  name  Lua global name
			 * @param  value Value of the global
			 * @return       Return true is everything is ok
			 */
			bool addGlobal(const std::string &name, bool value);

			/**
			 * Add a global integer variable to the lua state 
			 * @param  name  Lua global name
			 * @param  value Value of the global
			 * @return       Return true is everything is ok
			 */
			bool addGlobal(const std::string &name, int value);
			/**
			 * Add a global double variable to the lua state 
			 * @param  name  Lua global name
			 * @param  value Value of the global
			 * @return       Return true is everything is ok
			 */
			bool addGlobal(const std::string &name, double value);

			/**
			 * Add a global string variable to the lua state 
			 * @param  name  Lua global name
			 * @param  value Value of the global
			 * @return       Return true is everything is ok
			 */
			bool addGlobal(const std::string &name, const char *value);

			/**
			 * Add a global string (as std::string) variable to the lua state 
			 * @param  name  Lua global name
			 * @param  value Value of the global
			 * @return       Return true if everything is ok
			 */
			bool addGlobal(const std::string &name, const std::string &value);

			/**
			 * Execute the given lua file.
			 * @param  file Filename
			 * @return      Return true if everything is ok
			 */
			bool doFile(const std::string &file);

			/**
			 * Execute the given lua string.
			 * @param  lua Lua string
			 * @return      Return true if everything is ok
			 */
			bool doString(const std::string &lua);

			/**
			 * Return the lua state as lua_State LuaApi
			 * @return Lua state
			 */
			lua_State *getState() const;

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