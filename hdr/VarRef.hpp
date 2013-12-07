#ifndef A_VAR_REF_HPP
#define A_VAR_REF_HPP

#include <sstream>
#include <ios>

#include "IVarRef.hpp"


namespace LuaDust
{
	template <typename Type>
	class VarRef : public IVarRef
	{
		public:
			VarRef(LuaDust *dust, const std::string &name, Type *ref);
			virtual ~VarRef();

			virtual const std::string &getName() const;

			virtual std::string getStringValue(bool) const;

		protected:

			virtual void updateRef();
			virtual void pushRef();

			LuaDust *_dust;
			std::string _name;
			Type *_ref;
	};

	#include "VarRef.inl"
} // End LuaDust namespace

#endif // A_VAR_REF_HPP