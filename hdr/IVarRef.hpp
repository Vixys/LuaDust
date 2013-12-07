#ifndef I_VAR_REF_HPP
#define I_VAR_REF_HPP

#include <string>

namespace LuaDust
{
	class IVarRef
	{
		public:
			virtual ~IVarRef() { }

			virtual const std::string &getName() const = 0;
			virtual std::string getStringValue(bool codeStyle = false) const = 0;

		protected:

			friend class LuaDust;

			virtual void updateRef() = 0;
			virtual void pushRef() = 0;

	};
} // End LuaDust namespace

#endif // I_VAR_REF_HPP
