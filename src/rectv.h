//#include <cuda_runtime.h>
#include "radonusfft.h"

class rectv
{
	//parameters
	size_t N;
	size_t Ntheta;
	size_t M;
	size_t Nz;
	size_t Nzp;
	size_t Nrot;
	float tau;
	float lambda0;
	float lambda1;

	//number of gpus
	size_t ngpus;

	//class for applying Radon transform
	radonusfft** rad;

	//vars
	float *f;
	float *fn;
	float *ft;
	float *ftn;
	float *g;
	float *h1;
	float4 *h2;
	float **theta;
	float2 **phi;

	//temporary arrays on gpus
	float **ftmp;
	float **gtmp;
	float **ftmps;
	float **gtmps;

	void radonapr(float *g, float* f, int igpu);
	void radonapradj(float *f, float* g, int igpu);
	void gradient(float4 *g, float* f, int iz, int igpu);
	void divergent(float *fn, float* f, float4* g, int igpu);	
	void prox(float *h1, float4* h2, float *g, int igpu);	
	void updateft(float* ftn, float* fn, float* f, int igpu);
	void radonfbp(float *f, float* g, int igpu);

  public:
	rectv(size_t N, size_t Ntheta, size_t M, size_t Nrot, size_t Nz, size_t Nzp,
		  size_t ngpus, float lambda0, float lambda1);
	~rectv();
	void itertvR(float *fres, float *g, size_t niter);
};
