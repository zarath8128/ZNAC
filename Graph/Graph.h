#ifndef ZARATH_ZNAC_GRAPH_GRAPH_H
#define ZARATH_ZNAC_GRAPH_GRAPH_H

#include "../basic/general.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>

namespace ZNAC
{
	namespace Graph
	{
		template<class T>
		void WriteOut(const char *path, ReadBuffer)
		{

		}

		template<unsigned int dim, class T = double>
		class Vertex
			:public Vector<dim, T>
		{
		public:
			void WriteOut(std::ofstream &ofs)
			{
				ofs.write((char*)&Vector<dim, T>::buf, dim*sizeof(T));
			}

			void ReadIn(std::ifstream &ifs)
			{
				ifs.read((char*)&Vector<dim, T>::buf, dim*sizeof(T));
			}
		};


/*		template<class T>
		class Vertex
			:public ReadBuffer<T>
		{
		public:
			Vertex() = default;
			
			void WriteOut(const char *path)
			{
				std::ofstream ofs(path, std::ios::out | std::ios::binary);
				if(!ofs)
				{
					std::cerr << "Coundn't open file " << path << "\n";
					return;
				}

				uint64_t dim = ReadBuffer<T>::Used;
				uint64_t size = sizeof(T);
				ofs.write((char*)&dim, sizeof(uint64_t));
				ofs.write((char*)&size, sizeof(uint64_t));
				ofs.write(CLASS_NAME((*this)[0]), 1 + strlen(CLASS_NAME((*this)[0])));
				for(unsigned int i = 0; i < ReadBuffer<T>::Used; ++i)
					ofs.write((char*)&(*this)[i], size);
			}

			void ReadIn(const char *path)
			{
				std::ifstream ifs(path, std::ios::in | std::ios::binary);
				if(!ifs)
				{
					std::cerr << "Coudn't open file " << path << "\n";
					return;
				}

				uint64_t dim, dammy;
				char cdammy;
				ReadBuffer<char> c;
				T temp;
				ifs.read((char*)&dim, sizeof(uint64_t));
				ifs.read((char*)&dammy, sizeof(uint64_t));
				do
				{
					ifs.read(&cdammy, 1);
					c << cdammy;
				}while(cdammy);

				char type[c.Used];
				for(unsigned int i = 0; i < c.Used; ++i)
					type[i] = c[i];

				if(strcmp(type, CLASS_NAME(T())))
				{
					std::cerr << "invalid type reading.\nrequired type is \"" << type << "\".\n";
					return;
				}

				for(uint64_t i = 0; i < dim; ++i)
				{
					ifs.read((char*)&temp, sizeof(T));
					*this << temp;
				}
			}
		};

		template<class T>
		class Arrow
			:public ReadBuffer<ReadBuffer<T>>
		{
		public:
			Arrow() = default;

			void WriteOut(const char *path)
			{
				std::ofstream ofs(path, std::ios::out | std::ios::binary);
				if(!ofs)
				{
					std::cerr << "Coundn't open file " << path << "\n";
					return;
				}

				uint64_t dim = ReadBuffer<ReadBuffer<T>>::Used;
				uint64_t size = sizeof(T);
				ofs.write((char*)&dim, sizeof(uint64_t));
				ofs.write((char*)&size, sizeof(uint64_t));
				ofs.write(CLASS_NAME((*this)[0]), 1 + strlen(CLASS_NAME((*this)[0])));
				for(unsigned int i = 0; i < ReadBuffer<ReadBuffer<T>>::Used; ++i)
				{
					dim = (*this)[i].Used;
					ofs.write((char*)&dim, sizeof(uint64_t));
					for(unsigned int j = 0; j < dim; ++j)
						ofs.write((char*)&(*this)[i][j], size);
				}
			}

			Arrow(const char *path):ReadBuffer<ReadBuffer<T>>(0)
			{
				std::ifstream ifs(path, std::ios::in | std::ios::binary);
				if(!ifs)
				{
					std::cerr << "Coudn't open file " << path << "\n";
					return;
				}

				uint64_t dim, dammy;
				char cdammy;
				ReadBuffer<char> c;
				T temp;
				ifs.read((char*)&dim, sizeof(uint64_t));
				ifs.read((char*)&dammy, sizeof(uint64_t));
				do
				{
					ifs.read(&cdammy, 1);
					c << cdammy;
				}while(cdammy);

				char type[c.Used];
				for(unsigned int i = 0; i < c.Used; ++i)
					type[i] = c[i];

				if(strcmp(type, CLASS_NAME(T())))
				{
					std::cerr << "invalid type reading.\nrequired type is \"" << type << "\".\n";
					return;
				}

				for(uint64_t i = 0; i < dim; ++i)
				{
					ifs.read((char*)&dim, sizeof(uint64_t));
					*this << ReadBuffer<T>(0);
					for(unsigned int j = 0; j < dim; ++j)
					{
						ifs.read((char*)&temp, sizeof(T));
						(*this)[i] << temp;
					}
				}
			}
		};*/
	}
}

#endif
