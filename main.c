#include <stdio.h>
#include <stdlib.h>

int n = 4;
double *x, *y, *X, *Y, eps = 0.1;
const double N = 4;

double func(double x)
{
	return x * x;
}

double del[6][7] = {0};

int Del(double xn)
{

int i, j;
	for (i = 0; i < 6; i++){
		del[i][0] = X[i];
		del[i][1] = Y[i];
	}
	for (i = 2; i < 5; i++){
		for (j = 0; j < n / 2 - i + 2; j ++){
			del[j][i] = del[j + 1][i - 1] - del[j][i - 1];
		}
	}		
}

double q(int k, double xn)
{
	if (k == 0)
		return 1;
	double q = xn - X[0];
	int i;
	for (i = 1; i <  k; i++){
		q *= xn - X[0] - i;
	} 
}

int fact(int k)
{
int i, p = 1;
	if (n == 0)
		return 1;
	for ( i = k; i > 1; i--)
		p *= k;
	return p;
}

double intNewton(double xn){
	double p;
	int i, j;
	Del(xn);
	
	for (i = 0; i < 4 + 1; i++){
		p += del[0][i + 1] * q(i, xn) / fact(i);
		//printf("p = %.3f i =  %d\n", p, i);
	}
	return p;
}

double init()
{
	for (int i = 0; i <= N; i++){
		X[i] = x[i] = i;
		Y[i] = y[i] = func(x[i]);
	}
}


double Simpson()
{
double I = 0, I2n = 0, h = 0, k = 0;
	x = (double *)malloc(sizeof(double) * n * 2);
	y = (double *)malloc(sizeof(double) * n * 2);
	X = (double *)malloc(sizeof(double) * N);
	Y = (double *)malloc(sizeof(double) * N);
	n = N;
	init();
		h = (x[n] - x[0]) / n;
		
	for (int i = 1; i <= n - 1; i = i + 2){
		I += 4 * y[i];
	}
	
	for (int i = 2; i <= n - 2; i = i + 2){
		I += 2 * y[i];
	}
	I += (y[0] + y[n]);
	I = I * h / 3;
	printf("I = %.3f\n", I);
		
	for (k = 0; (I - I2n) / 3 > eps; k++){
		n *= 2;
		if (k > 0){
			x = realloc(x, sizeof(double) * n);
			y = realloc(y, sizeof(double) * n);
			I = I2n;
		}
		
		for (int i = 0; i <= n; i++){
			
			x[i] = i * h / 2;
			y[i] = func(x[i]);
			
		}
		
		h = (x[n] - x[0]) / n;
		I2n = 0;
		for (int i = 1; i <= n - 1; i = i + 2){
			I2n += 4 * y[i];
		}
	
		for (int i = 2; i <= n - 2; i = i + 2){
			I2n += 2 * y[i];
		}
		I2n += (y[0] + y[n]);
		I2n = I2n * (h / 3);
		printf("I2n = %.3f\n", I2n);
		k++;
	}
	return I2n;
}

double integ()
{
double I, I2n, h, k = 0;
	x = (double *)malloc(sizeof(double) * n * 2);
	y = (double *)malloc(sizeof(double) * n * 2);
	X = (double *)malloc(sizeof(double) * N);
	Y = (double *)malloc(sizeof(double) * N);

	init();
		h = (x[n] - x[0]) / n;
		
	for (int i = 1; i <= n - 1; i++){
		I += y[i];
	}
	I += (y[0] + y[n]) / 2;
	I = I * h;
	printf("I = %.3f\n", I);
		
	for (k = 0; (I - I2n) / 3 > eps; k++){
		n *= 2;
		if (k > 0){
			x = realloc(x, sizeof(double) * n);
			y = realloc(y, sizeof(double) * n);
			I = I2n;
		}
		
		for (int i = 0; i <= n; i++){
			
			x[i] = i * h / 2;
			y[i] = func(x[i]);
			
		}
		
		h = (x[n] - x[0]) / n;
		I2n = 0;
		for (int i = 1; i <= n - 1; i++){
			I2n += y[i];
		}
		I2n += (y[0] + y[n]) / 2;
		I2n = I2n * h;
		printf("I2n = %.3f\n", I2n);
		k++;
	}
	return I2n;
}

int main()
{
	printf("\nФормула трапеции: \n");
	integ();	
	printf("Формула Симпсона: \n");
	Simpson();
	printf("\nx: ");
	for (int i = 0; i <= N; i++)
		printf("%.2f  ", X[i]);
	printf("\n");
	
	printf("y: ");
	for (int i = 0; i <= N; i++)
		printf("%.2f  ", Y[i]);
	printf("\n");

	
	
return 0;
}
