#ifndef _helper_h_
#define _helper_h_

#include<bits/stdc++.h>
using namespace std;
struct sudrng{
	unsigned x,y,z,w;
	sudrng(): x(13020230), y(38282424), z(24355534), w(424889889) {}
	unsigned next(){
		unsigned t = x ^ (x<<11);
		x = y; y = z; z = w;
		return w = w^(w>>19) ^ t ^ (t>>8);
	}
} rng;

double rand_1(){
	return rng.next()%1000000001 / 1000000000.0;
}

struct matrix{
	int n,m;
	double **a;
	matrix(): n(0), m(0), a(nullptr) {}
	matrix(int rows, int cols){
		n = rows;
		m = cols;

		a = new double* [n];
		for(int i = 0; i < n; i++){
			a[i] = new double [m];
			for(int j = 0; j < m; j++){
				a[i][j] = 0;
			}
		}
	}
	matrix(const matrix &x){
		int i, j;
		n = x.n;
		m = x.m;

		a = new double* [n];
		for(int i = 0; i < n; i++){
			a[i] = new double [m];
			for(int j = 0; j < m; j++){
				a[i][j] = x.a[i][j];
			}
		}

	}


~matrix(){
	for(int i = 0; i < n; i++){
		free(a[i]);
	}
	free(a);
}

	void operator =(const matrix &x){
		int i, j;
		n = x.n;
		m = x.m;

		a = new double* [n];
		for(int i = 0; i < n; i++){
			a[i] = new double [m];
			for(int j = 0; j < m; j++){
				a[i][j] = x.a[i][j];
			}
		}
	}
	void random(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				a[i][j] = rand_1();
				if(rng.next()%2 == 0) a[i][j] = -a[i][j];
			}
		}
	}

	void zero(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				a[i][j] = 0.0;	
			}
		}	
	}
	void add(matrix x){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				a[i][j] += x[i][j];
			}	
		}
	}
	double* &operator [](const int &id){
		return a[id];
	}
};
	
	matrix addMat(matrix x, matrix y){
		matrix result(x.n,x.m);
		for(int i = 0; i < x.n; i++){
			for(int j = 0; j < x.m; j++){
				result.a[i][j] = x.a[i][j] + y.a[i][j]; 
			}
		}
		return result;
	}
	
	matrix subMat(matrix x, matrix y){
		matrix result(x.n,x.m);
		for(int i = 0; i < x.n; i++){
			for(int j = 0; j < x.m; j++){
				result.a[i][j] = x.a[i][j] - y.a[i][j]; 
			}
		}
		return result;
	}
	matrix mulMat(matrix x, matrix y){
		matrix result(x.n,x.m);
		for(int i = 0; i < x.n; i++){
			for(int j = 0; j < x.m; j++){
				result.a[i][j] = x.a[i][j] * y.a[i][j]; 
			}
		}
		return result;
	}
	matrix transMat(matrix x){
		matrix result(x.m,x.n);
		for(int i = 0; i < x.n; i++){
			for(int j = 0; j < x.m; j++){
				result.a[j][i] = x.a[i][j];
			}
		}
		return result;
	}
	matrix mulMat2d(matrix x, matrix y){
		matrix result(x.n,y.m);
		for(int i =0; i < x.n; i++){
			for(int j = 0; j < y.m; j++){
				for(int k = 0; k < x.m; k++){
					result.a[i][j] += x.a[i][k] * y.a[k][j];
				}
			}
		}
		return result;
	}

	double act(double x){
		return 1.0 / (1.0 + exp(-x));
	}
	double der(double x){
		return x * (1.0 - x);
	}
	matrix activate(matrix x){
		matrix result(x.n,x.m);
		for(int i = 0; i < x.n; i++){
			for(int j = 0; j < x.m; j++){
				result.a[i][j] = act(result.a[i][j]); 
			}
		}
		return result;
	}

	matrix derive(matrix x){
		matrix result(x.n,x.m);
		for(int i = 0; i < x.n; i++){
			for(int j = 0; j < x.m; j++){
				result.a[i][j] = der(result.a[i][j]); 
			}
		}
		return result;
	}
#endif

