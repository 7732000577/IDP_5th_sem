#include <stdio.h> 
#include <string.h>
#include <math.h>
//#include <complex.h>

typedef struct Complex{

	double real;
	double imag;
} Complex;

Complex add(Complex n1, Complex n2)
{
  Complex temp;
  temp.real = n1.real + n2.real;
  temp.imag = n1.imag + n2.imag;
  return(temp);
}


Complex multi(Complex n1, Complex n2)
{
  Complex temp;
  temp.real = n1.real*n2.real - n1.imag*n2.imag;
  temp.imag = n1.imag*n2.real + n2.imag*n1.real;
  return(temp);
}


int main()
{
	double PI = acos(-1);
	// long int n,i,a,m;
	// scanf("%ld",&n);

	// double input[n],b;
	// for(i=0;i<n;i++)
	// {
	// 	scanf("%lf",&input[i]);
	// }		
	// printf("\n");

	// b = log2(n);
	// a = pow(2,ceil(b));

	// double padding_array[a];

	// for(i=0;i<a;i++)
	// {
	// 	if (i<n)
	// 		padding_array[i] = input[i];
	// 	else
	// 		padding_array[i] = 0;
	// }

	// for(i=0;i<a;i++)
	// {
	// 	printf("%lf ",padding_array[i]);
	// }
	// printf("\n");


    //double complex z;//z = cexp(I * PI) * cexp(I*PI)*5*I;
    // scanf("%lf ",&r);
    // scanf("%lf",&s);
    Complex array[4];
    double arr_real[] = {1,2,3,4},arr_imag[] = {0,0,0,0};
    for (int i = 0; i < 4; ++i)
    {
    	array[i].real = arr_real[i];
    	array[i].imag = arr_imag[i];
    }

    for (int i = 0; i < 4; ++i)
    {
    	printf("z = %.1f%+.1fi\n",array[i].real, array[i].imag);
    }

    return 0;
}