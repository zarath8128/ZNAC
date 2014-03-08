#ifndef ZARATH_ZNAC_GPGPU_CUDA_CUDA_UTILITY_H
#define ZARATH_ZNAC_GPGPU_CUDA_CUDA_UTILITY_H

#include <iostream>
#include "cuda_runtime.h"

namespace ZNAC
{
	namespace CUDA
	{
		cudaError_t CCALL(cudaError_t err);

		class cudaDevice
		{
		public:
			cudaDevice(unsigned int i);
			const cudaDeviceProp &Property();
			operator bool() const;

			static unsigned int Count(){int c;CCALL(cudaGetDeviceCount(&c));return c;}

		private:
			cudaDeviceProp prop;
			bool IsEnable;
		};

		template<class T>
		class cudaBuffer
		{
		public:
			const unsigned int dim;

			cudaBuffer(unsigned int dim):dim(dim), buf(0), err(cudaSuccess), IsEnable((err = CCALL(cudaMalloc(&buf, dim*sizeof(T)))) == cudaSuccess){}
			~cudaBuffer(){CCALL(cudaFree(buf));}
			cudaError_t operator=(T *v){if(IsEnable)return CCALL(cudaMemcpy(buf, v, dim*sizeof(T), cudaMemcpyHostToDevice));return err;}
			cudaError_t operator<<(T *v){if(IsEnable)return CCALL(cudaMemcpy(buf, v, dim*sizeof(T), cudaMemcpyHostToDevice));return err;}
			cudaError_t operator>>(T *v){if(IsEnable)return CCALL(cudaMemcpy(v, buf, dim*sizeof(T), cudaMemcpyDeviceToHost));return err;}
			operator bool()const{return IsEnable;}
			operator T*()const{return buf;}
		private:
			T *buf;
			cudaError_t err;
			bool IsEnable;
		};


		/* Cuda Matrix-Vector Multiplication Sample */

	/*	template<class T>
		__global__ void mat_mul_vec(T *ans, T *mat, T *vec)
		{
			const unsigned int dim = gridDim.x;
			const unsigned int count = dim/blockDim.x;
			const unsigned int row = blockIdx.x;
			extern __shared__ T buf[];
			buf[threadIdx.x] = 0;

			for(unsigned int i = 0; i < count; ++i)
				buf[threadIdx.x] += mat[row*dim + i*blockDim.x + threadIdx.x]*vec[i*blockDim.x + threadIdx.x];

			for(unsigned int i = 2; i <= blockDim.x; i <<= 1)
			{
				__syncthreads();
				if(threadIdx.x < blockDim.x/i)
					buf[threadIdx.x] += buf[threadIdx.x + blockDim.x/i];
			}
			if(threadIdx.x == 0)
				ans[row] = buf[0];
		}*/

	}
}

#endif