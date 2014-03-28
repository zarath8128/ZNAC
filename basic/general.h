#ifndef ZARATH_ZNAC_BASIC_GENERAL_H
#define ZARATH_ZNAC_BASIC_GENERAL_H

#include <utility>
#include <typeinfo>
#include <cxxabi.h>
#include <iostream>

#define DEBUG_MSG(...) printf("\n/*----debug message----*/\n\nfile:" __FILE__ "\nline:%d\ndate:" __DATE__ "\n\nmessage is below:\n", __LINE__), printf("" __VA_ARGS__), printf("\n/*---- message end ----*/\n\n")

namespace ZNAC
{
	template<class T>
	class IClonable
	{
	public:
		virtual T *Clone() = 0;
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
	class ReadBuffer
	{
	public:
		const unsigned int &Used;
		ReadBuffer():ReadBuffer(16){}
		ReadBuffer(unsigned int n):Used(used), buffer(new T[n]), used(0), reserved(n)
		{
		}
		ReadBuffer(const ReadBuffer &r) = delete;
		ReadBuffer(ReadBuffer &&r):Used(used), buffer(r.buffer), used(r.used), reserved(r.reserved)
		{
			r.buffer = nullptr;
		}

		~ReadBuffer(){
			delete [] buffer;
		}

		void operator<<(const T &t){Check(); 
			buffer[used++] = t;
		}
		void operator<<(T &&t){Check();
		       	buffer[used++] = t;
		}

		ReadBuffer &operator=(const ReadBuffer &) = delete;
		ReadBuffer &operator=(ReadBuffer &&r)
		{
			used = r.used;
			r.used = 0;
			reserved = r.reserved;
			r.reserved = 0;
			delete [] buffer;
			buffer = r.buffer;
			r.buffer = nullptr;
		}

		T &operator[](unsigned int i){return buffer[i];}

		void Clear(){used = 0;}

	private:
		T *buffer;
		unsigned int used;
		unsigned int reserved;

		void Check()
		{
			if(used == reserved)
			{
				T *temp = new T[reserved *= 2];
				for(unsigned int i = 0; i < used; ++i)
					temp[i] = std::move(buffer[i]);
				delete [] buffer;
				buffer = temp;
			}
		}
	};

	template<unsigned int dim, class T = double>
	class Vector
	{
	public:
		Vector() = default;

		Vector &operator=(const Vector &v) = default;
		
		T &operator[](unsigned int i){return buf[i];}

	protected:
		T buf[dim];
	};

	template<class T>
	constexpr const T &MAX(const T &a, const T &b){return ((a < b)?(b):(a));}

	template<class T>
	constexpr const T &MIN(const T &a, const T &b){return ((a > b)?(b):(a));}

	template<class T>
	constexpr T ABS(const T &a){return ((a < 0)?(-a):(a));}

	template<class T>
	constexpr int SIGN(const T &a){return ((a < 0)?(-1):(1));}

	template<class T>
	const char *CLASS_NAME(const T &t){int dammy;const std::type_info & id = typeid(t);return abi::__cxa_demangle(id.name(), 0, 0, &dammy);}
}

#endif
