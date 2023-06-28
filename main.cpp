#include "bitpack.h"
#include "comparison.h"
#include "minimizer.h"
#include "factorize.h"
#include "swa.h"
#include "coord.h"

#include "edlib.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <string.h>
#include <algorithm>

#define SNUM 1000
#define TINDEL 50
#define MICROAL 0
#define LEAF_COUNTING 0
#define LEVEL_SIZE_NUMBER 0
using namespace std;

int distancex = 0;
int totalCoverx = 0;
int uniqueCoverx = 0;

void eliminateDuplicates(std::vector<Coordinate>& coordinates) {
    if (coordinates.empty())
        return;

    std::vector<Coordinate> uniqueCoordinates;
    uniqueCoordinates.reserve(coordinates.size());
    uniqueCoordinates.push_back(coordinates[0]);

    for (size_t i = 1; i < coordinates.size(); ++i) {
        if (!(coordinates[i] == coordinates[i - 1]))
            uniqueCoordinates.push_back(coordinates[i]);
    }

    coordinates = std::move(uniqueCoordinates);
}

void filereadref( ifstream& f, string& s ){
	string temp;
	while( getline( f, temp ) ){
		if(temp[0] != '>' ){
			s = s.append(temp);
		}
	}
}

void countN( int* nmap, string& s ){
	int ii = 0;
	int ni = 0;
	for( int i = 0 ; i < s.size(); i++){
		if( s[i] == 'N' ){
			ni++;
		}else{
			nmap[ii] = ni;
			ii++;
		}
	}

}

void eraseN( string& s ){
		erase(s,'N');
		erase(s,'.');
		erase(s,'-');
}

void reversecomplement( string& s, string& r){
	r = string( s.rbegin(), s.rend());
	replace(r.begin(), r.end(), 'A', 'Z' );
	replace(r.begin(), r.end(), 'T', 'A' );
	replace(r.begin(), r.end(), 'Z', 'T' );
	replace(r.begin(), r.end(), 'G', 'Z' );
	replace(r.begin(), r.end(), 'C', 'G' );
	replace(r.begin(), r.end(), 'Z', 'C' );
}

void findSeeds( std::vector<Coordinate>& v, lyndonWord& l1, lyndonWord& l2, string& st1 , string& st2, int* & nMap1, int* & nMap2, int*& end1 , int*& end2 , int a, int b, int c, int d,  int e, int k  , int reverse= 0 ){
	vector<lyndonWord*> lwl1, lwl2;
	slices( &l1, lwl1,  d ,b );
	slices( &l2, lwl2,  d ,b );
	int dd = st1.size();
	int dd2 = st2.size();

	for( int j = 0 ; j < lwl1.size(); j++){
		int tempMax = 0;
		for( int  jj = 0; jj < lwl2.size(); jj++ ){
//			cout << reverse << " "<< j << " "<<jj << endl;
			int tempj = 0;
			vector<long> yanc;
      long lend1 = l1.end > d*(j+a) ? d*(j+a) : l1.end ;
      long lend2 = l2.end > d*(jj+a) ? d*(jj+a) : l2.end;
//			getAnchor( lwl1[j], lwl2[jj] , yanc, k, l1.end/d*(j+a), l2.end/d*(jj+a)  );
      getAnchor( lwl1[j], lwl2[jj] , yanc, k, lend1, lend2  );
		vector<long> anc;
			getIntervals( yanc, b/e, anc, c);
			if( anc.empty() || anc.size() < 4) continue;
			for( int i = 0; i < anc.size()-3; i+=4){
				int fip,fep,sip,sep;

				fip = anc[i] > b ?  end1[anc[i]-b] : end1[0]; //firstEnds[anc[i]-b];
				fep = anc[i+2] + b < st1.length() ?  end1[anc[i+2]+b-1] : end1[st1.length()-1 ] ;// firstEnds[anc[i+2]+b-1];
				sip = anc[i+1] > b ? end2[anc[i+1]-b] : end2[0]; //secondEnds[anc[i+1]-b];
				sep = anc[i+3] + b < st2.length() ? end2[anc[i+3]+b-1] :end2[st2.length()-1 ] ; //secondEnds[anc[i+3]+b-1];

				string temp1 = st1.substr( fip , fep-fip );
				string temp2 = st2.substr( sip, sep-sip );
				if( temp1.length() == 0 || temp2.length() == 0 ) continue; 
				EdlibAlignResult result = edlibAlign( temp1.c_str(), temp1.size(),
									temp2.c_str(), temp2.size(),
									edlibNewAlignConfig(temp1.size()/100, EDLIB_MODE_NW, EDLIB_TASK_PATH, NULL, 0) );
				if( result.editDistance >= 0 ){
					switch ( reverse ){
						case 0:
	       	                        //		cout << fip + nMap1[fip] << "," << fep+ nMap1[fep] << "-" << sip + nMap2[sip] << "," << sep+ nMap2[sep] <<": " << result.editDistance  <<  endl;
							v.push_back( Coordinate  ( fip + nMap1[fip] , fep+ nMap1[fep] , sip + nMap2[sip] , sep+ nMap2[sep] , result.editDistance ));
							break;
						case 1:
	        	                  //      	cout << dd - fep + nMap1[dd-fep-1] << "," << dd- fip + nMap1[dd-fip-1]  << "-" << sip + nMap2[sip] << "," << sep+ nMap2[sep] <<": " << result.editDistance  <<  endl;
							 v.push_back( Coordinate  ( dd - fep + nMap1[dd-fep-1] , dd- fip + nMap1[dd-fip-1] , sip + nMap2[sip] , sep+ nMap2[sep] , result.editDistance ));
							break;
						case 2:
	       	                        //		cout << fip + nMap1[fip] << "," << fep+ nMap1[fep] << "-" << dd2 - sep + nMap2[dd-sep-1] << "," << dd2 - sip + nMap2[dd-sip-1] <<": " << result.editDistance  <<  endl;
							 v.push_back( Coordinate  (fip + nMap1[fip] , fep+ nMap1[fep] , dd2 - sep + nMap2[dd-sep-1] , dd2 - sip + nMap2[dd-sip-1] , result.editDistance ));
							break;
						case 3:
	       	                        //		cout << dd - fep + nMap1[dd-fep-1] << "," << dd- fip + nMap1[dd-fip-1] << "-" << dd2 - sep + nMap2[dd-sep-1] << "," << dd2 - sip + nMap2[dd-sip-1] <<": " << result.editDistance  <<  endl;
								v.push_back( Coordinate  (dd - fep + nMap1[dd-fep-1], dd- fip + nMap1[dd-fip-1] , dd2 - sep + nMap2[dd-sep-1] , dd2 - sip + nMap2[dd-sip-1] , result.editDistance ));
							break;
					}
					if( MICROAL ){
       	                	       		char* cigar = edlibAlignmentToCigar(result.alignment, result.alignmentLength, EDLIB_CIGAR_STANDARD);
              	        	        		printf("%s\n", cigar);
              		                		free(cigar);
						cout << "-------------------------------------------------------------------------------------------" << endl;
					}
        	                        distancex += result.editDistance;
               	               		totalCoverx += temp2.size();
					tempj += temp1.size();
               	       		}
			}
			if( tempMax < tempj ) tempMax = tempj;

		}
		uniqueCoverx += tempMax;
	}

}

void findAllSeeds(std::vector<Coordinate>& v , lyndonWord** llist, string** slist, int*& nMap1, int*& nMap2, int** ends, int a, int b, int c, int d, int e, int k  ){
			findSeeds(v,*llist[0],*llist[1], *slist[0] , *slist[1] , nMap1,nMap2,ends[0],ends[1],a,b,c,d,e,k);
			findSeeds(v,*llist[2],*llist[1], *slist[2] , *slist[1] ,nMap1,nMap2,ends[2],ends[1],a,b,c,d,e,k,1);
//			findSeeds(v,*llist[0],*llist[3], *slist[0] , *slist[3] , nMap1,nMap2,ends[0],ends[3],a,b,c,d,e,k,2);
//			findSeeds(v,*llist[2],*llist[3], *slist[2] , *slist[3] ,nMap1,nMap2,ends[2],ends[3],a,b,c,d,e,k,3);
			sort(v.begin(), v.end(), compareCoordinates);
			eliminateDuplicates(v);
}

int main( int argc, char* argv[]){

	if( argc < 9 ){


		return 0;
	}
		int* ends[4];
		int* firstEnds;
		int* secondEnds;
		int* revEnds;
		int* revEnds2;
		int* nMap1;
		int *nMap2;
		string temp;
		string st1 = "";
		string st2 = "";
		string st1r = "";
		string st2r = "";
		string bp1 = "";
		string bp2 = "";
		string bpr = "";
		string bpr2 = "";
		ifstream f1( argv[1]);
		ifstream f2( argv[2]);
		int b = stoi( argv[3]);
		int k = stoi( argv[4]);
		int chain = stoi(argv[5]);
		int err = stoi(argv[6]);
		int d = stoi(argv[7]);
		int a = stoi(argv[8]);

		cerr << "first file reading..." << endl;
		filereadref(f1,st1);
		cerr << "second file reading..." << endl;
		filereadref(f2,st2);
		cerr << "cleaning..."<< endl;
		nMap1 = (int*) malloc( sizeof(int)* (st1.size() - count(st1.begin(), st1.end(), 'N')) );
		nMap2 = (int*)malloc( sizeof(int)* (st2.size() - count(st2.begin(), st2.end(), 'N')) );
		countN( nMap1, st1 );
		countN( nMap2, st2 );
		eraseN( st1);
		eraseN( st2);

		reversecomplement( st1, st1r );
		reversecomplement( st2, st2r );
		cerr << "first genome bitpacking..." << endl;
		int dumo;
		ends[2] = bitpack( st1r, bpr, dumo);
		revEnds = ends[2];//bitpack( st1r, bpr, dumo);
		ends[0] = bitpack( st1, bp1, dumo);
		firstEnds = ends[0];//bitpack( st1, bp1, dumo);
		cerr << "size1: " << dumo << endl;
		cerr << "second genome bitpacking..." << endl;
		ends[1] = bitpack( st2, bp2, dumo);
		secondEnds = ends[1];//bitpack( st2, bp2, dumo);
		ends[3] = bitpack( st2r, bpr2, dumo);
		revEnds2 = ends[3];//bitpack( st2r, bpr2, dumo);
		cerr << "size2: " << dumo << endl;

		cerr << "first genome lyndon init..." << endl;
		lyndonWord l1( &bp1 );
		lynInit( l1, b);
		cerr << "second genome lyndon init..." << endl;
		lyndonWord l2( &bp2 );
		lynInit( l2, b);
		cerr << "reverse genome lyndon init..." << endl;
		lyndonWord lr( &bpr );
		lynInit( lr, b);
		cerr << "reverse2 genome lyndon init..." << endl;
		lyndonWord lr2( &bpr2 );
		lynInit( lr2, b);

		cerr << "find anchors" << endl;

		lyndonWord* llist[4];
		llist[0] = &l1;
		llist[1] = &l2;
		llist[2] = &lr;
		llist[3] = &lr2;

		string* slist[4];
		slist[0] = &st1;
		slist[1] = &st2;
		slist[2] = &st1r;
		slist[3] = &st2r;

		std::vector<Coordinate> v;

		findAllSeeds(v, llist, slist, nMap1, nMap2, ends, a, b, chain, d, err, k);
		//lexispetialList( l1 );
		int disum = 0;
		int cove = 0;
		for( Coordinate c: v){
			disum += c.d;
			cove += c.fe-c.fi;
			cout << c << endl;
		}
//		cout << "distance:" << distancex << endl;
//		cout << "Total cover:" << totalCoverx << "("<< uniqueCoverx << ")" << endl;
		cerr << "distance:" << disum << endl;
		cerr << "Total cover:" << cove << endl;


	return 0;
}
