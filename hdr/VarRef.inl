template <typename Type>
inline VarRef<Type>::VarRef(LuaDust *, const std::string &, Type *)
{
	// compilation error
}

template <typename Type>
inline VarRef<Type>::~VarRef()
{
}

template <typename Type>
inline const std::string &VarRef<Type>::getName() const
{
	return this->_name;
}

template <typename Type>
inline std::string VarRef<Type>::getStringValue(bool) const
{
	std::stringstream out;
	
	out << *this->_ref;

	return out.str();
}

template <>
inline void VarRef<int>::pushRef()
{
	lua_pushinteger(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline VarRef<int>::VarRef(LuaDust *dust, const std::string &name, int *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
}

template <>
inline void VarRef<int>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tointeger(this->_dust->getState(), -1);
}

template <>
inline void VarRef<bool>::pushRef()
{
	lua_pushboolean(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline VarRef<bool>::VarRef(LuaDust *dust, const std::string &name, bool *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
}

template <>
inline void VarRef<bool>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_toboolean(this->_dust->getState(), -1);
}

template <>
inline void VarRef<float>::pushRef()
{
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline VarRef<float>::VarRef(LuaDust *dust, const std::string &name, float *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
}

template <>
inline void VarRef<float>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tonumber(this->_dust->getState(), -1);
}

template <>
inline void VarRef<double>::pushRef()
{
	lua_pushnumber(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline VarRef<double>::VarRef(LuaDust *dust, const std::string &name, double *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
}

template <>
inline void VarRef<double>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = lua_tonumber(this->_dust->getState(), -1);
}

template <>
inline void VarRef<char*>::pushRef()
{
	lua_pushstring(this->_dust->getState(), *this->_ref);
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline VarRef<char*>::VarRef(LuaDust *dust, const std::string &name, char **ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
}

template <>
inline void VarRef<char*>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = const_cast<char*>(lua_tostring(this->_dust->getState(), -1));
}

template <>
inline void VarRef<std::string>::pushRef()
{
	lua_pushstring(this->_dust->getState(), this->_ref->c_str());
	lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <>
inline VarRef<std::string>::VarRef(LuaDust *dust, const std::string &name, std::string *ref)
{
	this->_dust = dust;
	this->_ref = ref;
	this->_name = name;
}

template <>
inline void VarRef<std::string>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	*this->_ref = const_cast<char*>(lua_tostring(this->_dust->getState(), -1));
}

template <>
inline std::string VarRef<std::string>::getStringValue(bool codeStyle) const
{
	std::stringstream out;
	
	if (codeStyle)
		out << "\"" << *this->_ref << "\"";
	else
		out << *this->_ref;

	return out.str();
}

template <>
inline std::string VarRef<char *>::getStringValue(bool codeStyle) const
{
	std::stringstream out;
	
	if (codeStyle)
		out << "\"" << *this->_ref << "\"";
	else
		out << *this->_ref;

	return out.str();
}

template <>
inline std::string VarRef<bool>::getStringValue(bool) const
{
	std::stringstream out;
	
	out << std::boolalpha << *this->_ref;

	return out.str();
}