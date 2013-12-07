template <>
inline bool Internal::getValue<bool>(lua_State *state, int id)
{
	return lua_toboolean(state, id);
}

template <>
inline int Internal::getValue<int>(lua_State *state, int id)
{
	return lua_tointeger(state, id);
}

template <>
inline float Internal::getValue<float>(lua_State *state, int id)
{
	return lua_tonumber(state, id);
}

template <>
inline double Internal::getValue<double>(lua_State *state, int id)
{
	return lua_tonumber(state, id);
}

template <>
inline const char *Internal::getValue<const char *>(lua_State *state, int id)
{
	return lua_tostring(state, id);
}

template <>
inline std::string Internal::getValue<std::string>(lua_State *state, int id)
{
	return lua_tostring(state, id);
}

template <>
inline void Internal::pushValue<bool>(lua_State *state, bool value)
{
	lua_pushboolean(state, value);
}

template <>
inline void Internal::pushValue<int>(lua_State *state, int value)
{
	lua_pushinteger(state, value);
}

template <>
inline void Internal::pushValue<float>(lua_State *state, float value)
{
	lua_pushnumber(state, value);
}

template <>
inline void Internal::pushValue<double>(lua_State *state, double value)
{
	lua_pushnumber(state, value);
}

template <>
inline void Internal::pushValue<char *>(lua_State *state, char *value)
{
	lua_pushstring(state, value);
}

template <>
inline void Internal::pushValue<std::string>(lua_State *state, std::string value)
{
	lua_pushstring(state, value.c_str());
}

template <>
struct Internal::pop_func_params<0>
{
	template<typename R, typename... ArgsT, typename... ArgsF, typename... Args>
	inline static R pop_params(lua_State *, R (*func)(ArgsF...), const std::tuple<ArgsT...> &, Args... args)
	{
		return func(args...);
	}

	template<typename R, typename Class, typename... ArgsT, typename... ArgsF, typename... Args>
	inline static R pop_params(lua_State *, Class *ptr, R (Class::*func)(ArgsF...), const std::tuple<ArgsT...> &, Args... args)
	{
		return (ptr->*func)(args...);
	}
};

template <>
inline bool Internal::paramValue<bool>(lua_State *state, int id)
{
	return lua_toboolean(state, id);
}

template <>
inline int Internal::paramValue<int>(lua_State *state, int id)
{
	return luaL_checkint(state, id);
}

template <>
inline float Internal::paramValue<float>(lua_State *state, int id)
{
	return luaL_checknumber(state, id);
}

template <>
inline double Internal::paramValue<double>(lua_State *state, int id)
{
	return luaL_checknumber(state, id);
}

template <>
inline std::string Internal::paramValue<std::string>(lua_State *state, int id)
{
	return luaL_checkstring(state, id);
}

template <>
inline const char * Internal::paramValue<const char *>(lua_State *state, int id)
{
	return luaL_checkstring(state, id);
}

template <typename ReturnType, typename... ArgsT, typename... Args>
ReturnType Internal::callFunc(lua_State *state, ReturnType (*func)(Args...), const std::tuple<ArgsT...> & argsType)
{
	return Internal::pop_func_params<sizeof...(Args)>::pop_params(state, func, argsType);
}

template <typename ReturnType, typename Class, typename... ArgsT, typename... Args>
ReturnType Internal::callFunc(lua_State *state, Class *ptr, ReturnType (Class::*func)(Args...), const std::tuple<ArgsT...> & argsType)
{
	return Internal::pop_func_params<sizeof...(Args)>::pop_params(state, ptr, func, argsType);
}
