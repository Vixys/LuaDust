template <typename ContainerType>
inline Array<ContainerType>::Array(LuaDust *dust, const std::string &name, ContainerType *container)
{
	this->_dust = dust;
	this->_ref = container;
	this->_name = name;
	lua_newtable(this->_dust->getState());
    lua_setglobal(this->_dust->getState(), this->_name.c_str());
}

template <typename ContainerType>
inline Array<ContainerType>::~Array()
{
}

template <typename ContainerType>
inline void Array<ContainerType>::updateRef()
{
	lua_getglobal(this->_dust->getState(), this->_name.c_str());
	if (lua_istable(this->_dust->getState(), -1))
    {
    	lua_pushnil(this->_dust->getState());
		while (lua_next(this->_dust->getState(), -2) != 0) 
		{
			int i = lua_tointeger(this->_dust->getState(), -2) - 1;

			if (this->_ref->size() <= i)
    			throw LuaDustException("Array: " + this->_name + ": the size of the array cannot be change.");

			(*this->_ref)[i] = Internal::getValue<ValueType>(this->_dust->getState(), -1);

			lua_pop(this->_dust->getState(), 1);
		}    	
    }
    else
    {
    	throw LuaDustException("Array: " + this->_name + ": Invalid use of the array type.");
    }
}

template <typename ContainerType>
inline void Array<ContainerType>::pushRef()
{
	int i = 1;
	for (ValueType value : *this->_ref)
	{
	    lua_getglobal(this->_dust->getState(), this->_name.c_str());

	    lua_pushinteger(this->_dust->getState(), i);

	    Internal::pushValue(this->_dust->getState(), value);

	    lua_settable(this->_dust->getState(), -3);
		    
	    lua_setglobal(this->_dust->getState(), this->_name.c_str());

	    ++i;
	}
}

template <typename ContainerType>
std::string Array<ContainerType>::getStringValue(bool) const
{
	std::stringstream out;
	int i = 0;

	out << "{";
	for (ValueType value : *this->_ref)
	{
		if (i > 0)
			out << ',';
	   	out << ' ';
	   	if (std::is_same<ValueType, std::string>::value
	   		|| std::is_same<ValueType, char *>::value)
	   	{
	   		out << '"' << value << '"';
	   	}
	   	else
		   	out << value;
		++i;
	}
	out << " }";

	return out.str();
}

template <typename ContainerType>
inline const std::string &Array<ContainerType>::getName() const
{
	return this->_name;
}