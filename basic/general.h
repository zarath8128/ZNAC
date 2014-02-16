#ifndef ZARATH_ZNAC_BASIC_GENERAL_H
#define ZARATH_ZNAC_BASIC_GENERAL_H

namespace ZNAC
{
	template<class T>
	class IClonable
	{
	public:
		constexpr virtual T *Clone() = 0;
	};
}

#endif
