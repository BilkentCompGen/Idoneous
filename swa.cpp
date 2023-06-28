#include <string>
#include <iostream>
using namespace std;


#define GAP_PEN (-1)
#define MIS_PEN (-1)


int max( int a, int b){
	return a > b ? a : b;
}

int mini( int a, int b){
	return a < b ? a : b;
}

int delta( char a, char b){
	if( a >> 6 == b >> 6)
		return 1; //64 - max(a&63,b&63);
	return MIS_PEN;
}

int sw_score( string x, string y, int lenx, int leny ){
	int*  scores = (int*)malloc( lenx * leny * sizeof(int));
	int tempmax = 0;
//	cout << "lenx: " << lenx << endl;
//	cout << "leny: " << leny << endl;

	for( int i = 0; i < lenx*leny; i++){
		if( i < leny ){
			scores[i] = 0;
		}else if( i % leny == 0 ){
			scores[i] = 0;
		}else{
			scores[i] = max( max( 0 , scores[i-1-leny]+delta( x.at(i/leny-1), y.at(i%leny-1) )), max( scores[i-1] + GAP_PEN , scores[i-leny] + GAP_PEN ));
			tempmax = max( tempmax, scores[i]);
		}
	}
	free(scores);
	return tempmax;
}
