#include <stdio.h>
#include <stdlib.h>

double** ler(const char *nomeArq, int *d)
{
	int i, j, dim;
	double **M, a;
	FILE *arq;
    
    arq = fopen(nomeArq, "r");
	i = fscanf(arq,"%d",&dim);
	M = malloc( dim*sizeof(double *));
	for( i = 0 ; i < dim ; i++ )
		M[i] = (double *) malloc((dim+1)*sizeof(double));
	
	i=j=0;
	while (fscanf(arq,"%lf",&a) != EOF) 
	{
		M[i][j] = a;
		j++;
		if (j == dim+1)
		{
			j = 0;
			i++;
		}
	}
	*d=dim;
	return M;
}

void imprime(double **M, int var)
{
	
	int i, j;
	
	for(i=0;i<var;i++) 
	{
		for(j=0;j<var+1;j++)  
			printf("%.0lf\t",M[i][j]);
			  
		puts("");
	}
}

void triangsup(double **M, int dim) 
{
	int i, j, k;
	double lamb;
	i=j=0;
	
	puts("\nMatriz triangularizada:");
	
	for(j=0; j<dim; j++)
	{
		for(i=j; i<dim-1; i++) 
		{
			lamb=M[i+1][j]/M[j][j];
			for(k=j; k<dim+1; k++)
			{
				M[i+1][k] = M[i+1][k] - (lamb)*M[j][k];
			}
		}
	}
}

void subsreversa (double **M, double *raizes, int dim)
{
	int i, j;
	double soma=0;
	
	
	for(i=dim-1; i>=0; i--)
	{
		raizes[i] = M[i][dim];
		
		for(j=dim; j>=i+1; j--)
			raizes[i]-=M[i][j]*raizes[j];
			
		raizes[i]/=M[i][i];
	}
}
	
	

		

main(int argc, char **argv) {
	double **M;

	double *raizes;

	int i, dim;
	
	M=ler(argv[1], &dim);

	imprime(M,dim);
	triangsup(M,dim);
	imprime(M,dim);
	
	raizes = malloc(dim*sizeof(double));
	subsreversa(M,raizes,dim);
	
	puts("Raizes\n\n");
	
	for(i=0; i<dim; i++)
		printf("x%d = %5.2lf\t", i, raizes[i]);
		
	printf("\n\n");
	
}
