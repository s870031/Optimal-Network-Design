#include <iostream>
#include <math.h>
#include <time.h>
#include "generator.h"

// Print 2D Matrix
void Generator::printMatrix (vector<vector<int> > m) {
	for(int row=0; row<m.size(); row++) {
		for(int col=0; col<m[0].size(); col++) {
			cout << m[row][col] << " ";
		}
		cout << endl;
	}
}
// Generate b[i][j]
vector<vector<int> > Generator::generateBij(int N) {
	int d[20] = {2,0,2,1,2,8,6,5,2,8,
		2,0,2,1,2,8,6,5,2,8};
	vector<vector<int> > b(N, vector<int>(N,0));

	// Set b[i][j] = | di - dj |
	//	if i=j, b[i][j] = 0
	for (int i=0; i<b.size(); i++) {
		for(int j=0; j<b[0].size(); j++) {
			if (i==j)
				b[i][j] = 0;
			else 
				b[i][j] = abs(d[i]-d[j]);
		}
	}
	return b;
}
// Generate K Random Nums in the range
vector<int> Generator::getKRandNums(int range,int k) {
	vector<int> kRandNums;
	// Generate random number k times
	for(int i=0; i<k; i++) {
		int r = (rand()%range) + 1;
		kRandNums.push_back(r);
	}
	return kRandNums;
}
// Generate a[i][j]
vector<vector<int > > Generator::generateAij(int N, int k) {
	vector<vector<int> > a(N,vector<int>(N,0));
	vector<int> kRandNums;

	// Set a[i][j]:
	//	a[i][j1..jk] = 1
	//	a[i][
	//	a[i][i] = 0;
	for (int i=0; i<N; i++) {
		kRandNums = getKRandNums(N-1,k);
		// Set a[i][jk] = 1;
		for (int jn=0; jn<kRandNums.size(); jn++) {
			a[i][kRandNums[jn]] = 1;
		}
		// Set other a[i][j]
		for(int j=0; j<N; j++) {
			if (i==j)
				a[i][j] = 0;
			else if (a[i][j] == 1) 
				continue;
			else
				a[i][j] = 200;
		}
	}
	return a;
}
