#ifndef _neural_h_
#define neural_h_

#include "helper.h"
#include<bits/stdc++.h>
using namespace std;
struct NeuralNet{
	int n;
	vector<int> size;
	vector<matrix> w,b,d_w,d_b;
	double learning_rate;
	NeuralNet() {}
	NeuralNet(vector<int> sz, double alpha){
		n = (int)(sz.size());
		size = sz;
		w.resize(n-1);
		b.resize(n-1);
		d_w.resize(n-1);
		d_b.resize(n-1);
		for(int i = 0; i < n-1; i++){
			w[i] = matrix(size[i],size[i+1]);
			b[i] = matrix(1, size[i+1]);
			d_w[i] = matrix(size[i], size[i+1]);
			d_b[i] = matrix(1,size[i+1]);
			w[i].random();
			b[i].random();
		}
		learning_rate = alpha;
	}
	matrix feedForward(matrix input){
		for(int i = 0; i < n-1; i++){
			input = activate( addMat(mulMat2d(input, w[i]),b[i]) );
		}
		return input;
	}

	void backPropagation(matrix input, matrix output){
		vector<matrix> l;
		matrix delta;
		l.push_back(input);
		for(int i = 0; i < n-1; i++){
			input = activate(addMat(mulMat2d(input,w[i]), b[i]));
			l.push_back(input);
		}
		delta = subMat(input,output);
		delta = mulMat(delta,derive(l[n-1]));
		d_b[n-2].add(delta);
		d_w[n-2].add(mulMat2d(transMat(l[n-2]), delta));
		for(int i = n-2; i >= 0; i--){
			delta = mulMat2d(delta,transMat(w[i+1]));
			delta = mulMat(delta, derive(l[i+1]));
			d_b[i].add(delta);
			d_w[i].add(mulMat2d(transMat(l[i]), delta));
		}
	}
	void train(vector<matrix> inputs, vector<matrix> outputs){
		for(int i = 0; i < n-1; i++){
			d_w[i].zero();
			d_b[i].zero();
		}
		for(int i = 0; i <(int)(inputs.size()); i++){
			backPropagation(inputs[i], outputs[i]);
		}
		for(int i = 0; i < n-1; i++){
			for(int j = 0; j < d_w[i].n; j++){
				for(int k = 0; k < d_w[i].m; k++){
					d_w[i][j][k] /= (double)(inputs.size());
					w[i][j][k] -= learning_rate*d_w[i][j][k];
				}
			}
			for(int j = 0; j < d_b[i].n; j++){
				for(int k = 0; k < d_b[i].m; k++){
					d_b[i][j][k] /= (double)(inputs.size());
					b[i][j][k] -= learning_rate*d_b[i][j][k];
				}
			}
		}

	}

};
#endif
