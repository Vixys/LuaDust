#ifndef LUA_DUST_REF_VAR_HPP
#define LUA_DUST_REF_VAR_HPP

#include "LuaDustRef.hpp"

template <typename Type>
class LuaDustRefVar : public LuaDustRef
{
	public:
		LuaDustRefVar(LuaDust *dust, const std::string &name, Type *ref);

		void updateRef();
		void pushRef();

		const std::string &getName() const
		{
			return this->_name;
		}

		const void *getRefPtr() const
		{
			return this->_ref;
		}

	private:

		Type *_ref;
		std::string _name;
		LuaDust *_dust;
};

#include "LuaDustRefVar.inl"

#endif // LUA_DUST_REF_VAR_HPP