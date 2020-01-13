#include <stdio.h>
#include <math.h>
#define PI 3.14159

void print_array(double A[], long int A_size)
{
	long int i;
	for(i = 0; i < A_size; i++)
	{
		printf("%lf ", A[i]);
	}
	printf("\n");
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

void correlation(double A[], long int A_size, double B[], long int B_size,double Correlation[])
{
	long int i;
	for(i = 0; i < B_size; i++)
	{
		long int j;
		for(j = i; j < (i + A_size ); j++)
		{
			Correlation[j] += (A[j - i] * B[A_size - i]);
		}
	}
	return;
}

void convolution(double A[], long int A_size, double B[], long int B_size,double Convolution[],long int final_size)
{
	long int i;
    for(i = 0; i < final_size; i++)
	{
		Convolution[i] = 0;
	}
	for(i = 0; i < B_size; i++)
	{
		long int j;
		for(j = i; j < (i + A_size ); j++)
		{
			Convolution[j] += (A[j - i] * B[i]);
		}
	}
	
	
	return;
}


void modified_convolution(double A[], long int A_size, double B[], long int B_size,double Convolution[],long int final_size)
{
	long int i, a = (A_size-1)/2,b = B_size/2;
    for(i = 0; i < final_size; i++)
	{
		Convolution[i] = 0;
	}
	if (a%2==0)
	{
	    for(i = 1; i < a; i=i+2)
	{
		long int j;
		for(j = i; j < (i + B_size ); j++)
		{
			Convolution[j] += (B[j - i] * A[i]);
			Convolution[A_size+B_size-1-j-1] += (B[B_size-1-(j-i)] * A[i]);
		}
	}
	}
	else
	{
	    for(i = 0; i < a; i=i+2)
	{
		long int j;
		for(j = i; j < (i + B_size ); j++)
		{
			Convolution[j] += (B[j - i] * A[i]);
			Convolution[A_size+B_size-1-j-1] += (B[B_size-1-(j-i)] * A[i]);
		}
	}
	}
	long int k=0;
	for (i = (A_size+B_size-1)/2 - b;i<=(A_size+B_size-1)/2 + b;i++,k++)
	    {
	       
	        Convolution[i]+= A[a]*B[k];
	    }
	return;
}

void window_generator(double arr[], long int N)
{
	
	for(long int i=0;i<N;i++)
	{	
		arr[i] = 0.54 - 0.46*cos((2*PI*i)/(N-1));  //generating window array
	}
}

void sinc_generator(double sinc[] , long int size, double omega)
{
	
	long int mid = size/2;
	
	for(long int i=0;i<size;i++)
	{
		if(i== mid)
			sinc[i] = omega/PI;
		else
			sinc[i] = sin(omega*(i-mid))/(PI*(i-mid));
	}
}

void halfBandFilter(double arr[], long int N, double omega)
{
	long int mid = N/2;
	double window_hamming[N], sinc[N] ;
	for(long int i=0;i<N;i++)
		arr[i] = 0;
	
	window_generator(window_hamming, N);
	sinc_generator(sinc, N, omega);

	for(long int i=0;i<N;i++)
		arr[i] = sinc[i]*window_hamming[i];

	arr[mid] = 0.5;

	return;
	
}

void Down_sampling(double A[], long int A_size, long int rate, double down_sampling[])
{
	long int i, j = 0;
	for(i = 0; i < A_size; i += rate, j++)
	{
		down_sampling[j] = A[i];
	}
	return;
}

void Up_sampling(double A[], long int A_size, long int rate,double up_sampling[])
{
	long int i, j = 0;
	for(i = 0; i < A_size; i++)
	{
		up_sampling[j++] = A[i];
		long int k;
		for(k = 0; k < (rate - 1); k++)
		{
			up_sampling[j++] = 0;
		}
	}
	return;
}

void trim(double arr[], double arr_final[], long int n, long int m)
{
    
    
	long int start = (n-m)/2, i=0;
    for(i = 0; i < m; i++)
	{
		arr_final[i] = 0;
	}
	for(i=0;i<m;i++)
	{
		arr_final[i] = arr[start+i];
	}
}

void Decimation(double Convolution[],double decimation[],long int A_size,double B[],long int B_size)
{
	
	double A[A_size],omega = PI/2;
	halfBandFilter(A,A_size,omega);

	convolution(A, A_size, B, B_size, Convolution,A_size + B_size -1);
	double arr_final[A_size];
    trim(Convolution,arr_final,(A_size + B_size - 1),A_size);

    Down_sampling(arr_final, A_size,2,decimation);
    return;
}

void Decimation_modified(double Convolution[],double decimation_hbf[],long int A_size,double B[],long int B_size)
{

double A[A_size],omega = PI/2;
halfBandFilter(A,A_size,omega);

modified_convolution(A, A_size, B, B_size, Convolution,A_size + B_size -1);
double arr_final[A_size];
trim(Convolution,arr_final,(A_size + B_size - 1),A_size);

Down_sampling(arr_final, A_size,2,decimation_hbf);
return;
}

void Interpolation(double decimation[],double interpolation[],long int A_size,double B[],long int B_size)
{
	
	double A[A_size],omega = PI/2;
	halfBandFilter(A,A_size,omega);

	double arr_final1[(((long int)((A_size - 1) / 2)) + 1)*2];
	Up_sampling(decimation,(((long int)((A_size - 1) / 2)) + 1),2,arr_final1);

	double Convolution[(((long int)((A_size - 1) / 2)) + 1)*2+A_size-1];
	convolution(A, A_size,arr_final1,(((long int)((A_size - 1) / 2)) + 1)*2, Convolution,(((long int)((A_size - 1) / 2)) + 1)*2+A_size-1);

    trim(Convolution,interpolation,(((long int)((A_size - 1) / 2)) + 1)*2+A_size-1,((long int)((A_size - 1) / 2)) + 1);
    return;
}

void Interpolation_modified(double decimation[],double interpolation_hbf[],long int A_size,double B[],long int B_size)
{
	
	double A[A_size],omega = PI/2;
	halfBandFilter(A,A_size,omega);

	double arr_final1[(((long int)((A_size - 1) / 2)) + 1)*2];
	Up_sampling(decimation,(((long int)((A_size - 1) / 2)) + 1),2,arr_final1);

	double Convolution[(((long int)((A_size - 1) / 2)) + 1)*2+A_size-1];
	modified_convolution(A, A_size,arr_final1,(((long int)((A_size - 1) / 2)) + 1)*2, Convolution,(((long int)((A_size - 1) / 2)) + 1)*2+A_size-1);

    trim(Convolution,interpolation_hbf,(((long int)((A_size - 1) / 2)) + 1)*2+A_size-1,((long int)((A_size - 1) / 2)) + 1);
    return;
}

