#ifndef ZARATH_ZNAC_BASIC_GENERAL_H
#define ZARATH_ZNAC_BASIC_GENERAL_H

#include <utility>
#include <typeinfo>
#include <cxxabi.h>
#include <iostream>
#include "../LA/Vector.h"

#define DEBUG_MSG(...) printf("\n/*----debug message----*/\n\nfile:" __FILE__ "\nline:%d\ndate:" __DATE__ "\n\nmessage is below:\n", __LINE__), printf("" __VA_ARGS__), printf("\n/*---- message end ----*/\n\n")

namespace ZNAC
{
	template<class T>
	constexpr const T &MAX(const T &a, const T &b){return ((a < b)?(b):(a));}

	template<class T>
	constexpr const T &MIN(const T &a, const T &b){return ((a > b)?(b):(a));}

	template<class T>
	constexpr T ABS(const T &a){return ((a < 0)?(-a):(a));}

	template<class T>
	constexpr int SIGN(const T &a){return ((a < 0)?(-1):(1));}

	template<class T>
	void SWAP(T &a, T &b)
	{
		T c = a;
		a = b;
		b = c;
	}

	template<class T>
	const char *CLASS_NAME(const T &t){int dammy;const std::type_info & id = typeid(t);return abi::__cxa_demangle(id.name(), 0, 0, &dammy);}

	template<class T, class... TT>
	struct TemplateCount{constexpr operator unsigned int(){return TemplateCount<TT...>() + 1;}};
	template<class T>
	struct TemplateCount<T>{constexpr operator unsigned int(){return 1;}};

	template<class... TT>
	class FlexibleIndex
		:public LA::IVector<unsigned int>
	{
	public:

		template<class... Args>
		FlexibleIndex(unsigned int val, const Args&... args):FlexibleIndex(args...){Max[--n] = val, buf[n] = 0;}
		unsigned int &operator[](unsigned int i){return buf[i];}
		const unsigned int &operator[](unsigned int i) const {return buf[i];}
		const unsigned int * const &MAX(){return Max;}
		constexpr unsigned int N() const {return TemplateCount<TT...>();}
		constexpr operator unsigned int() {return LinearIndex();}
		constexpr unsigned int operator()(TT... args){return Index(0, args...);}

	private:
		unsigned int buf[TemplateCount<TT...>()];
		unsigned int Max[TemplateCount<TT...>()];
		unsigned int n;

		FlexibleIndex(unsigned int val):n(TemplateCount<TT...>() - 1){Max[n] = val, buf[n] = 0;}
		constexpr unsigned int LinearIndex(){return LinearIndex(0);}
		constexpr unsigned int LinearIndex(unsigned int i){return i != TemplateCount<TT...>()?LinearIndex(i + 1)*Max[i] + buf[i]:0;}
		template<class...Args>
		constexpr unsigned int Index(unsigned int i, unsigned int n, Args... args){return Index(i + 1, args...)*Max[i] + n;}
		constexpr unsigned int Index(unsigned int i, unsigned int n){return 0*i + n;}
	};

	template<class... TT>
	FlexibleIndex<TT...> Index(TT... args){return FlexibleIndex<TT...>(args...);}

}

#endif
