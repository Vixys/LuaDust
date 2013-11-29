// template <typename Type>
// bool LuaDust::addCustomGlobal(const std::string &name, const Type &value)
// {
// 	// Custom value type
// 	std::cout << "ERROR: " << name << ":" << value << std::endl;
// 	// lua_setglobal(this->state, name.c_str());
// 	return true;
// }

template <typename RetType, typename... Args>
LuaDustFunction<RetType, Args...> *LuaDust::addFunction(const std::string &name, RetType (*func)(Args...))
{
	auto *f = new LuaDustFunction<RetType, Args...>(this, name, func);
	return f;
}

template <typename Type>
LuaDustRef *LuaDust::addRefGlobal(const std::string &name, Type *value)
{
	auto new_ref_global = new LuaDustRefVar<Type>(this, name, value);
	this->_refs.push_back(new_ref_global);
	return new_ref_global;
}
