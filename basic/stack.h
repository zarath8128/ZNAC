#ifndef ZNAC_BASIC_STACK_H
#define ZNAC_BASIC_STACK_H

#include <utility>

namespace ZNAC
{
	template<class T>
	class Arrow
	{
	public:
		Arrow* next;
		T data;

		Arrow(T &&t):next(nullptr), data(t){}
		Arrow(T &&t, Arrow *next):next(next), data(t){}
		~Arrow(){delete next;}
	};

	template<class T>
	class Stack
	{
	public:
		Stack():top(nullptr){}
		~Stack(){delete top;}

		void Push(T &&t){top = new Arrow<T>(std::move(t), top);}
		T &&Pop(){T&& t = std::move(top->data); top = top->next; return std::move(t);}
	private:
		Arrow<T> *top;
	};
}

#endif
