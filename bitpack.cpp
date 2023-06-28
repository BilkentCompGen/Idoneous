#include "bitpack.h"
using namespace std;


string basePrint( const unsigned char c ){
	switch( c / 64  ){
		case A:
			return  "A" + to_string( 64 -  c%64 );
		case C:
			return  "C" + to_string( 64 - c%64 );
		case T:
			return  "T" + to_string(  64 - c%64 );
		case G:
			return  "G" + to_string( 64 -  c%64 );
	}
	return  "";
}

string strandPrint( string s){
	string result = "";
	for(int i = 0; i < s.size(); i++){
		result += basePrint(s[i]) + " ";
	}
	return result;
}

int* bitpack( string s , string & rle, int& size){
	size = s.size();
	rle="";
	char in = s[0];
	unsigned int rep = 1;
	for( int i = 1; i < s.size() ; i++){
		if( in != s[i] || rep == 62 ){
			unsigned char c = (((in / 2)%4)<<6) + 64 - rep;
			rle += c;
			rep = 1;
			in = s[i];
		}else{
			rep++;
		}
	}
	unsigned char c = (((in / 2)%4)<<6) +  64 - rep;
	rle += c;
	size = rle.size();
	int* endMap = (int*) malloc( (size+1) * sizeof(long));
	endMap[0] = 0;
	for( int i = 1; i < size ; i++ ){
		endMap[i] = endMap[i-1] + 64 -  (rle[i-1] & 63 );
		if( endMap[i] < 0 ) cout << endMap[i] << " " << i << endl;
	}
	endMap[size] = s.size();
	return endMap;
}


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
