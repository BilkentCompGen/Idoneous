#include <iostream>
#include <string.h>
using namespace std;



enum bases{A=0,C,T,G=3};


string basePrint( const unsigned char c );
string strandPrint( string s );
int* bitpack( string s , string & rle, int& size  );


/*int main( int argc, char* argv[]){

	string s = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATGGGCCTTTAAACCACACAA";
	int size;
	string b = "";
	bitpack(s,b,size);
	cout << s << endl;
	for( int i = 0; i < size; i++ ){
			cout << basePrint(b[i]) << " ";
	}
	cout << endl;


	return 0;

}
*/
