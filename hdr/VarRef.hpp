#ifndef A_VAR_REF_HPP
#define A_VAR_REF_HPP

#include <sstream>
#include <ios>

#include "IVarRef.hpp"


namespace LuaDust
{
	/**
	 * Represent a c++ reference in lua.
	 */
	template <typename Type>
	class VarRef : public IVarRef
	{
		public:
			/**
			 * Constrictor
			 *
			 * \param dust Lua state
			 * \param name Lua variable name
			 * \param ref Reference to the c++ variable
			 */
			VarRef(LuaDust *dust, const std::string &name, Type *ref);

			/**
			 * Desctructor
			 */
			virtual ~VarRef();

			/**
			 * @copydoc IVarRef::getName
			 */
			virtual const std::string &getName() const;

			/**
			 * @copydoc IVarRef::getStringValue
			 */
			virtual std::string getStringValue(bool) const;

		protected:

			/**
			 * @copydoc IVarRef::updateRef
			 */
			virtual void updateRef();
			/**
			 * @copydoc IVarRef::pushRef
			 */
			virtual void pushRef();

			LuaDust *_dust;
			std::string _name;
			Type *_ref;
	};

	#include "VarRef.inl"
} // End LuaDust namespace

#endif // A_VAR_REF_HPP