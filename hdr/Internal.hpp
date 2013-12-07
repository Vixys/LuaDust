#ifndef LUA_DUST_UTILS_HPP
#define LUA_DUST_UTILS_HPP

#include <tuple>

namespace LuaDust
{
	class Internal
	{
		public:
			template <typename Type>
			static Type getValue(lua_State *state, int id);

			template <typename Type>
			static void pushValue(lua_State *state, Type value);

		private:
			template <unsigned int N> 
			struct pop_func_params
			{
				template<typename R, typename... ArgsT, typename... ArgsF, typename... Args>
				static R pop_params(lua_State *state, R (*func)(ArgsF...), const std::tuple<ArgsT...> &tuple, Args... args)
				{
					const static unsigned int argCount = sizeof...(ArgsT);
	                typedef typename std::remove_reference<decltype(std::get<N-1>(tuple))>::type ltype_const;
	                typedef typename std::remove_const<ltype_const>::type ltype;
	                return pop_func_params<N-1>::pop_params(state, func, std::forward<decltype(tuple)>(tuple), paramValue<ltype>(state, -(argCount-N+1)), args... );
				}

				template<typename R, typename Class, typename... ArgsT, typename... ArgsF, typename... Args>
				static R pop_params(lua_State *state, Class *ptr, R (Class::*func)(ArgsF...), const std::tuple<ArgsT...> &tuple, Args... args)
				{
					const static unsigned int argCount = sizeof...(ArgsT);
	                typedef typename std::remove_reference<decltype(std::get<N-1>(tuple))>::type ltype_const;
	                typedef typename std::remove_const<ltype_const>::type ltype;
	                return pop_func_params<N-1>::pop_params(state, ptr, func, std::forward<decltype(tuple)>(tuple), paramValue<ltype>(state, -(argCount-N+1)), args... );
				}
			};

			template <typename RetType, typename... Args>
			friend class Function;

			template <typename RetType, typename Class, typename... Args>
			friend class Method;

			template <typename ReturnType, typename... ArgsT, typename... Args>
			static ReturnType callFunc(lua_State *state, ReturnType (*func)(Args...), const std::tuple<ArgsT...> &args);

			template <typename ReturnType, typename Class, typename... ArgsT, typename... Args>
			static ReturnType callFunc(lua_State *state, Class *ptr, ReturnType (Class::*func)(Args...), const std::tuple<ArgsT...> &args);

			// template <typename ReturnType, typename... ArgsT, typename... Args>
			// static ReturnType popParams(lua_State *state, ReturnType (*func)(Args...), const std::tuple<ArgsT...> & argsType);

			template <typename ParamType>
			static ParamType paramValue(lua_State *state, int id);
	};

	#include "Internal.inl"
} // End LuaDust namespace

#endif // LUA_DUST_UTILS_HPP