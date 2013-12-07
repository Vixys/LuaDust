#ifndef LUA_DUST_FUNCTION_HPP
#define LUA_DUST_FUNCTION_HPP

#include <tuple>

#include "Internal.hpp"

namespace LuaDust
{
	template <typename RetType, typename... Args>
	class Function
	{
		public:
			typedef RetType (*FunctionType)(Args...);

			Function(LuaDust *dust, const std::string &name, FunctionType &func)
			{
				this->_func = func;
				this->_dust = dust;
				lua_pushlightuserdata(this->_dust->getState(), this);
			    lua_pushcclosure(this->_dust->getState(), &__call, 1);
			    lua_setglobal(this->_dust->getState(), name.c_str());
			}

			~Function() { }

		private:
			
			FunctionType _func;
			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);
			
			static int __call(lua_State *state)
			{
				auto func = (Function<RetType, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
				return func->_call(state);
			}

			int _call(lua_State *state)
			{
				RetType ret = Internal::callFunc(state, this->_func, this->_args);
				if (Arg_Count_ > 0)
					lua_pop(state, Arg_Count_);
				Internal::pushValue(state, ret);
				return 1;
			}
	};

	template <typename... Args>
	class Function<void, Args...>
	{
		public:
			typedef void (*FunctionType)(Args...);

			Function(LuaDust *dust, const std::string &name, FunctionType &func)
			{
				this->_func = func;
				this->_dust = dust;
				lua_pushlightuserdata(this->_dust->getState(), this);
			    lua_pushcclosure(this->_dust->getState(), &__call, 1);
			    lua_setglobal(this->_dust->getState(), name.c_str());
			}

			~Function() { }

		private:
			
			FunctionType _func;
			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);

			static int __call(lua_State *state)
			{
				auto func = (Function<void, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
				return func->_call(state);
			}

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