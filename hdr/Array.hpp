#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <array>
#include <sstream>
#include <type_traits>

#include "IVarRef.hpp"
#include "LuaDustException.hpp"

namespace LuaDust
{
	template <typename ContainerType>
	class Array : public IVarRef
	{
		typedef typename ContainerType::value_type ValueType;

		public:
			Array(LuaDust *dust, const std::string &name, ContainerType *container);
			~Array();

			virtual const std::string &getName() const;

			virtual std::string getStringValue(bool) const;

		protected:
			virtual void updateRef();
			virtual void pushRef();

			LuaDust *_dust;
			std::string _name;
			ContainerType *_ref;
	};

	#include "Array.inl"
} // End LuaDust namespace

#endif // ARRAY_HPP