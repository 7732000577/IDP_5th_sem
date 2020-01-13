#include <stdio.h>
#include <math.h>
#define PI 3.14159

void print_array(double A[], long int A_size)
{
	long int i;
	for(i = 0; i < A_size; i++)
	{
		printf("%lf", A[i]);
		printf("\n");
	}
	
	return;
}

void scan(double A[],long int A_size)
{
    long int i;
    for(i = 0; i < A_size; i++)
	{
		scanf("%lf", &A[i]);
	}
	return ;
}

void window_generator(double arr[], long int N)
{
	
	for(long int i=0;i<N;i++)
	{	
		arr[i] = 0.54 - 0.46*cos((2*PI*i)/(N-1));  //generating window array
	}
}

void sinc_generator_lpf(double sinc_lpf[] , long int size, double omega)
	{
		
		long int mid = size/2;
		
		for(long int i=0;i<size;i++)
		{
			if(i== mid)
				sinc_lpf[i] = omega/PI;
			else
				sinc_lpf[i] = sin(omega*(i-mid))/(PI*(i-mid));
		}
	}


void LPF(double arr[], long int N, double omega)
	{
		long int mid = N/2;
		double window_hamming[N], sinc_lpf[N] ;
		for(long int i=0;i<N;i++)
			arr[i] = 0;
		
		window_generator(window_hamming, N);
		sinc_generator_lpf(sinc_lpf, N, omega);

		for(long int i=0;i<N;i++)
			arr[i] = sinc_lpf[i]*window_hamming[i];
		
		return;
	}

void sinc_generator_hpf(double sinc_hpf[] , long int size, double omega)
	{
		
		long int mid = size/2;
		
		for(long int i=0;i<size;i++)
		{
			if(i== mid)
				sinc_hpf[i] = 1 - omega/PI;
			else
				sinc_hpf[i] = (sin(PI*(i-mid)) - sin(omega*(i-mid)))/(PI*(i-mid));
		}
	}

void HPF(double arr[], long int N, double omega)
	{
		long int mid = N/2;
		double window_hamming[N], sinc_hpf[N] ;
		for(long int i=0;i<N;i++)
			arr[i] = 0;
		
		window_generator(window_hamming, N);
		sinc_generator_hpf(sinc_hpf, N, omega);

		for(long int i=0;i<N;i++)
			arr[i] = sinc_hpf[i]*window_hamming[i];
		arr[mid] = omega/PI;

		return;
	}

void sinc_generator_bpf(double sinc_bpf[] , long int size, double omega1,double omega2)
	{
		
		long int mid = size/2;
		
		for(long int i=0;i<size;i++)
		{
			if(i== mid)
				sinc_bpf[i] = (omega2 - omega1)/PI;
			else
				sinc_bpf[i] = (sin(omega2*(i-mid)) - sin(omega1*(i-mid)))/(PI*(i-mid));
		}
	}

void BPF(double arr[], long int N, double omega1, double omega2)
	{
		long int mid = N/2;
		double window_hamming[N], sinc_bpf[N] ;
		for(long int i=0;i<N;i++)
			arr[i] = 0;
		
		window_generator(window_hamming, N);
		sinc_generator_bpf(sinc_bpf, N, omega1,omega2);

		for(long int i=0;i<N;i++)
			arr[i] = sinc_bpf[i]*window_hamming[i];
		return;	
	}

void Moving_average_filter(long int l,double arr[],long int size,double mvf[])
{

	long int i,j;
	for(j = 0;j<size;j++)
	{
		mvf[j]=0;
	}
	for(j = 0;j<size;j++)
	{
		for(i=0 ; i<l ; i++)
		{
			if (j-i>=0)
				mvf[j]+=arr[j-i];
		}

		mvf[j] = mvf[j]/l;
	}
	return;
}