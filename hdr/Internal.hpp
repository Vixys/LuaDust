#ifndef LUA_DUST_UTILS_HPP
#define LUA_DUST_UTILS_HPP

#include <tuple>

namespace LuaDust
{
	/**
	 * This class contains internal usefull for the binding process.
	 */
	class Internal
	{
		public:
			/**
			 * Get from the lua state stack the value of Type.
			 *
			 * \param state Lua state
			 * \param int id on the stack
			 * \return  Value on the stack
			 */
			template <typename Type>
			static Type getValue(lua_State *state, int id = -1);

			/**
			 * Push a value of Type on the lua state stack.
			 */
			template <typename Type>
			static void pushValue(lua_State *state, Type value);

		private:

			/**
			 * Loop template structure.
			 *
			 * (For internal use only)
			 */
			template <unsigned int N> 
			struct pop_func_params
			{
				/**
				 * Get all parameter from the lua state stack and call the function func
				 *
				 * \param state Lua state
				 * \param func Function to call
				 * \param argsType Tuple of all parameter type
				 * \param args Varidic parameter containing all function parameter (Use for internal purpose)
				 * \return Return value of the calling function func
				 */
				template<typename R, typename... ArgsT, typename... ArgsF, typename... Args>
				static R pop_params(lua_State *state, R (*func)(ArgsF...), const std::tuple<ArgsT...> &argsType, Args... args)
				{
					const static unsigned int argCount = sizeof...(ArgsT);
	                typedef typename std::remove_reference<decltype(std::get<N-1>(argsType))>::type ltype_const;
	                typedef typename std::remove_const<ltype_const>::type ltype;
	                return pop_func_params<N-1>::pop_params(state, func, std::forward<decltype(argsType)>(argsType), paramValue<ltype>(state, -(argCount-N+1)), args... );
				}

				/**
				 * Get all parameter from the lua state stack and call the method func
				 *
				 * \param state Lua state
				 * \param meth Method to call
				 * \param argsType Tuple of all parameter type
				 * \param args Varidic parameter containing all method parameter (Use for internal purpose)
				 * \return Return value of the calling method meth
				 */
				template<typename R, typename Class, typename... ArgsT, typename... ArgsF, typename... Args>
				static R pop_params(lua_State *state, Class *ptr, R (Class::*meth)(ArgsF...), const std::tuple<ArgsT...> &argsType, Args... args)
				{
					const static unsigned int argCount = sizeof...(ArgsT);
	                typedef typename std::remove_reference<decltype(std::get<N-1>(argsType))>::type ltype_const;
	                typedef typename std::remove_const<ltype_const>::type ltype;
	                return pop_func_params<N-1>::pop_params(state, ptr, meth, std::forward<decltype(argsType)>(argsType), paramValue<ltype>(state, -(argCount-N+1)), args... );
				}
			};

			template <typename RetType, typename... Args>
			friend class Function;

			template <typename RetType, typename Class, typename... Args>
			friend class Method;

			/**
			 * Call the given function using the pop_func_params structure
			 *
			 * \param state Lua state
			 * \param func Function to call
			 * \param args Tuple of all parameter type
			 * \return Return value of the calling function func
			 */
			template <typename ReturnType, typename... ArgsT, typename... Args>
			static ReturnType callFunc(lua_State *state, ReturnType (*func)(Args...), const std::tuple<ArgsT...> &args);

			/**
			 * Call the given method using the pop_func_params structure
			 *
			 * \param state Lua state
			 * \param meth Function to call
			 * \param args Tuple of all parameter type
			 * \return Return value of the calling method meth
			 */
			template <typename ReturnType, typename Class, typename... ArgsT, typename... Args>
			static ReturnType callFunc(lua_State *state, Class *ptr, ReturnType (Class::*meth)(Args...), const std::tuple<ArgsT...> &args);

			// template <typename ReturnType, typename... ArgsT, typename... Args>
			// static ReturnType popParams(lua_State *state, ReturnType (*func)(Args...), const std::tuple<ArgsT...> & argsType);

			/**
			 * Get the param value from the lua state stack.
			 *
			 * Use when calling function or method
			 *
			 * \param state Lua state
			 * \param int id on the stack
			 * \return Return the parameter value
			 */
			template <typename ParamType>
			static ParamType paramValue(lua_State *state, int id);
	};

	#include "Internal.inl"
} // End LuaDust namespace

#endif // LUA_DUST_UTILS_HPP