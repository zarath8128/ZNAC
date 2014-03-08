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

	template<class T>
	class IWrapper
	{
	public:
		IWrapper():buf(0){}
		IWrapper(T &t):buf(&t){}

		operator T&(){return *buf;}
		void Set(T &b){buf = &b;}
		
	protected:
		T *buf;

	};

	template<class T>
	constexpr const T &MAX(const T &a, const T &b){return ((a < b)?(b):(a));}

	template<class T>
	constexpr const T &MIN(const T &a, const T &b){return ((a > b)?(b):(a));}

	template<class T>
	constexpr T ABS(const T &a){return ((a < 0)?(-a):(a));}

	template<class T>
	constexpr int SIGN(const T &a){return ((a < 0)?(-1):(1));}
}

#endif
