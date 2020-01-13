#include <stdio.h> 
#include <math.h>

struct Complex{
	double real;
	double imag;
};

struct Complex add(struct Complex n1,struct Complex n2)
{
  struct Complex temp;
  temp.real = n1.real + n2.real;
  temp.imag = n1.imag + n2.imag;
  return(temp);
}

struct Complex sub(struct Complex n1,struct  Complex n2)
{
  struct Complex temp;
  temp.real = n1.real - n2.real;
  temp.imag = n1.imag - n2.imag;
  return(temp);
}

struct Complex multi(struct Complex n1,struct  Complex n2)
{
  struct Complex temp;
  temp.real = n1.real*n2.real - n1.imag*n2.imag;
  temp.imag = n1.imag*n2.real + n2.imag*n1.real;
  return(temp);
}

void print(struct Complex temp[], int a)
{
	int i = 0;
	printf("\n");
	for(i = 0; i < a; i++)
	{
		printf("z = %.1f%+.1fi\n", (temp[i].real), (temp[i].imag));
	}
	printf("\n");
}

void even_elements(struct Complex arr[],struct Complex output2[],int size)
{
	int i,j = 0;
	for(i=0;i<size;i+=2,j++)
		output2[j] = arr[i];
}

void odd_elements(struct Complex arr[],struct Complex output2[],int size)
{
	int i,j = 0;
	for(i=1;i<size;i+=2,j++)
		output2[j] = arr[i];
}

void fft(struct Complex output_fft[], struct Complex x[], int a)
{
	if(a == 1)
		output_fft[0] = x[0];
	else
	{
		struct Complex input_even[a/2],input_odd[a/2],output1[a/2],output2[a/2];
		double PI = acos(-1);

		even_elements(x ,input_even, a);
		odd_elements(x, input_odd, a);

		fft(output1,input_even,a/2);
		fft(output2,input_odd,a/2);

		int index=0,loop,i;
		for(loop = 0; loop < a/2; loop++)
		{
     		output_fft[index] = output1[loop];
     		index++; 
 		}
   		for(loop = 0; loop < a/2; loop++)
   		{
      		output_fft[index] = output2[loop];
      		index++;
        }

        int k;
        for(k=0;k<(a/2);k++)
		{		
			struct Complex t = output_fft[k];
			struct Complex n2,result1,result2,result3;
			n2.real = cos(-2*PI*k/a);
			n2.imag = sin(-2*PI*k/a);

			result1 = multi(n2, output_fft[k+(a/2)]);
			result2 = add(t, result1);
			result3 = sub(t, result1);
			output_fft[k] = result2;
			output_fft[k+(a/2)] = result3;
		}
	}
}

void ifft(struct Complex output_ifft[], struct Complex x[], int a)
{
	if(a == 1)
		output_ifft[0] = x[0];
	else
	{
		struct Complex input_even[a/2],input_odd[a/2],output1[a/2],output2[a/2];
		double PI = acos(-1);

		even_elements(x ,input_even, a);
		odd_elements(x, input_odd, a);
	
		ifft(output1,input_even,a/2);
		ifft(output2,input_odd,a/2);

		int index=0,loop,i;
		for(loop = 0; loop < a/2; loop++)
		{
     		output_ifft[index] = output1[loop];
     		index++; 
 		}
   		for(loop = 0; loop < a/2; loop++)
   		{
      		output_ifft[index] = output2[loop];
      		index++;
        }

        int k;
        for(k=0;k<(a/2);k++)
		{		
			struct Complex t = output_ifft[k];
			struct Complex n2,result1,result2,result3;
			n2.real = cos(2*PI*k/a);
			n2.imag = sin(2*PI*k/a);

			result1 = multi(n2, output_ifft[k+(a/2)]);
			result2 = add(t, result1);
			result3 = sub(t, result1);
			output_ifft[k] = result2;
			output_ifft[k+(a/2)] = result3;
		}

		for(k = 0; k < a; k++)
		{
			output_ifft[k].real = output_ifft[k].real / 2;
			output_ifft[k].imag = output_ifft[k].imag / 2;
		}
	}
}
