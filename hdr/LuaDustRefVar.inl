template <typename Type>
LuaDustRefVar<Type>::LuaDustRefVar(LuaDust *dust, const std::string &name, Type *ref)
{
	std::cerr << "reference incorrect" << std::endl;
}

template <typename Type>
void LuaDustRefVar<Type>::updateRef()
{
	std::cerr << "reference incorrect" << std::endl;
}

template <>
LuaDustRefVar<int>::LuaDustRefVar(LuaDust *dust, const std::string &name, int *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushinteger(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
void LuaDustRefVar<int>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tointeger(this->_dust->getState(), -1);
}

template <>
void LuaDustRefVar<int>::pushRef()
{
	lua_pushinteger(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
LuaDustRefVar<float>::LuaDustRefVar(LuaDust *dust, const std::string &name, float *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
void LuaDustRefVar<float>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tonumber(this->_dust->getState(), -1);
}

template <>
void LuaDustRefVar<float>::pushRef()
{
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
LuaDustRefVar<double>::LuaDustRefVar(LuaDust *dust, const std::string &name, double *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
void LuaDustRefVar<double>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tonumber(this->_dust->getState(), -1);
}

template <>
void LuaDustRefVar<double>::pushRef()
{
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
LuaDustRefVar<char*>::LuaDustRefVar(LuaDust *dust, const std::string &name, char **ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushstring(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
void LuaDustRefVar<char*>::pushRef()
{
	lua_pushstring(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
void LuaDustRefVar<char*>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = const_cast<char*>(lua_tostring(this->_dust->getState(), -1));
}

template <>
LuaDustRefVar<std::string>::LuaDustRefVar(LuaDust *dust, const std::string &name, std::string *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushstring(this->_dust->getState(), this->_ref->c_str());
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
void LuaDustRefVar<std::string>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = const_cast<char*>(lua_tostring(this->_dust->getState(), -1));
}

template <>
void LuaDustRefVar<std::string>::pushRef()
{
	lua_pushstring(this->_dust->getState(), this->_ref->c_str());
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}