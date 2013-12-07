template <typename RetType, typename... Args>
Function<RetType, Args...> *LuaDust::addFunction(const std::string &name, RetType (*func)(Args...))
{
	auto *f = new Function<RetType, Args...>(this, name, func);
	return f;
}

template <typename RetType, typename Class, typename... Args>
Method<RetType, Class, Args...> *LuaDust::addFunction(const std::string &name, Class *ptr, RetType (Class::*func)(Args...))
{
	auto *f = new Method<RetType, Class, Args...>(this, name, ptr, func);
	return f;
}

template <typename Type>
IVarRef *LuaDust::addRefGlobal(const std::string &name, Type *value)
{
	auto new_ref_global = new VarRef<Type>(this, name, value);
	this->_refs.push_back(new_ref_global);
	return new_ref_global;
}

template <typename Type>
Array<Type> *LuaDust::addArray(const std::string &name, Type *value)
{
	auto new_array = new Array<Type>(this, name, value);
	this->_refs.push_back(new_array);
	return new_array;
}
