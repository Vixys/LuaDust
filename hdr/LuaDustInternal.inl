template <typename ReturnType>
void LuaDustInternal::returnValue(lua_State *state, ReturnType ret)
{
}

template <>
inline void LuaDustInternal::returnValue<int>(lua_State *state, int ret)
{
	lua_pushinteger(state, ret);
}

template <>
inline void LuaDustInternal::returnValue<double>(lua_State *state, double ret)
{
	lua_pushnumber(state, ret);
}

template <>
inline void LuaDustInternal::returnValue<const char *>(lua_State *state, const char * ret)
{
	lua_pushstring(state, ret);
}

template <>
struct LuaDustInternal::pop_func_params<0>
{
	template<typename R, typename... ArgsT, typename... ArgsF, typename... Args>
	static R pop_params(lua_State *, R (*func)(ArgsF...), const std::tuple<ArgsT...> &, Args... args)
	{
		return func(args...);
	}
};

template <typename ParamType>
ParamType LuaDustInternal::paramValue(lua_State *state, int id)
{
	return nullptr;
}

template <>
inline int LuaDustInternal::paramValue<int>(lua_State *state, int id)
{
	return luaL_checkint(state, id);
}

template <>
inline double LuaDustInternal::paramValue<double>(lua_State *state, int id)
{
	return luaL_checknumber(state, id);
}

template <>
inline const char * LuaDustInternal::paramValue<const char *>(lua_State *state, int id)
{
	return luaL_checkstring(state, id);
}

template <typename ReturnType, typename... ArgsT, typename... Args>
ReturnType LuaDustInternal::callFunc(lua_State *state, ReturnType (*func)(Args...), const std::tuple<ArgsT...> & argsType)
{
	return LuaDustInternal::pop_func_params<sizeof...(Args)>::pop_params(state, func, argsType);
}
