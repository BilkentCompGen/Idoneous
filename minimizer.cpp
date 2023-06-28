#include "bitpack.h"
#include "comparison.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int windowSize( int k, int l, int order){
	return l;//l*(order+1)+k*order;
}

void minimizer( const char* s, int n, int k, int l , vector<int>* mins){
	for(int ord = 0; ord < ORDER_SIZE; ord++ ){
		int jump = 1;
		for( int i = 0; i < n - windowSize(k,l,ord) - k  ; i++){
			int tempmax = 0;
			for( int j = jump; j < windowSize(k,l,ord); j++ ){
				if( kmerCmp( &s[i + tempmax], &s[i + j], k , ord) >= 0 ){
					tempmax = j;
				}
			}
			jump = 1 + ((windowSize(k,l,ord)-1-tempmax)%(windowSize(k,l,ord)-1));// tempmax ? l - tempmax :  1;
			i += tempmax;
			mins[ord].push_back(i);
		}
	}


/*	for( int i = 0 ; i < ORDER_SIZE; i++){
		cout << "i: " << i << "|";
		for (vector<int>::iterator it = mins[i].begin() ; it != mins[i].end(); ++it)
    			cout << ' ' << *it;
		cout << endl;
	}
*/

}
/*
int main( int argc, char* argv[] ){
	string s0 = "CCATCCTGCGTGGCCGAGGGCTTCTTAGAAGCGAGACGGAGCAGACCCATCTGCTACTGCCCTTTCTATAATAACTAAAGTTAGCTGCCCTGGACTATTCACCCCCTAGTCTCAATTTAAGAAGATCCCCATGGCCACAGGGCCCCTGCCTGGGGGCTTGTCACCTCCCCCACCTTCTTCCTGAGTCATTC";
	string s;
	vector<int> mins[ORDER_SIZE];
	int n;
	bitpack(s0,s,n);
	const char * cs = s.c_str();
	cout << n << " " << strandPrint(s) <<  endl;
	int k = 3;
	int l = 10;
	if( argc > 2){
		k = stoi(argv[1]);
		l = k + stoi(argv[2]);
	}
	minimizer(cs,n,k,l,mins);
	
	for( int i = 0 ; i < ORDER_SIZE; i++){
		cout << "i: " << i << endl; 
		for (vector<int>::iterator it = mins[i].begin() ; it != mins[i].end(); ++it)
    			cout << ' ' << strandPrint(s.substr(*it,k))<< endl;
		cout << endl;
	}
	return 0;
}*/
