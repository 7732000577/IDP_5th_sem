#include <stdio.h> 
#include <math.h>
#include "common_functions.h"

int main()
{
	int i,size,a;
	scanf("%d",&size);
	a = pow(2,ceil(log2(size)));
	struct Complex x[a],output_fft[a],output_ifft[a];
	for(i=0;i<a;i++)
	{
		if(i < size)
		{
			double p,q;
			scanf("%lf %lf",&p,&q);
			x[i].real = p;
			x[i].imag = q;	
		}
		else
		{
			x[i].real = 0;
			x[i].imag = 0;
		}
	}
	printf("input\n");
	print(x, a);

	fft(output_fft,x,a);
	ifft(output_ifft, output_fft, a);

	printf("fft\n");
	print(output_fft, a);

	printf("ifft\n");
	print(output_ifft, a);
	return 0;
}