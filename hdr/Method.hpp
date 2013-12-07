#ifndef METHOD_HPP
#define METHOD_HPP

#include <tuple>

#include "Internal.hpp"

namespace LuaDust
{
	template <typename RetType, typename Class, typename... Args>
	class Method
	{
		public:
			typedef RetType (Class::*MethodType)(Args...);

			Method(LuaDust *dust, const std::string &name, Class *class_ptr, MethodType &func);

			~Method() { }

		private:
			
			Class *_class;
			MethodType _func;
			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);
			
			static int __call(lua_State *state);

			int _call(lua_State *state);
	};

	template <typename Class, typename... Args>
	class Method<void, Class, Args...>
	{
		public:
			typedef void (Class::*MethodType)(Args...);

			Method(LuaDust *dust, const std::string &name, Class *class_ptr, MethodType &func);

			~Method() { }

		private:
			
			Class *_class;
			MethodType _func;
			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);

			static int __call(lua_State *state);

			int _call(lua_State *state);
	};

	#include "Method.inl"
} // End LuaDust namespace

#endif // METHOD_HPP