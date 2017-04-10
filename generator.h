#ifndef GE_H
#define GE_H

#include <vector>
using namespace std;
class Generator
{
	public:
		vector<vector<int> > generateAij(int N, int k);
		vector<vector<int> > generateBij(int N);
		vector<int> getKRandNums(int range, int k);
		void printMatrix(vector<vector<int> > m);
};

#endif
