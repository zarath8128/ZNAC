#ifndef ZNAC_BASIC_BUFFER_H
#define ZNAC_BASIC_BUFFER_H

#include <utility>
#include <iostream>

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

		void Push(T &&t){top = new Arrow<T>(std::forward<T>(t), top);}
		T &&Pop(){T&& t = std::forward<T>(top->data); top = top->next; return std::forward<T>(t);}
		bool IsEmpty(){return top == nullptr;}

		void operator << (T &&t){top = new Arrow<T>(std::forward<T>(t), top);}
		void operator >> (T &t){t = std::forward<T>(top->data); Arrow<T>* tmp = top->next; top->next = nullptr; delete top; top = tmp;}
		constexpr operator bool(){return top != nullptr;}
	private:
		Arrow<T> *top;
	};

	template<class T>
	class Chain
	{
	public:
		Chain *next, *prev;
		T data;

		Chain():next(nullptr), prev(nullptr){}
		Chain(T &&t):Chain(std::forward<T>(t), nullptr, nullptr){}
		Chain(T &&t, Chain *next):Chain(std::forward<T>(t), next, nullptr){}
		Chain(T &&t, Chain *next, Chain *prev):next(next), prev(prev), data(t){}
		~Chain(){delete next;}
	};

	template<class T>
	class Queue
	{
	public:
		Queue():top(nullptr), bottom(nullptr){}
		~Queue(){delete top;}

		void Enqueue(T &&t)
		{
			top = new Chain<T>(std::forward<T>(t), top);
			if(top->next != nullptr)
				top->next->prev = top;
			bottom = bottom==nullptr ? top->next : bottom;
		}

		T &&Dequeue()
		{
			T &&t = std::forward<T>(bottom->data);
			bottom = bottom->prev;
			if(bottom != nullptr)
		       		delete bottom->next, bottom->next = nullptr;
		       	return std::forward<T>(t);
		}

		bool IsEmpty(){return bottom == nullptr;}

	private:
		Chain<T> *top, *bottom;
	};

	template<class T>
	class Array
	{
	public:
		const unsigned int &Used;

		Array(unsigned int preserve = 16):Used(used), buf(new T[preserve]), reserved(preserve), used(0){}
		~Array(){delete [] buf;}

		T &operator[](unsigned int i){return buf[i];}
		void Add(unsigned int i, T &&t)
		{
			if(used == reserved)
			{
				T *tmp = new T[reserved *= 2];
				for(unsigned int j = 0; j < used; ++j)
					tmp[j] = buf[j];
				delete [] buf;
				buf = tmp;
			}

			for(unsigned int j = used; j > i; --j)
				buf[j] = buf[j - 1];
			buf[i] = std::forward<T>(t);
			++used;
		}

		void Remove(unsigned int i)
		{
			for(unsigned int j = i + 1; j < used; ++j)
				buf[j - 1] = buf[j];
			--used;
		}

		void operator<<(T &&t){Add(used, std::forward<T>(t));}
		void operator>>(T &t){t = std::forward<T>(buf[--used]);}
	private:
		T *buf;
		unsigned int reserved, used;
	};

	template<class T>
	class bNode
	{
	public:
		bNode *parent, *left, *right;
		T data;

		bNode(T &&t, bNode *parent = nullptr, bNode *left = nullptr, bNode *right = nullptr):parent(parent), left(left), right(right), data(std::forward<T>(t)){}
	};

	template<class T>
	class bTree
	{
	public:
		bTree():root(nullptr){}

		void Add(T &&t)
		{
			bNode<T> *tmp = root;
			if(root == nullptr)
				root = new bNode<T>(std::forward<T>(t));
			else
				while((tmp = Add(std::forward<T>(t), tmp)) != nullptr);
		}

		const T *Get(const T &t)
		{
			return Get(t, root);
		}



	private:
		bNode<T> *root;

		bNode<T> *Add(T &&t, bNode<T> *r)
		{
			if(t < r->data)
				if(r->left == nullptr)
					r->left = new bNode<T>(std::forward<T>(t));
				else
					return r->left;
			else
				if(r->right == nullptr)
					r->right = new bNode<T>(std::forward<T>(t));
				else
					return r->right;
			return nullptr;
		}

		const T *Get(const T &t, bNode<T> *r)
		{
			if(r == nullptr)
				return nullptr;

			if(t == r->data)
				return &r->data;

			if(t < r-> data)
				return Get(t, r->left);
			else
				return Get(t, r->right);

			return nullptr;
		}
	};
}

#endif
