template <typename RetType, typename Class, typename... Args>
Method<RetType, Class, Args...>::Method(LuaDust *dust, const std::string &name, Class *class_ptr, MethodType &func)
{
	this->_class = class_ptr;
	this->_func = func;
	this->_dust = dust;
	lua_pushlightuserdata(this->_dust->getState(), this);
    lua_pushcclosure(this->_dust->getState(), &__call, 1);
    lua_setglobal(this->_dust->getState(), name.c_str());
}

template <typename RetType, typename Class, typename... Args>
int Method<RetType, Class, Args...>::__call(lua_State *state)
{
	auto func = (Method<RetType, Class, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
	return func->_call(state);
}

template <typename RetType, typename Class, typename... Args>
int Method<RetType, Class, Args...>::_call(lua_State *state)
{
	RetType ret = Internal::callFunc(state, this->_class, this->_func, this->_args);
	if (Arg_Count_ > 0)
		lua_pop(state, Arg_Count_);
	Internal::pushValue(state, ret);
	return 1;
}

template <typename Class, typename... Args>
Method<void, Class, Args...>::Method(LuaDust *dust, const std::string &name, Class *class_ptr, MethodType &func)
{
	this->_class = class_ptr;
	this->_func = func;
	this->_dust = dust;
	lua_pushlightuserdata(this->_dust->getState(), this);
    lua_pushcclosure(this->_dust->getState(), &__call, 1);
    lua_setglobal(this->_dust->getState(), name.c_str());
}

template <typename Class, typename... Args>
int Method<void, Class, Args...>::__call(lua_State *state)
{
	auto func = (Method<void, Class, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
	return func->_call(state);
}

template <typename Class, typename... Args>
int Method<void, Class, Args...>::_call(lua_State *state)
{
	Internal::callFunc(state, this->_class, this->_func, this->_args);
	if (Arg_Count_ > 0)
		lua_pop(state, Arg_Count_);
	return 1;
}

