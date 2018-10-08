#include <stdio.h>

//=======================================================
const int READERROR=-1;
const	int	EMPTY=0;
const	int EMPTYDATA=-2;
const	int	WRITEERROR=-3;
const	int	MaxDataSize=1000;//max. number of measurements

//=========================================================
int ReadData(double U[],double I[]);
int ComputeResistance(double U[],double I[],double R[],int nline);
int WriteResults(double R[],int nline);

//=========================================================
int main()
{
double R[MaxDataSize]={};//Resistance array
double U[MaxDataSize]={};//Voltage array
double I[MaxDataSize]={};//Amperage array
double r_LSM=0;//Resistance which is computed with Least Squares Method
int nline=0;//number of measurements

//............................................................
{
	if (ReadData(U,I)==READERROR) return READERROR;
	if (ReadData(U,I)==EMPTY) 	  return EMPTYDATA;
	nline=ReadData(U,I);
}

ComputeResistance(U,I,R,nline);

if (WriteResults(R,nline)==WRITEERROR) return WRITEERROR;

printf("Hope you'll have 'perfect'(10) for this laboratory work\n");
return 0;
}

//=================================================================

int ReadData(double U[],double I[])
{
	FILE*file=fopen("Data.txt", "r");
	if (!file)
		{
			printf("Can not open Data.txt\n");
		  return READERROR;
	  }
	int line=0;
	for(;;)
		{
			if (fscanf(file,"%lg %lg",&U[line+1],&I[line+1])==EOF) break;
			line++;
		}
	fclose(file);
	return line;
}

int ComputeResistance(double U[],double I[],double R[],int nline)
{
	for(int line=0;;)
	{
		line++;
		if (line>nline) break;
		R[line]=U[line]/I[line];
	}
}


int WriteResults(double R[],int nline)
{
	FILE*file=fopen("Results.txt","w");
	if (!file)
	{
		printf("Can not open Results.txt");
		return WRITEERROR;
	}
	int line=0;
	for(;;)
	{
		line++;
		if (line>nline) break;
		fprintf(file, "%lg\n",R[line]);
	}

}
