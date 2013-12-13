#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <array>
#include <sstream>
#include <type_traits>

#include "IVarRef.hpp"
#include "LuaDustException.hpp"

namespace LuaDust
{
	/**
	 * Represent a Lua basic array in C++
	 */
	template <typename ContainerType>
	class Array : public IVarRef
	{
		typedef typename ContainerType::value_type ValueType;

		public:
			/**
			 * Constructor
			 *
			 * \param dust Pointer to the lua state/
			 * \param name Lua var name
			 * \param container C++ container. Use to initiate the lua array value. 
			 */
			Array(LuaDust *dust, const std::string &name, ContainerType *container);

			/**
			 * Destructor
			 */
			~Array();

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
			ContainerType *_ref;
	};

	#include "Array.inl"
} // End LuaDust namespace

#endif // ARRAY_HPP