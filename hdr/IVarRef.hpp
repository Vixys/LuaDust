#ifndef I_VAR_REF_HPP
#define I_VAR_REF_HPP

#include <string>

namespace LuaDust
{
	/**
	 * Represent the base of a reference on a lua variable.
	 */
	class IVarRef
	{
		public:
			/**
			 * Destructor
			 */
			virtual ~IVarRef() { }

			/**
			 * Return the var name in the lua state.
			 * @return String of the name
			 */
			virtual const std::string &getName() const = 0;

			/**
			 * Return the value of the lua variavle as a string.
			 * @param  codeStyle If true the string value will be in code style
			 * @return           Variable value as string
			 */
			virtual std::string getStringValue(bool codeStyle = false) const = 0;

		protected:

			friend class LuaDust;

			/**
			 * Update the value of the c++ reference.

			 * This method is called after every code execution. (LuaDust::doString & LuaDust::doFile)
			 */
			virtual void updateRef() = 0;

			/**
			 * Update the vcalue of the lua referemce
			 *
			 * This method is called before every code execution. (LuaDust::doString & LuaDust::doFile)
			 */
			virtual void pushRef() = 0;

	};
} // End LuaDust namespace

#endif // I_VAR_REF_HPP
