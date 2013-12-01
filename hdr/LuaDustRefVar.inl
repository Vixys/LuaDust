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
inline LuaDustRefVar<int>::LuaDustRefVar(LuaDust *dust, const std::string &name, int *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushinteger(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline void LuaDustRefVar<int>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tointeger(this->_dust->getState(), -1);
}

template <>
inline void LuaDustRefVar<int>::pushRef()
{
	lua_pushinteger(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline LuaDustRefVar<float>::LuaDustRefVar(LuaDust *dust, const std::string &name, float *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline void LuaDustRefVar<float>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tonumber(this->_dust->getState(), -1);
}

template <>
inline void LuaDustRefVar<float>::pushRef()
{
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline LuaDustRefVar<double>::LuaDustRefVar(LuaDust *dust, const std::string &name, double *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline void LuaDustRefVar<double>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tonumber(this->_dust->getState(), -1);
}

template <>
inline void LuaDustRefVar<double>::pushRef()
{
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline LuaDustRefVar<char*>::LuaDustRefVar(LuaDust *dust, const std::string &name, char **ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushstring(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline void LuaDustRefVar<char*>::pushRef()
{
	lua_pushstring(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline void LuaDustRefVar<char*>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = const_cast<char*>(lua_tostring(this->_dust->getState(), -1));
}

template <>
inline LuaDustRefVar<std::string>::LuaDustRefVar(LuaDust *dust, const std::string &name, std::string *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
	lua_pushstring(this->_dust->getState(), this->_ref->c_str());
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline void LuaDustRefVar<std::string>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = const_cast<char*>(lua_tostring(this->_dust->getState(), -1));
}

template <>
inline void LuaDustRefVar<std::string>::pushRef()
{
	lua_pushstring(this->_dust->getState(), this->_ref->c_str());
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline std::string LuaDustRefVar<std::string>::getStringValue() const
{
	std::stringstream out;
	
	out << "\"" << *this->_ref << "\"";

	return out.str();
}