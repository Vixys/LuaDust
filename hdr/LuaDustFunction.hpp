#ifndef LUA_DUST_FUNCTION_HPP
#define LUA_DUST_FUNCTION_HPP

#include <tuple>

#include "LuaDustInternal.hpp"

template <typename RetType, typename... Args>
class LuaDustFunction
{
	public:
		typedef RetType (*Function)(Args...);

		LuaDustFunction(LuaDust *dust, const std::string &name, Function &func)
		{
			this->_func = func;
			this->_dust = dust;
			lua_pushlightuserdata(this->_dust->getState(), this);
		    lua_pushcclosure(this->_dust->getState(), &__call, 1);
		    lua_setglobal(this->_dust->getState(), name.c_str());
		}

		~LuaDustFunction() { }

	private:
		
		Function _func;
		LuaDust *_dust;
		std::tuple<Args...> _args;
		static const unsigned int Arg_Count_ = sizeof...(Args);
		
		static int __call(lua_State *state)
		{
			auto func = (LuaDustFunction<RetType, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
			return func->_call(state);
		}

		int _call(lua_State *state)
		{
			RetType ret = LuaDustInternal::callFunc(state, this->_func, this->_args);
			if (Arg_Count_ > 0)
				lua_pop(state, Arg_Count_);
			LuaDustInternal::returnValue(state, ret);
			return 1;
		}
};

template <typename... Args>
class LuaDustFunction<void, Args...>
{
	public:
		typedef void (*Function)(Args...);

		LuaDustFunction(LuaDust *dust, const std::string &name, Function &func)
		{
			this->_func = func;
			this->_dust = dust;
			lua_pushlightuserdata(this->_dust->getState(), this);
		    lua_pushcclosure(this->_dust->getState(), &__call, 1);
		    lua_setglobal(this->_dust->getState(), name.c_str());
		}

		~LuaDustFunction() { }

	private:
		
		Function _func;
		LuaDust *_dust;
		std::tuple<Args...> _args;
		static const unsigned int Arg_Count_ = sizeof...(Args);

		static int __call(lua_State *state)
		{
			auto func = (LuaDustFunction<void, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
			return func->_call(state);
		}

		int _call(lua_State *state)
		{
			LuaDustInternal::callFunc(state, this->_func, this->_args);
			if (Arg_Count_ > 0)
				lua_pop(state, Arg_Count_);
			return 1;
		}
};

#include "LuaDustFunction.inl"

#endif // LUA_DUST_FUNCTION_HPP