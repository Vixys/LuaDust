#ifndef LUA_DUST_FUNCTION_HPP
#define LUA_DUST_FUNCTION_HPP

#include <tuple>

#include "Internal.hpp"

namespace LuaDust
{
	/**
	 * Represent a C++ function callable in Lua state.
	 */
	template <typename RetType, typename... Args>
	class Function
	{
		public:
			/**
			 * Function signature.
			 */
			typedef RetType (*FunctionType)(Args...);

			/**
			 * Constructor
			 *
			 * \param dust Pointer to the lua state
			 * \param name Function name in the lua state
			 * \param func Pointer to the C++ function
			 */
			Function(LuaDust *dust, const std::string &name, FunctionType &func)
			{
				this->_func = func;
				this->_dust = dust;
				lua_pushlightuserdata(this->_dust->getState(), this);
			    lua_pushcclosure(this->_dust->getState(), &__call, 1);
			    lua_setglobal(this->_dust->getState(), name.c_str());
			}

			/**
			 * Destructor
			 */
			~Function() { }

		private:
			
			FunctionType _func;
			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);
			
			/**
			 * Function use for the binding between the lua and the C++.
			 *
			 * This function is called when the lua state try to call the C++ function.
			 *  
			 * @param  state Lua state
			 * @return       Status of the the calling process
			 */
			static int __call(lua_State *state)
			{
				auto func = (Function<RetType, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
				return func->_call(state);
			}

			/**
			 * This function call the C++ function. By using template, determine what kind of parameter need the C++ function
			 * and pop parameter from the lua state stack.
			 * 
			 * @param  state Lua state
			 * @return       If everything is ok, return 1.
			 */
			int _call(lua_State *state)
			{
				RetType ret = Internal::callFunc(state, this->_func, this->_args);
				if (Arg_Count_ > 0)
					lua_pop(state, Arg_Count_);
				Internal::pushValue(state, ret);
				return 1;
			}
	};

	/**
	 * Represent a C++ function callable in Lua state.
	 */
	template <typename... Args>
	class Function<void, Args...>
	{
		public:
			/**
			 * Function signature.
			 */
			typedef void (*FunctionType)(Args...);

			/**
			 * Constructor
			 *
			 * \param dust Pointer to the lua state
			 * \param name Function name in the lua state
			 * \param func Pointer to the C++ function
			 */
			Function(LuaDust *dust, const std::string &name, FunctionType &func)
			{
				this->_func = func;
				this->_dust = dust;
				lua_pushlightuserdata(this->_dust->getState(), this);
			    lua_pushcclosure(this->_dust->getState(), &__call, 1);
			    lua_setglobal(this->_dust->getState(), name.c_str());
			}

			/**
			 * Destructor
			 */
			~Function() { }

		private:
			
			FunctionType _func;
			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);

			/**
			 * Function use for the binding between the lua and the C++.
			 *
			 * This function is called when the lua state try to call the C++ function.
			 *  
			 * @param  state Lua state
			 * @return       Status of the the calling process
			 */
			static int __call(lua_State *state)
			{
				auto func = (Function<void, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
				return func->_call(state);
			}

			/**
			 * This function call the C++ function. By using template, determine what kind of parameter need the C++ function
			 * and pop parameter from the lua state stack.
			 * 
			 * @param  state Lua state
			 * @return       If everything is ok, return 1.
			 */
			int _call(lua_State *state)
			{
				Internal::callFunc(state, this->_func, this->_args);
				if (Arg_Count_ > 0)
					lua_pop(state, Arg_Count_);
				return 1;
			}
	};
} // End LuaDust namespace

#endif // LUA_DUST_FUNCTION_HPP