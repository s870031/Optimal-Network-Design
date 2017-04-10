/*
 * C++ Program to Find All Pairs Shortest Path
 */
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include "generator.h"
#define infi 999

const int N=20; // Number of nodes

using namespace std;
int p[N][N];
/*
 * All Pairs Shortest Path using Floyd's Algorithm
 */
void allpairshort(vector<vector<int> > a, int n) {
	int k, i, j;
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (a[i][k] + a[k][j] < a[i][j]) {
					a[i][j] = a[i][k] + a[k][j];
					p[i][j] = k;
				}
			}
		}
	}
}

/*
 * Storing the shortest path
 */
void shortest(int i, int j, vector<int> &path) {
	int k = p[i][j];
	if (k > 0) {
		shortest(i, k, path);
		path.push_back(k);
		shortest(k, j, path);
	}
}
/*
 * Return the Shortest Path
 */
vector<int> findpath(vector<vector<int> > a, int i, int j, int n) {
	vector<int> path;
	if (a[i][j]  < infi) {
		path.push_back(i);
		shortest(i, j,path);
		path.push_back(j);
	}
	return path;
}
void saveDotFile(vector<vector<int> > graph, string filename) {
	std::ofstream dot_file1(filename);
	dot_file1 << "digraph D {\n"
		<< "  rankdir=LR\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			if (graph[i][j] != 0) {
				dot_file1 << i << " -> " << j 
					<< "[label=\"" << graph[i][j] << "\"";
				dot_file1 << ", color=\"black\"]";
			}
		}
	}
	dot_file1 << "}";
}
/*
 * Main Contains Menu
 */
int main() {

	// TODO Bad implimentation of random number.
	// Try to use other way to generate random number
	// e.g. c++11 library <random>
	srand(time(0));
	int k;
	Generator g;
	vector<vector<int> > b; // Demand of all link ij
	vector<vector<int> > a; // Cost of all link ij
	vector<vector<int> > z(N,vector<int>(N,0)); // Capacity of all link ij
	int optimalCost = 0;
	int linksCreated = 0; // Count the number of links created

	//cout << "k factor: "; cin >> k;
	k = 13;

	// Generate aij and bij
	b = g.generateBij(N);
	a = g.generateAij(N,k);

	// Draw cost topology in dot file
	//saveDotFile(a,"costtopology.dot");

	// Calculate shortest path 
	allpairshort(a, N);

	// Set Capacity
	for(int k=0; k<N; k++) {
		for(int l=0; l<N; l++) {
			vector<int> path;
			path = findpath(a,k,l,N);
			// Go throuth the path and 
			//	set each link capacity as bkl
			for(int i=0; i<path.size()-1; i++) {
				int i1=path[i], i2=path[i+1];

				z[i1][i2] += b[k][l];	
			}
		}
	}

	// Calculate cost and link created
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if(z[i][j] != 0) {
				// Calculate number of links
				linksCreated++;
			}
			// Calculate expected cost
			optimalCost += (z[i][j]*a[i][j]);
		}
	}
	// Draw estimated topology in dot file
	saveDotFile(z,"topology.dot");

	// Print outcome
	cout << endl;
	cout << "k = " << k << endl;
	cout << "Links created: " << linksCreated << endl;
	cout << "Link density : " << (double)linksCreated/(N*(N-1)) << endl;
	cout << "Optimal cost : " << optimalCost << endl;
	cout << endl;
//	cout << "Estimated links: (numbers represents the capacity)" << endl;
//	g.printMatrix(z);
//	cout << endl;
	return 0;
}
