// template <class RetType, class... Args>
// LuaDustFunction::LuaDustFunction(LuaDust *dust, const std::string &name, RetType (*func)(Args...))
// {
// 	this->_func = func;
// 	this->_dust = dust;
// 	lua_pushlightuserdata(this->_dust->getState(), this);
//     lua_pushcclosure(this->_dust->getState(), &__call, 1);
//     lua_setglobal(this->_dust->getState(), name.c_str());
// }

// template <class RetType, class... Args>
// int LuaDustFunction::__call(lua_State *state)
// {
// 	auto func = (LuaDustFunction<RetType, Args...> *)lua_touserdata(state, lua_upvalueindex(1));
// 	return func->_call(state);
// }

// template <class RetType, class... Args>
// int LuaDustFunction::_call(lua_State *state)
// {
// 	LuaDust::callFunc(this->dust, this->func, this->_args)
// 	lua_pop(this->_dust->getState(), sizeof(Args...));
// 	LuaDust::returnValue(this->_dust, ret);
// 	return 1;
// }