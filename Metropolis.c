#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double targetDistrib(double x){//Define target distribution up to a constant. 
	double y;
	y=x*exp(-2*x);
return y;	
}

double proposalDistrib(double x){//Sample from a proposal distribution. I chose the uniform distribution U(x-1.5,x+1.5) using a pseudo-RNG.
	double y;
	y=rand()%3000000;
	y=y/1000000.0;
	y=x-1.5+y;
return y;
}

void SampleGenerator(double initVal, int *Samplesize, double *Sample){//Generate samples from target distribution.
	double proposal;//Define proposal constant.
	double distribRatio;//Define the ratio of distributions (see below). This will be the acceptance probability for our proposal.
	double RandomNumb;//A (pseudo) random number between 0 and 1 that will help us decide if our proposal gets accepted.
	for(int i = 0;i<Samplesize[0];i++){
		proposal = proposalDistrib(initVal);//Generate proposal using the proposal distribution.
		if(targetDistrib(initVal)>0){//Do not divide by 0...
			distribRatio = targetDistrib(proposal)/targetDistrib(initVal);//Generate acceptance probability for generated proposal.
		}
		else{
			distribRatio = 1;//Reject initial value if it has target probability 0.
		}
		RandomNumb = rand()%1000000;//generate random number between 0 and 1.
		RandomNumb = RandomNumb/1000000.0;//-''-
		if(distribRatio > RandomNumb){//Accept proposal.
			Sample[i] = proposal;
			initVal = proposal;
		}
		else{
			Sample[i] = initVal;//Reject proposal.
		}
	}
}

int main(){
	int *Samplesize;//Defining variables and allocating storage.
	double *Sample;
	double initVal = 1;//Define initial value.)
	Samplesize = (int *) malloc(sizeof(int)+1);
	Samplesize[0] = 1000000;//Define sample size
	Sample = (double *) malloc(sizeof(double)*Samplesize[0]+1);
	SampleGenerator(initVal, Samplesize, Sample);
	
	FILE *fp;//create/open file and write sample values.
	fp = fopen("MetropolisSample.txt", "w");
	for(int j=0; j<Samplesize[0]; j++) {
		fprintf(fp, "%f\n", Sample[j]);
	}
		fclose(fp);
}
