#include <complex>
#include <iostream>
#include <time.h>
#include <omp.h>

#define NTH 2 //num threads

using namespace std;

int main(){
	int max_row, max_column, max_n;
	cin >> max_row;
	cin >> max_column;
	cin >> max_n;

	char **mat = (char**)malloc(sizeof(char*)*max_row);

	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column);

//calcular o tempo
   double starttime = omp_get_wtime();
   //#pragma omp parallel for schedule(static) num_threads((NTH/2))
	for(int r = 0; r < max_row; ++r){
	   #pragma omp parallel for schedule(dynamic) num_threads(NTH)
		for(int c = 0; c < max_column; ++c){
			complex<float> z;
			int n = 0;
			while(abs(z) < 2 && ++n < max_n)
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / max_column - 1.5,
					(float)r * 2 / max_row - 1
				);
			//#pragma omp barrier
			mat[r][c]=(n == max_n ? '#' : '.');
		}
	}
   double endtime = omp_get_wtime();
/*
	for(int r = 0; r < max_row; ++r){
		for(int c = 0; c < max_column; ++c)
			std::cout << mat[r][c];
		cout << '\n';
	}	*/
std::cout << "Tempo: " << endtime - starttime << " segundos." << endl;
}


