#ifndef METHOD_HPP
#define METHOD_HPP

#include <tuple>

#include "Internal.hpp"

namespace LuaDust
{
	/**
	 * Represent a C++ class method callable in Lua state.
	 */
	template <typename RetType, typename Class, typename... Args>
	class Method
	{
		public:
			/**
			 * Method signature.
			 */
			typedef RetType (Class::*MethodType)(Args...);

			/**
			 * Constructor
			 *
			 * \param dust Pointer to the lua state
			 * \param name Function name in the lua state
			 * \param class_ptr Class pointer to call the method pointer
			 * \param meth Pointer to the C++ method
			 */
			Method(LuaDust *dust, const std::string &name, Class *class_ptr, MethodType &meth);

			/**
			 * Destructor
			 */
			~Method() { }

		private:
			
			Class *_class;
			MethodType _func;
			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);
			
			/**
			 * Function use for the binding between the lua and the C++.
			 *
			 * This function is called when the lua state try to call the C++ class method.
			 *  
			 * @param  state Lua state
			 * @return       Status of the the calling process
			 */
			static int __call(lua_State *state);

			/**
			 * This function call the C++ function. By using template, determine what kind of parameter need the C++ function
			 * and pop parameter from the lua state stack.
			 * 
			 * @param  state Lua state
			 * @return       If everything is ok, return 1.
			 */
			int _call(lua_State *state);
	};

	/**
	 * Represent a C++ class method callable in Lua state.
	 */
	template <typename Class, typename... Args>
	class Method<void, Class, Args...>
	{
		public:
			/**
			 * Method signature.
			 */
			typedef void (Class::*MethodType)(Args...);

			/**
			 * Constructor
			 *
			 * \param dust Pointer to the lua state
			 * \param name Function name in the lua state
			 * \param class_ptr Class pointer to call the method pointer
			 * \param meth Pointer to the C++ method
			 */
			Method(LuaDust *dust, const std::string &name, Class *class_ptr, MethodType &meth);

			/**
			 * Destructor
			 */
			~Method() { }

		private:
			
			Class *_class;
			MethodType _func;			/**
			 * Function signature.
			 */

			LuaDust *_dust;
			std::tuple<Args...> _args;
			static const unsigned int Arg_Count_ = sizeof...(Args);

			/**
			 * Function use for the binding between the lua and the C++.
			 *
			 * This function is called when the lua state try to call the C++ class method.
			 *  
			 * @param  state Lua state
			 * @return       Status of the the calling process
			 */
			static int __call(lua_State *state);

			/**
			 * This function call the C++ function. By using template, determine what kind of parameter need the C++ function
			 * and pop parameter from the lua state stack.
			 * 
			 * @param  state Lua state
			 * @return       If everything is ok, return 1.
			 */
			int _call(lua_State *state);
	};

	#include "Method.inl"
} // End LuaDust namespace

#endif // METHOD_HPP