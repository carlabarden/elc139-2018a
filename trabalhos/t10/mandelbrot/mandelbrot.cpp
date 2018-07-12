#include <complex>
#include <iostream>
#include <chrono>
#include "tbb/tbb.h"

using namespace std;
using namespace tbb;

void mdb (int maxcol, int maxn, int maxrow, char **matriz, int rr, int c){
	complex<float> z;
	int n = 0;
	while(abs(z) < 2 && ++n < maxn)
		z = pow(z, 2) + decltype(z)(
			(float)c * 2 / maxcol - 1.5,
			(float)rr * 2 / maxrow - 1
		);
	matriz[rr][c]=(n == maxn ? '#' : '.');
}

int main(){
	int max_row, max_column, max_n;
	cin >> max_row;
	cin >> max_column;
	cin >> max_n;

	char **mat = (char**)malloc(sizeof(char*)*max_row);

	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column);

//tempooo
auto start_time = chrono::high_resolution_clock::now();
   for(int r = 0; r < max_row; ++r)
      parallel_for(int(0), max_column, [&](int c){
         mdb(max_column, max_n, max_row, mat, r, c);
      });
	
auto end_time = chrono::high_resolution_clock::now();
long long ttime = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

/*	for(int r = 0; r < max_row; ++r){
		for(int c = 0; c < max_column; ++c)
			std::cout << mat[r][c];
		cout << '\n';
	}	*/
std::cout << "TBB (microsegundos): ; " << ttime <<  ";" << endl;
}

